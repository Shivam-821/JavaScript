#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>

void bresenham(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;
    int e2;

    while (1)
    {
        putpixel(x1, y1, WHITE);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;

        if (e2 > -dy)
        {
            err = err - dy;
            x1 = x1 + sx;
        }

        if (e2 < dx)
        {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    int x1, y1, x2, y2;

    initgraph(&gd, &gm, "");

    printf("Enter x1 y1: ");
    scanf("%d %d", &x1, &y1);

    printf("Enter x2 y2: ");
    scanf("%d %d", &x2, &y2);

    bresenham(x1, y1, x2, y2);

    getch();
    closegraph();

    return 0;
}