#include <GL/glut.h>

GLfloat light_pos[] = {2.0, 5.0, 3.0, 1.0};
GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

void setMaterial(float r, float g, float b)
{
    GLfloat material[] = {r, g, b, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
}

void drawTable()
{
    setMaterial(0.45, 0.25, 0.1);

    /* Table top */
    glPushMatrix();
    glTranslatef(0, -1.5, 0);
    glScalef(4.0, 0.4, 3.2);
    glutSolidCube(1);
    glPopMatrix();

    /* Front-left leg */
    glPushMatrix();
    glTranslatef(-2.7, -3.0, 2.0);
    glScalef(0.4, 3.0, 0.4);
    glutSolidCube(1);
    glPopMatrix();

    /* Front-right leg */
    glPushMatrix();
    glTranslatef(2.7, -3.0, 2.0);
    glScalef(0.4, 3.0, 0.4);
    glutSolidCube(1);
    glPopMatrix();

    /* Back-left leg */
    glPushMatrix();
    glTranslatef(-2.7, -3.0, -2.0);
    glScalef(0.4, 3.0, 0.4);
    glutSolidCube(1);
    glPopMatrix();

    /* Back-right leg */
    glPushMatrix();
    glTranslatef(2.7, -3.0, -2.0);
    glScalef(0.4, 3.0, 0.4);
    glutSolidCube(1);
    glPopMatrix();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(7,5,8, 0,0,0, 0,1,0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    drawTable();

    setMaterial(0.7, 0.3, 0.1);

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(-20, 0, 1, 0);
    glutSolidTeapot(1.2);
    glPopMatrix();

    glutSwapBuffers();
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glShadeModel(GL_SMOOTH);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700,600);
    glutCreateWindow("Shaded Teapot Scene");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}