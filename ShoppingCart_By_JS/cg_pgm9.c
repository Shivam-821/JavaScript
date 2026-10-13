#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define LEFT   1
#define RIGHT  2
#define BOTTOM 4
#define TOP    8

float xmin = 100, ymin = 100;
float xmax = 400, ymax = 300;
float x1, y1, x2, y2;
float cx1, cy1, cx2, cy2;
int accepted;

int computeCode(float x, float y)
{
    int code = 0;

    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;

    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;

    return code;
}

int cohenSutherland(float *ax, float *ay,
                    float *bx, float *by)
{
    int code1 = computeCode(*ax, *ay);
    int code2 = computeCode(*bx, *by);

    while (1)
    {
        if ((code1 | code2) == 0)
            return 1;

        if ((code1 & code2) != 0)
            return 0;

        int outcode = code1 ? code1 : code2;
        float x, y;

        if (outcode & TOP)
        {
            if (*by == *ay)
                return 0;

            x = *ax + (*bx - *ax) *
                (ymax - *ay) / (*by - *ay);
            y = ymax;
        }
        else if (outcode & BOTTOM)
        {
            if (*by == *ay)
                return 0;

            x = *ax + (*bx - *ax) *
                (ymin - *ay) / (*by - *ay);
            y = ymin;
        }
        else if (outcode & RIGHT)
        {
            if (*bx == *ax)
                return 0;

            y = *ay + (*by - *ay) *
                (xmax - *ax) / (*bx - *ax);
            x = xmax;
        }
        else
        {
            if (*bx == *ax)
                return 0;

            y = *ay + (*by - *ay) *
                (xmin - *ax) / (*bx - *ax);
            x = xmin;
        }

        if (outcode == code1)
        {
            *ax = x;
            *ay = y;
            code1 = computeCode(*ax, *ay);
        }
        else
        {
            *bx = x;
            *by = y;
            code2 = computeCode(*bx, *by);
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glColor3f(0.5, 0.5, 0.5);

    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    if (accepted)
    {
        glColor3f(0.0, 0.6, 0.0);
        glLineWidth(3.0);

        glBegin(GL_LINES);
            glVertex2f(cx1, cy1);
            glVertex2f(cx2, cy2);
        glEnd();
    }

    glFlush();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 400);
}

int main(int argc, char **argv)
{
    printf("Enter the first endpoint (x1 y1): ");
    if (scanf("%f %f", &x1, &y1) != 2)
        return 1;

    printf("Enter the second endpoint (x2 y2): ");
    if (scanf("%f %f", &x2, &y2) != 2)
        return 1;

    cx1 = x1;
    cy1 = y1;
    cx2 = x2;
    cy2 = y2;

    accepted = cohenSutherland(&cx1, &cy1, &cx2, &cy2);

    if (accepted)
        printf("Line accepted after clipping.\n");
    else
        printf("Line rejected: outside clipping window.\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 560);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}