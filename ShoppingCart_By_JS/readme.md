#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

#define PI 3.14159265

void rotateOrigin(int x[], int y[], int n, float angle)
{
    float rad = angle * PI / 180.0;
    int i;

    for (i = 0; i < n; i++)
    {
        int newX = x[i] * cos(rad) - y[i] * sin(rad);
        int newY = x[i] * sin(rad) + y[i] * cos(rad);

        x[i] = newX;
        y[i] = newY;
    }
}

void rotateFixedPoint(int x[], int y[], int n,
                      float angle, int h, int k)
{
    float rad = angle * PI / 180.0;
    int i;

    for (i = 0; i < n; i++)
    {
        // Translate fixed point to origin
        int tx = x[i] - h;
        int ty = y[i] - k;

        // Rotate
        int rx = tx * cos(rad) - ty * sin(rad);
        int ry = tx * sin(rad) + ty * cos(rad);

        // Translate back
        x[i] = rx + h;
        y[i] = ry + k;
    }
}

void drawTriangle(int x[], int y[])
{
    line(x[0], y[0], x[1], y[1]);
    line(x[1], y[1], x[2], y[2]);
    line(x[2], y[2], x[0], y[0]);
}

int main()
{
    int gd = DETECT, gm;

    int x[3] = {200, 300, 250};
    int y[3] = {200, 200, 100};

    int xo[3], yo[3];
    int xf[3], yf[3];

    float angle;
    int h, k;

    initgraph(&gd, &gm, "");

    // Draw original triangle
    drawTriangle(x, y);

    printf("Enter rotation angle: ");
    scanf("%f", &angle);

    // Copy original coordinates
    for (int i = 0; i < 3; i++)
    {
        xo[i] = x[i];
        yo[i] = y[i];

        xf[i] = x[i];
        yf[i] = y[i];
    }

    // Rotate about origin
    rotateOrigin(xo, yo, 3, angle);

    // Draw triangle rotated about origin
    drawTriangle(xo, yo);

    // Fixed point
    printf("Enter fixed point (h, k): ");
    scanf("%d %d", &h, &k);

    // Rotate about fixed point
    rotateFixedPoint(xf, yf, 3, angle, h, k);

    // Draw triangle rotated about fixed point
    drawTriangle(xf, yf);

    getch();
    closegraph();

    return 0;
}