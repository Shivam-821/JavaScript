#include <GL/glut.h>

// Light source position (x, y, z, w) - w=1.0 for positional light
GLfloat light_position[] = { 2.0f, 4.0f, 3.0f, 1.0f };

// Light properties
GLfloat light_ambient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f }; // Bright white light
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

// Teapot material properties (Shiny Colorful Material)
GLfloat teapot_ambient[]   = { 0.8f, 0.1f, 0.2f, 1.0f }; // Deep Red
GLfloat teapot_diffuse[]   = { 0.9f, 0.2f, 0.3f, 1.0f };
GLfloat teapot_specular[]  = { 0.7f, 0.7f, 0.7f, 1.0f }; // Highlights
GLfloat teapot_shininess[] = { 50.0f };                 // High shininess

// Table top material properties (Wood/Matte Brown Tone)
GLfloat table_ambient[]    = { 0.4f, 0.2f, 0.1f, 1.0f };
GLfloat table_diffuse[]    = { 0.6f, 0.3f, 0.15f, 1.0f };
GLfloat table_specular[]   = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat table_shininess[]  = { 5.0f };

// Table leg material properties (Metallic Dark Gray)
GLfloat leg_ambient[]      = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat leg_diffuse[]      = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat leg_specular[]     = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat leg_shininess[]    = { 32.0f };

void init(void) {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Dark background
    glEnable(GL_DEPTH_TEST);               // Enable Z-buffer depth testing
    glEnable(GL_LIGHTING);                 // Enable OpenGL lighting
    glEnable(GL_LIGHT0);                   // Enable Light 0
    glEnable(GL_NORMALIZE);                // Normalize surface normals for proper lighting calculation
    glShadeModel(GL_SMOOTH);               // Smooth shading (Gouraud)

    // Configure Light 0
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void drawTableLeg(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.1f, 1.0f, 0.1f); // Scale cube to make a tall vertical leg
    glutSolidCube(1.0);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up camera view (LookAt)
    gluLookAt(3.0, 3.0, 5.0,   // Camera position
              0.0, 0.0, 0.0,   // Pointing target (Center)
              0.0, 1.0, 0.0);  // Up vector

    // --- 1. DRAW TABLE TOP ---
    glMaterialfv(GL_FRONT, GL_AMBIENT, table_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, table_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, table_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, table_shininess);

    glPushMatrix();
    glTranslatef(0.0f, -0.05f, 0.0f);
    glScalef(3.0f, 0.1f, 2.0f); // Wide, flat tabletop surface
    glutSolidCube(1.0);
    glPopMatrix();

    // --- 2. DRAW TABLE LEGS ---
    glMaterialfv(GL_FRONT, GL_AMBIENT, leg_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, leg_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, leg_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, leg_shininess);

    drawTableLeg( 1.35f, -0.55f,  0.85f);
    drawTableLeg(-1.35f, -0.55f,  0.85f);
    drawTableLeg( 1.35f, -0.55f, -0.85f);
    drawTableLeg(-1.35f, -0.55f, -0.85f);

    // --- 3. DRAW COLORFUL SHADED TEAPOT ---
    glMaterialfv(GL_FRONT, GL_AMBIENT, teapot_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapot_shininess);

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Position teapot sitting on top of the table
    glutSolidTeapot(0.65);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shaded Scene: Teapot on Table");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
