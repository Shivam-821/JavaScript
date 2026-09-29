#include <GL/glut.h>

// Light source properties
GLfloat light_position[] = { 5.0, 8.0, 5.0, 1.0 };  // Positional light
GLfloat light_ambient[]  = { 0.3, 0.3, 0.35, 1.0 };
GLfloat light_diffuse[]  = { 1.0, 0.95, 0.85, 1.0 }; // slightly warm
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

// Material properties for teapot (shiny ceramic) - TEAL/BLUE
GLfloat pot_ambient[]   = { 0.0, 0.25, 0.3, 1.0 };
GLfloat pot_diffuse[]   = { 0.0, 0.65, 0.75, 1.0 };
GLfloat pot_specular[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat pot_shininess[] = { 120.0 };

// Material properties for table top (wood)
GLfloat table_ambient[]   = { 0.35, 0.18, 0.05, 1.0 };
GLfloat table_diffuse[]   = { 0.65, 0.35, 0.12, 1.0 };
GLfloat table_specular[]  = { 0.25, 0.15, 0.05, 1.0 };
GLfloat table_shininess[] = { 15.0 };

// Leg material (dark wood)
GLfloat leg_ambient[]   = { 0.2, 0.1, 0.03, 1.0 };
GLfloat leg_diffuse[]   = { 0.4, 0.2, 0.05, 1.0 };
GLfloat leg_specular[]  = { 0.2, 0.1, 0.05, 1.0 };
GLfloat leg_shininess[] = { 10.0 };

void init(void)
{
    // Sky-blue background instead of black
    glClearColor(0.35, 0.55, 0.75, 1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    // Set light source properties
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
}

void drawFloor(void)
{
    // A colored floor plane so colors reflect nicely
    GLfloat floor_ambient[]   = { 0.15, 0.3, 0.15, 1.0 };
    GLfloat floor_diffuse[]   = { 0.25, 0.55, 0.25, 1.0 };
    GLfloat floor_specular[]  = { 0.0, 0.0, 0.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   floor_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   floor_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  floor_specular);

    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-10.0, -2.0, -10.0);
        glVertex3f( 10.0, -2.0, -10.0);
        glVertex3f( 10.0, -2.0,  10.0);
        glVertex3f(-10.0, -2.0,  10.0);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(4.5, 5.0, 8.0,   // eye
              0.0, 1.0, 0.0,   // look at
              0.0, 1.0, 0.0);  // up

    // Re-specify light position after camera setup
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // ---- Floor ----
    drawFloor();

    // ---- Table top (brown wood) ----
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   table_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   table_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  table_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, table_shininess);

        glTranslatef(0.0, 0.0, 0.0);
        glScalef(4.0, 0.2, 4.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // ---- Table legs (dark brown) ----
    glMaterialfv(GL_FRONT, GL_AMBIENT,   leg_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   leg_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  leg_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, leg_shininess);

    GLfloat legX[4] = { 1.7, -1.7,  1.7, -1.7 };
    GLfloat legZ[4] = { 1.7,  1.7, -1.7, -1.7 };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
            glTranslatef(legX[i], -1.0, legZ[i]);
            glScalef(0.3, 2.0, 0.3);
            glutSolidCube(1.0);
        glPopMatrix();
    }

    // ---- Teapot (colorful ceramic) ----
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   pot_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   pot_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  pot_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, pot_shininess);

        glTranslatef(0.0, 0.9, 0.0);
        glutSolidTeapot(0.8);
    glPopMatrix();

    // ---- A small colored sphere (orange fruit) next to the teapot ----
    GLfloat fruit_ambient[]   = { 0.5, 0.2, 0.0, 1.0 };
    GLfloat fruit_diffuse[]   = { 1.0, 0.55, 0.0, 1.0 };
    GLfloat fruit_specular[]  = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat fruit_shininess[] = { 60.0 };

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   fruit_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   fruit_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  fruit_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, fruit_shininess);

        glTranslatef(1.0, 0.3, 0.8);
        glutSolidSphere(0.3, 32, 32);
    glPopMatrix();

    // ---- Another fruit (red apple) on the other side ----
    GLfloat apple_ambient[]   = { 0.4, 0.0, 0.0, 1.0 };
    GLfloat apple_diffuse[]   = { 0.9, 0.1, 0.1, 1.0 };
    GLfloat apple_specular[]  = { 1.0, 0.9, 0.9, 1.0 };
    GLfloat apple_shininess[] = { 80.0 };

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   apple_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   apple_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  apple_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, apple_shininess);

        glTranslatef(-1.0, 0.25, 0.8);
        glutSolidSphere(0.25, 32, 32);
    glPopMatrix();

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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Colorful Shaded Scene: Teapot on a Table");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}