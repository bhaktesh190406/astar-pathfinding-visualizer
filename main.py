import pygame
import ctypes
import numpy as np

ROWS = 20
COLS = 20
CELL_SIZE = 30

WIDTH = COLS * CELL_SIZE
HEIGHT = ROWS * CELL_SIZE

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("A* Visualizer")

grid = np.zeros((ROWS, COLS), dtype=np.int32)

start = (0, 0)
end = (19, 19)

lib = ctypes.CDLL("./astar.dll")

lib.astar.argtypes = [
    np.ctypeslib.ndpointer(dtype=np.int32),
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_int,
    ctypes.c_int,
    np.ctypeslib.ndpointer(dtype=np.int32)
]

def draw_grid():
    screen.fill((255,255,255))

    for r in range(ROWS):
        for c in range(COLS):

            color = (200,200,200)

            if grid[r][c] == 1:
                color = (0,0,0)

            if (r,c) == start:
                color = (0,255,0)

            if (r,c) == end:
                color = (255,0,0)

            pygame.draw.rect(screen,color,(c*CELL_SIZE,r*CELL_SIZE,CELL_SIZE,CELL_SIZE))
            pygame.draw.rect(screen,(120,120,120),(c*CELL_SIZE,r*CELL_SIZE,CELL_SIZE,CELL_SIZE),1)

    pygame.display.update()


def run_astar():
    draw_grid()

    path = np.zeros((400,2),dtype=np.int32)

    count = lib.astar(
        grid,
        start[0],
        start[1],
        end[0],
        end[1],
        path
    )

    if count == -1:
        print("No path found ❌")
        return

    for i in range(count):
        x = path[i][0]
        y = path[i][1]

        if (x,y) != start and (x,y) != end:
            pygame.draw.rect(screen,(0,0,255),(y*CELL_SIZE,x*CELL_SIZE,CELL_SIZE,CELL_SIZE))

        pygame.display.update()
        pygame.time.delay(40)


def clear_grid():
    global grid
    grid = np.zeros((ROWS, COLS), dtype=np.int32)


running = True

while running:

    draw_grid()

    for event in pygame.event.get():

        if event.type == pygame.QUIT:
            running = False

        # LEFT CLICK → add wall
        if pygame.mouse.get_pressed()[0]:
            mx,my = pygame.mouse.get_pos()
            r = my // CELL_SIZE
            c = mx // CELL_SIZE

            if (r,c) != start and (r,c) != end:
                grid[r][c] = 1

        # RIGHT CLICK → remove wall
        if pygame.mouse.get_pressed()[2]:
            mx,my = pygame.mouse.get_pos()
            r = my // CELL_SIZE
            c = mx // CELL_SIZE

            if (r,c) != start and (r,c) != end:
                grid[r][c] = 0

        if event.type == pygame.KEYDOWN:

            if event.key == pygame.K_SPACE:
                run_astar()

            if event.key == pygame.K_c:
                clear_grid()

pygame.quit()