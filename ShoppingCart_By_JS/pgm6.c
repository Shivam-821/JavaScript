#include <GL/glut.h>

float angle = 0.0;

void drawCube()
{
    glBegin(GL_QUADS);

    glColor3f(1,0,0);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);

    glColor3f(0,1,0);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);

    glColor3f(0,0,1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,1,1);
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);

    glColor3f(1,1,0);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);

    glColor3f(1,0,1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);

    glColor3f(0,1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0,0,-6);
    glRotatef(angle,1,1,1);

    drawCube();

    glutSwapBuffers();
}

void update(int value)
{
    angle += 2.0;
    if(angle > 360)
        angle -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,0,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,1,100);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("Spinning Colour Cube");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}