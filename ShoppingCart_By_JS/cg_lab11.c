#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    float x, y;
} Point;

Point poly[MAX];
int n = 0;
int filled = 0;

void scanLineFill()
{
    int i, j;
    float ymin = poly[0].y, ymax = poly[0].y;
    float xint[MAX], temp;

    for (i = 1; i < n; i++) {
        if (poly[i].y < ymin) ymin = poly[i].y;
        if (poly[i].y > ymax) ymax = poly[i].y;
    }

    glColor3f(0.2, 0.7, 0.3);

    for (int y = (int)ymin; y <= (int)ymax; y++) {
        int count = 0;

        for (i = 0; i < n; i++) {
            j = (i + 1) % n;

            if ((poly[i].y <= y && poly[j].y > y) ||
                (poly[j].y <= y && poly[i].y > y)) {

                xint[count++] = poly[i].x +
                    (y - poly[i].y) *
                    (poly[j].x - poly[i].x) /
                    (poly[j].y - poly[i].y);
            }
        }

        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                if (xint[i] > xint[j]) {
                    temp = xint[i];
                    xint[i] = xint[j];
                    xint[j] = temp;
                }
            }
        }

        glBegin(GL_LINES);
        for (i = 0; i < count - 1; i += 2) {
            glVertex2f(xint[i], y);
            glVertex2f(xint[i + 1], y);
        }
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (n > 0) {
        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < n; i++)
            glVertex2f(poly[i].x, poly[i].y);
        glEnd();

        if (filled)
            scanLineFill();
    }

    glFlush();
}

void setPolygon(int choice)
{
    n = 0;
    filled = 0;

    switch (choice) {
        case 1:
            n = 3;
            poly[0] = (Point){150, 100};
            poly[1] = (Point){350, 100};
            poly[2] = (Point){250, 300};
            break;

        case 2:
            n = 4;
            poly[0] = (Point){150, 100};
            poly[1] = (Point){350, 100};
            poly[2] = (Point){350, 300};
            poly[3] = (Point){150, 300};
            break;

        case 3:
            n = 5;
            poly[0] = (Point){250, 350};
            poly[1] = (Point){350, 250};
            poly[2] = (Point){310, 120};
            poly[3] = (Point){190, 120};
            poly[4] = (Point){150, 250};
            break;

        case 4:
            exit(0);
    }

    glutPostRedisplay();
}

void menu(int choice)
{
    if (choice == 5) {
        filled = 1;
        glutPostRedisplay();
    } else {
        setPolygon(choice);
    }
}

void createMenu()
{
    glutCreateMenu(menu);
    glutAddMenuEntry("Triangle", 1);
    glutAddMenuEntry("Rectangle", 2);
    glutAddMenuEntry("Pentagon", 3);
    glutAddMenuEntry("Fill Polygon", 5);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 400);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan-Line Polygon Filling");

    init();
    glutDisplayFunc(display);
    createMenu();

    printf("Right-click inside the window to open the menu.\n");

    glutMainLoop();
    return 0;
}