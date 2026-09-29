#include <GL/glut.h>

float angleX = 0.0f;
float angleY = 0.0f;
float angleZ = 0.0f;

float speed = 1.0f;
int rotating = 1;

void drawCube()
{
    glBegin(GL_QUADS);

    /* Front */
    glColor3f(1.0, 0.1, 0.1);
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f(-1,  1,  1);

    /* Back */
    glColor3f(0.1, 1.0, 0.1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1,  1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1, -1, -1);

    /* Top */
    glColor3f(0.1, 0.3, 1.0);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1,  1);
    glVertex3f( 1, 1,  1);
    glVertex3f( 1, 1, -1);

    /* Bottom */
    glColor3f(1.0, 1.0, 0.1);
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);
    glVertex3f(-1, -1,  1);

    /* Right */
    glColor3f(1.0, 0.1, 1.0);
    glVertex3f(1, -1, -1);
    glVertex3f(1,  1, -1);
    glVertex3f(1,  1,  1);
    glVertex3f(1, -1,  1);

    /* Left */
    glColor3f(0.1, 1.0, 1.0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    /* Move cube away from camera */
    glTranslatef(0.0, 0.0, -6.0);

    /* Apply rotations */
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);

    drawCube();

    glutSwapBuffers();
}

void update(int value)
{
    if (rotating)
    {
        angleX += speed;
        angleY += speed * 0.8;
        angleZ += speed * 0.5;
    }

    if (angleX >= 360) angleX -= 360;
    if (angleY >= 360) angleY -= 360;
    if (angleZ >= 360) angleZ -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            angleX -= 5;
            break;

        case GLUT_KEY_DOWN:
            angleX += 5;
            break;

        case GLUT_KEY_LEFT:
            angleY -= 5;
            break;

        case GLUT_KEY_RIGHT:
            angleY += 5;
            break;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '+':
        case '=':
            speed += 0.5f;

            if (speed > 10.0f)
                speed = 10.0f;
            break;

        case '-':
        case '_':
            speed -= 0.5f;

            if (speed < 0.0f)
                speed = 0.0f;
            break;

        case 'z':
            angleZ += 5;
            break;

        case 'Z':
            angleZ -= 5;
            break;

        case ' ':
            rotating = !rotating;
            break;

        case 'r':
        case 'R':
            angleX = 0.0f;
            angleY = 0.0f;
            angleZ = 0.0f;
            speed = 1.0f;
            rotating = 1;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.03, 0.03, 0.06, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 1.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0,
                   (float)width / height,
                   1.0,
                   100.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Interactive Colour Cube");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}