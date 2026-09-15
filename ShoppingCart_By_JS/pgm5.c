#include <GL/glut.h>

// Camera position
float eyeX = 3.0, eyeY = 3.0, eyeZ = 3.0;

// Draw the colored cube
void drawCube()
{
    glBegin(GL_QUADS);

    // Front - Red
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    // Back - Green
    glColor3f(0, 1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);

    // Left - Blue
    glColor3f(0, 0, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);

    // Right - Yellow
    glColor3f(1, 1, 0);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);

    // Top - Cyan
    glColor3f(0, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);

    // Bottom - Magenta
    glColor3f(1, 0, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera view
    gluLookAt(eyeX, eyeY, eyeZ,
              0, 0, 0,
              0, 1, 0);

    drawCube();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float)w / (float)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w': eyeY += 0.2; break;
        case 's': eyeY -= 0.2; break;
        case 'a': eyeX -= 0.2; break;
        case 'd': eyeX += 0.2; break;
        case 'z': eyeZ -= 0.2; break;
        case 'x': eyeZ += 0.2; break;
        case 27: exit(0);
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Color Cube with Perspective View");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}