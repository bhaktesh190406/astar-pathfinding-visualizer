#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROW 20
#define COL 20

typedef struct {
    int x;
    int y;
} Node;

int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int astar(int grid[ROW][COL], int startx, int starty, int endx, int endy, int path[400][2])
{
    int visited[ROW][COL] = {0};

    int dx[4] = {1,-1,0,0};
    int dy[4] = {0,0,1,-1};

    int count = 0;

    int x = startx;
    int y = starty;

    while(x != endx || y != endy)
    {
        int bestx = x;
        int besty = y;
        int besth = 9999;

        for(int i=0;i<4;i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx>=0 && ny>=0 && nx<ROW && ny<COL && !visited[nx][ny] && grid[nx][ny]==0)
            {
                int h = heuristic(nx,ny,endx,endy);

                if(h < besth)
                {
                    besth = h;
                    bestx = nx;
                    besty = ny;
                }
            }
        }

        x = bestx;
        y = besty;

        visited[x][y] = 1;

        path[count][0] = x;
        path[count][1] = y;

        count++;

        if(count > 399) break;
    }

    return count;
}