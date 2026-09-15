#include <GL/glut.h>
#include <stdio.h>

// Camera position and rotation angles
float camX = 0.0, camY = 0.0, camZ = 5.0;
float rotX = 0.0, rotY = 0.0;
float fov = 60.0;    // Field of view for perspective

// Cube rotation
float cubeAngle = 0.0;

void drawCube()
{
    glBegin(GL_QUADS);

    // Front face (RED)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);

    // Back face (GREEN)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);

    // Top face (BLUE)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    // Bottom face (YELLOW)
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);

    // Right face (MAGENTA)
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);

    // Left face (CYAN)
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set camera position (eye, center, up)
    gluLookAt(camX, camY, camZ,    // Eye position
              0.0, 0.0, 0.0,       // Look at origin
              0.0, 1.0, 0.0);      // Up vector

    // Apply user rotations (to rotate the whole scene)
    glRotatef(rotX, 1.0, 0.0, 0.0);
    glRotatef(rotY, 0.0, 1.0, 0.0);

    // Draw the color cube
    drawCube();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Perspective projection
    gluPerspective(fov, (float)w / h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Move camera closer / farther (Z-axis)
        case 'w': case 'W': camZ -= 0.3; break;
        case 's': case 'S': camZ += 0.3; break;

        // Move camera left / right (X-axis)
        case 'a': case 'A': camX -= 0.3; break;
        case 'd': case 'D': camX += 0.3; break;

        // Move camera up / down (Y-axis)
        case 'q': case 'Q': camY += 0.3; break;
        case 'e': case 'E': camY -= 0.3; break;

        // Rotate scene
        case 'i': case 'I': rotX -= 5.0; break;
        case 'k': case 'K': rotX += 5.0; break;
        case 'j': case 'J': rotY -= 5.0; break;
        case 'l': case 'L': rotY += 5.0; break;

        // Zoom via FOV (perspective effect)
        case '+': fov -= 2.0; if (fov < 10.0) fov = 10.0; break;
        case '-': fov += 2.0; if (fov > 120.0) fov = 120.0; break;

        // Reset
        case 'r': case 'R':
            camX = 0.0; camY = 0.0; camZ = 5.0;
            rotX = 0.0; rotY = 0.0;
            fov = 60.0;
            break;

        case 27: exit(0);  // ESC to quit
    }
    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:    camY += 0.3; break;
        case GLUT_KEY_DOWN:  camY -= 0.3; break;
        case GLUT_KEY_LEFT:  camX -= 0.3; break;
        case GLUT_KEY_RIGHT: camX += 0.3; break;
    }
    glutPostRedisplay();
}

void printHelp()
{
    printf("\n========== COLOR CUBE - CONTROLS ==========\n");
    printf("  W / S      : Move camera closer / farther (Z)\n");
    printf("  A / D      : Move camera left / right (X)\n");
    printf("  Q / E      : Move camera up / down (Y)\n");
    printf("  I / K      : Rotate scene around X-axis\n");
    printf("  J / L      : Rotate scene around Y-axis\n");
    printf("  + / -      : Change FOV (Zoom effect)\n");
    printf("  R          : Reset all\n");
    printf("  ESC        : Quit\n");
    printf("===========================================\n\n");
}

void init()
{
    glEnable(GL_DEPTH_TEST);       // Enable depth testing
    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Color Cube with Perspective Camera");

    init();
    printHelp();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}