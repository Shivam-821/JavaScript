#include <GL/glut.h>
#include <stdio.h>

// Camera position and rotation angles
float camX = 0.0, camY = 0.0, camZ = 5.0;
float rotX = 0.0, rotY = 0.0;
float fov = 60.0;

// Autorotation
int autoRotate = 1;          // 1 = ON, 0 = OFF
float autoSpeed = 0.5;       // Degrees per frame

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

    // Camera
    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Apply user / autorotation
    glRotatef(rotX, 1.0, 0.0, 0.0);
    glRotatef(rotY, 0.0, 1.0, 0.0);

    drawCube();

    glutSwapBuffers();
}

// -------- Autorotation update (called ~60 times/sec) --------
void update(int value)
{
    if (autoRotate)
    {
        rotY += autoSpeed;                       // Spin around Y-axis
        if (rotY >= 360.0) rotY -= 360.0;

        // Optional: also tilt slightly for a nicer 3D look
        // rotX += autoSpeed * 0.3;
        // if (rotX >= 360.0) rotX -= 360.0;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);   // ~60 FPS
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (float)w / h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        // Camera move
        case 'w': case 'W': camZ -= 0.3; break;
        case 's': case 'S': camZ += 0.3; break;
        case 'a': case 'A': camX -= 0.3; break;
        case 'd': case 'D': camX += 0.3; break;
        case 'q': case 'Q': camY += 0.3; break;
        case 'e': case 'E': camY -= 0.3; break;

        // Manual rotation
        case 'i': case 'I': rotX -= 5.0; break;
        case 'k': case 'K': rotX += 5.0; break;
        case 'j': case 'J': rotY -= 5.0; break;
        case 'l': case 'L': rotY += 5.0; break;

        // Zoom
        case '+': fov -= 2.0; if (fov < 10.0)  fov = 10.0;  break;
        case '-': fov += 2.0; if (fov > 120.0) fov = 120.0; break;

        // Autorotation toggle
        case ' ':                                // SPACE = toggle
            autoRotate = !autoRotate;
            printf("Autorotation: %s\n", autoRotate ? "ON" : "OFF");
            break;

        // Adjust autorotation speed
        case '[': autoSpeed -= 0.1; if (autoSpeed < 0.1) autoSpeed = 0.1; break;
        case ']': autoSpeed += 0.1; if (autoSpeed > 5.0) autoSpeed = 5.0; break;

        // Reset
        case 'r': case 'R':
            camX = 0.0; camY = 0.0; camZ = 5.0;
            rotX = 0.0; rotY = 0.0;
            fov = 60.0;
            autoSpeed = 0.5;
            autoRotate = 1;
            printf("Reset. Autorotation ON.\n");
            break;

        case 27: exit(0);
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
    printf("  SPACE      : Toggle autorotation ON/OFF\n");
    printf("  [ / ]      : Decrease / Increase autorotation speed\n");
    printf("  W / S      : Move camera closer / farther (Z)\n");
    printf("  A / D      : Move camera left / right (X)\n");
    printf("  Q / E      : Move camera up / down (Y)\n");
    printf("  I / K      : Manual rotate around X-axis\n");
    printf("  J / L      : Manual rotate around Y-axis\n");
    printf("  + / -      : Change FOV (Zoom effect)\n");
    printf("  R          : Reset all\n");
    printf("  ESC        : Quit\n");
    printf("===========================================\n\n");
}

void init()
{
    glEnable(GL_DEPTH_TEST);
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
    glutCreateWindow("Auto-Rotating Color Cube");

    init();
    printHelp();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, update, 0);   // Start autorotation timer

    glutMainLoop();
    return 0;
}