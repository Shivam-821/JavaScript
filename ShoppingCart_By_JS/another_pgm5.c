#include <GL/glut.h>
#include <stdio.h>

// Camera position
float camX = 0.0, camY = 0.0, camZ = 5.0;
float fov = 60.0;

// Rotation angles (X, Y, Z)
float rotX = 0.0, rotY = 0.0, rotZ = 0.0;

// Autorotation control
int autoRotate = 1;             // 1 = ON, 0 = OFF
float speedX = 0.5;             // degrees per frame on X
float speedY = 0.5;             // degrees per frame on Y
float speedZ = 0.0;             // degrees per frame on Z (0 = no spin on Z)

// Current rotation mode index
// 0 = all axes, 1 = X only, 2 = Y only, 3 = Z only
int rotMode = 0;

void drawCube()
{
    glBegin(GL_QUADS);

    // Front (RED)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);

    // Back (GREEN)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);

    // Top (BLUE)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    // Bottom (YELLOW)
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);

    // Right (MAGENTA)
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);

    // Left (CYAN)
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

    // Apply rotations on all three axes
    glRotatef(rotX, 1.0, 0.0, 0.0);
    glRotatef(rotY, 0.0, 1.0, 0.0);
    glRotatef(rotZ, 0.0, 0.0, 1.0);

    drawCube();

    glutSwapBuffers();
}

// -------- Autorotation update --------
void update(int value)
{
    if (autoRotate)
    {
        // Apply rotation according to current mode
        switch (rotMode)
        {
            case 0:  // All three axes
                rotX += speedX;
                rotY += speedY;
                rotZ += (speedZ != 0.0) ? speedZ : 0.3;
                break;

            case 1:  // X only
                rotX += speedX * 2.0;
                break;

            case 2:  // Y only
                rotY += speedY * 2.0;
                break;

            case 3:  // Z only
                rotZ += ((speedZ != 0.0) ? speedZ : 0.5) * 2.0;
                break;
        }

        // Wrap angles to keep them small
        if (rotX >= 360.0) rotX -= 360.0;
        if (rotY >= 360.0) rotY -= 360.0;
        if (rotZ >= 360.0) rotZ -= 360.0;
        if (rotX < 0.0)    rotX += 360.0;
        if (rotY < 0.0)    rotY += 360.0;
        if (rotZ < 0.0)    rotZ += 360.0;
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
        case 'u': case 'U': rotZ -= 5.0; break;
        case 'o': case 'O': rotZ += 5.0; break;

        // Zoom
        case '+': fov -= 2.0; if (fov < 10.0)  fov = 10.0;  break;
        case '-': fov += 2.0; if (fov > 120.0) fov = 120.0; break;

        // Toggle autorotation
        case ' ':
            autoRotate = !autoRotate;
            printf("Autorotation: %s\n", autoRotate ? "ON" : "OFF");
            break;

        // Change rotation mode
        case '1': rotMode = 0; printf("Mode: Rotate on ALL axes (X+Y+Z)\n"); break;
        case '2': rotMode = 1; printf("Mode: Rotate on X axis only\n");       break;
        case '3': rotMode = 2; printf("Mode: Rotate on Y axis only\n");       break;
        case '4': rotMode = 3; printf("Mode: Rotate on Z axis only\n");       break;

        // Adjust speeds
        case '[': speedX -= 0.1; speedY -= 0.1;
                  if (speedX < 0.1) speedX = 0.1;
                  if (speedY < 0.1) speedY = 0.1;
                  break;
        case ']': speedX += 0.1; speedY += 0.1;
                  if (speedX > 5.0) speedX = 5.0;
                  if (speedY > 5.0) speedY = 5.0;
                  break;

        // Reset
        case 'r': case 'R':
            camX = 0.0; camY = 0.0; camZ = 5.0;
            rotX = rotY = rotZ = 0.0;
            fov = 60.0;
            speedX = speedY = 0.5; speedZ = 0.3;
            autoRotate = 1;
            rotMode = 0;
            printf("Reset. Autorotation on ALL axes.\n");
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
    printf("\n========== AUTO-ROTATING COLOR CUBE ==========\n");
    printf("  SPACE      : Toggle autorotation ON/OFF\n");
    printf("  1          : Rotate on ALL axes (X + Y + Z)  [default]\n");
    printf("  2          : Rotate on X axis only\n");
    printf("  3          : Rotate on Y axis only\n");
    printf("  4          : Rotate on Z axis only\n");
    printf("  [ / ]      : Slow down / Speed up autorotation\n");
    printf("  W / S      : Camera closer / farther (Z)\n");
    printf("  A / D      : Camera left / right (X)\n");
    printf("  Q / E      : Camera up / down (Y)\n");
    printf("  I / K      : Manual rotate around X\n");
    printf("  J / L      : Manual rotate around Y\n");
    printf("  U / O      : Manual rotate around Z\n");
    printf("  + / -      : Change FOV (Zoom)\n");
    printf("  R          : Reset all\n");
    printf("  ESC        : Quit\n");
    printf("==============================================\n\n");
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
    glutCreateWindow("Cube Autorotating on All Axes");

    init();
    printHelp();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}