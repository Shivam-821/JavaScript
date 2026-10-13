#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef GLfloat Point[3];

Point v[4] = {
    {-1.0, -1.0, -1.0},
    { 1.0, -1.0,  1.0},
    {-1.0,  1.0,  1.0},
    { 1.0,  1.0, -1.0}
};

int depth;
float angleX = 20.0f;
float angleY = 30.0f;

void triangle(Point a, Point b, Point c)
{
    glBegin(GL_TRIANGLES);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
}

void tetrahedron(Point a, Point b, Point c, Point d)
{
    glColor3f(1.0, 0.0, 0.0);
    triangle(a, b, c);

    glColor3f(0.0, 1.0, 0.0);
    triangle(a, d, b);

    glColor3f(0.0, 0.0, 1.0);
    triangle(a, c, d);

    glColor3f(1.0, 1.0, 0.0);
    triangle(b, d, c);
}

void divideTetrahedron(Point a, Point b,
                       Point c, Point d, int m)
{
    if (m == 0)
    {
        tetrahedron(a, b, c, d);
        return;
    }

    Point ab, ac, ad, bc, bd, cd;

    for (int i = 0; i < 3; i++)
    {
        ab[i] = (a[i] + b[i]) / 2.0f;
        ac[i] = (a[i] + c[i]) / 2.0f;
        ad[i] = (a[i] + d[i]) / 2.0f;
        bc[i] = (b[i] + c[i]) / 2.0f;
        bd[i] = (b[i] + d[i]) / 2.0f;
        cd[i] = (c[i] + d[i]) / 2.0f;
    }

    divideTetrahedron(a, ab, ac, ad, m - 1);
    divideTetrahedron(ab, b, bc, bd, m - 1);
    divideTetrahedron(ac, bc, c, cd, m - 1);
    divideTetrahedron(ad, bd, cd, d, m - 1);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    divideTetrahedron(v[0], v[1], v[2], v[3], depth);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0,
                   (GLdouble)w / (GLdouble)h,
                   1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
            angleY -= 5.0f;
            break;

        case 'd':
        case 'D':
            angleY += 5.0f;
            break;

        case 'w':
        case 'W':
            angleX -= 5.0f;
            break;

        case 's':
        case 'S':
            angleX += 5.0f;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
    printf("Enter the number of recursive steps (0-8): ");

    if (scanf("%d", &depth) != 1 || depth < 0 || depth > 8)
    {
        printf("Invalid input. Enter a value from 0 to 8.\n");
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Sierpinski Gasket");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}