#include <GL/glut.h>
#include <stdlib.h>

// Global variables for rotation
static float rotateX = 20.0f;
static float rotateY = 30.0f;

// Light properties
GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPosition[] = { 5.0f, 8.0f, 5.0f, 1.0f }; // Positional light

// Material properties for the teapot
GLfloat potAmbient[] = { 0.3f, 0.1f, 0.1f, 1.0f };
GLfloat potDiffuse[] = { 0.9f, 0.2f, 0.2f, 1.0f };
GLfloat potSpecular[] = { 1.0f, 0.8f, 0.8f, 1.0f };
GLfloat potShininess[] = { 80.0f };

// Material properties for the table
GLfloat tableAmbient[] = { 0.2f, 0.15f, 0.1f, 1.0f };
GLfloat tableDiffuse[] = { 0.6f, 0.45f, 0.3f, 1.0f };
GLfloat tableSpecular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat tableShininess[] = { 30.0f };

void init(void)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Dark background
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    
    // Set light properties
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // Enable color material for easy color changes
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    // Enable smooth shading
    glShadeModel(GL_SMOOTH);
}

void drawTable(void)
{
    // Set table material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, tableAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tableDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tableSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, tableShininess);
    
    // Draw table top
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(4.0f, 0.2f, 3.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Draw table legs
    // Front left leg
    glPushMatrix();
    glTranslatef(-1.7f, -2.0f, 1.2f);
    glScalef(0.2f, 2.0f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Front right leg
    glPushMatrix();
    glTranslatef(1.7f, -2.0f, 1.2f);
    glScalef(0.2f, 2.0f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Back left leg
    glPushMatrix();
    glTranslatef(-1.7f, -2.0f, -1.2f);
    glScalef(0.2f, 2.0f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Back right leg
    glPushMatrix();
    glTranslatef(1.7f, -2.0f, -1.2f);
    glScalef(0.2f, 2.0f, 0.2f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawColorfulTeapot(void)
{
    // Draw teapot body with red color
    glColor3f(0.9f, 0.2f, 0.2f); // Red
    glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.0f);
    glScalef(1.0f, 0.8f, 1.0f);
    glutSolidTeapot(0.8);
    glPopMatrix();
    
    // Add colorful decorations using small spheres
    // Blue sphere on top (lid knob)
    glColor3f(0.2f, 0.3f, 0.9f); // Blue
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    
    // Green spheres around the body
    glColor3f(0.2f, 0.8f, 0.2f); // Green
    for (int i = 0; i < 8; i++) {
        float angle = i * 45.0f * 3.14159f / 180.0f;
        float x = 0.7f * cos(angle);
        float z = 0.7f * sin(angle);
        
        glPushMatrix();
        glTranslatef(x, -0.3f, z);
        glutSolidSphere(0.08, 15, 15);
        glPopMatrix();
    }
    
    // Yellow band around the middle
    glColor3f(0.9f, 0.9f, 0.2f); // Yellow
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidTorus(0.05, 0.75, 10, 30);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(6.0, 5.0, 8.0,  // Eye position
              0.0, 0.0, 0.0,  // Look at point
              0.0, 1.0, 0.0); // Up vector
    
    // Apply rotation
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    
    // Update light position (in world space)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // Draw the table
    drawTable();
    
    // Draw the colorful teapot on top of the table
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawColorfulTeapot();
    glPopMatrix();
    
    // Draw a simple floor
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-10.0f, -3.0f, -10.0f);
        glVertex3f(10.0f, -3.0f, -10.0f);
        glVertex3f(10.0f, -3.0f, 10.0f);
        glVertex3f(-10.0f, -3.0f, 10.0f);
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'x':
            rotateX += 5.0f;
            glutPostRedisplay();
            break;
        case 'X':
            rotateX -= 5.0f;
            glutPostRedisplay();
            break;
        case 'y':
            rotateY += 5.0f;
            glutPostRedisplay();
            break;
        case 'Y':
            rotateY -= 5.0f;
            glutPostRedisplay();
            break;
    }
}

void specialKeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            rotateX -= 5.0f;
            break;
        case GLUT_KEY_DOWN:
            rotateX += 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotateY -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            rotateY += 5.0f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Colorful Teapot on Table - OpenGL Shading");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    
    printf("Controls:\n");
    printf("- Arrow keys or X/x, Y/y to rotate the scene\n");
    printf("- ESC to exit\n");
    
    glutMainLoop();
    return 0;
}