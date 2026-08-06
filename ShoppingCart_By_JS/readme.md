#include <GL/glut.h>
#include <math.h>

int x1 = 50, y1 = 50;
int x2 = 400, y2 = 300;

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void DDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float Xinc = (float)dx / steps;
    float Yinc = (float)dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        drawPixel(round(x), round(y));
        x += Xinc;
        y += Yinc;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    DDA(x1, y1, x2, y2);

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}