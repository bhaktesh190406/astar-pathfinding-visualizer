#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROW 20
#define COL 20

typedef struct {
    int x, y;
    int g, h, f;
    int parent_x, parent_y;
} Node;

int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int isValid(int x, int y, int grid[ROW][COL])
{
    return (x >= 0 && y >= 0 && x < ROW && y < COL && grid[x][y] == 0);
}

int isInList(Node list[], int size, int x, int y)
{
    for(int i = 0; i < size; i++)
        if(list[i].x == x && list[i].y == y)
            return i;
    return -1;
}

void reconstructPath(Node closed[], int closedSize, int endx, int endy, int path[][2], int *pathLen)
{
    int x = endx, y = endy;
    *pathLen = 0;

    while(1)
    {
        path[*pathLen][0] = x;
        path[*pathLen][1] = y;
        (*pathLen)++;

        int index = isInList(closed, closedSize, x, y);
        if(index == -1) break;

        int px = closed[index].parent_x;
        int py = closed[index].parent_y;

        if(px == x && py == y) break;

        x = px;
        y = py;
    }
}

int astar(int grid[ROW][COL], int startx, int starty, int endx, int endy, int path[][2])
{
    Node open[400];
    Node closed[400];

    int openSize = 0, closedSize = 0;

    Node start = {startx, starty, 0, heuristic(startx,starty,endx,endy), 0, startx, starty};
    start.f = start.g + start.h;

    open[openSize++] = start;

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    int iterations = 0;
    int maxIterations = 10000;

    while(openSize > 0 && iterations < maxIterations)
    {
        iterations++;

        int best = 0;
        for(int i = 1; i < openSize; i++)
        {
            if(open[i].f < open[best].f)
                best = i;
        }

        Node current = open[best];

        open[best] = open[--openSize];
        closed[closedSize++] = current;

        if(current.x == endx && current.y == endy)
        {
            int pathLen;
            reconstructPath(closed, closedSize, endx, endy, path, &pathLen);
            return pathLen;
        }

        for(int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if(!isValid(nx, ny, grid))
                continue;

            if(isInList(closed, closedSize, nx, ny) != -1)
                continue;

            int g = current.g + 1;
            int h = heuristic(nx, ny, endx, endy);
            int f = g + h;

            int openIndex = isInList(open, openSize, nx, ny);

            if(openIndex == -1)
            {
                if(openSize >= 399) return -1;

                Node neighbor = {nx, ny, g, h, f, current.x, current.y};
                open[openSize++] = neighbor;
            }
            else if(g < open[openIndex].g)
            {
                open[openIndex].g = g;
                open[openIndex].f = g + open[openIndex].h;
                open[openIndex].parent_x = current.x;
                open[openIndex].parent_y = current.y;
            }
        }
    }

    return -1; // No path found
}