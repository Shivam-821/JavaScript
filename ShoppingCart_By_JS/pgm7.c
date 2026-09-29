#include <GL/glut.h>

// Light source properties
GLfloat light_position[] = { 5.0, 8.0, 5.0, 1.0 };  // Positional light
GLfloat light_ambient[]  = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

// Material properties for teapot (shiny ceramic)
GLfloat pot_ambient[]   = { 0.3, 0.1, 0.05, 1.0 };
GLfloat pot_diffuse[]   = { 0.8, 0.3, 0.1, 1.0 };
GLfloat pot_specular[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat pot_shininess[] = { 100.0 };

// Material properties for table (matte wood)
GLfloat table_ambient[]   = { 0.25, 0.15, 0.05, 1.0 };
GLfloat table_diffuse[]   = { 0.55, 0.35, 0.15, 1.0 };
GLfloat table_specular[]  = { 0.2, 0.2, 0.2, 1.0 };
GLfloat table_shininess[] = { 10.0 };

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Enable lighting and depth test
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    // Set light source properties
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Enable color tracking so glColor sets material colors
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Smooth shading
    glShadeModel(GL_SMOOTH);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(4.0, 5.0, 8.0,    // eye position
              0.0, 1.0, 0.0,    // look at point
              0.0, 1.0, 0.0);   // up vector

    // Reposition light after camera setup so it stays in world coords
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // ---- Draw the Table (top) ----
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   table_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   table_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  table_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, table_shininess);

        glTranslatef(0.0, 0.0, 0.0);
        glScalef(4.0, 0.2, 4.0);   // flat, wide top
        glutSolidCube(1.0);
    glPopMatrix();

    // ---- Draw Table Legs ----
    GLfloat legX[4] = { 1.7, -1.7,  1.7, -1.7 };
    GLfloat legZ[4] = { 1.7,  1.7, -1.7, -1.7 };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
            glTranslatef(legX[i], -1.0, legZ[i]);
            glScalef(0.3, 2.0, 0.3);
            glutSolidCube(1.0);
        glPopMatrix();
    }

    // ---- Draw the Teapot on the table ----
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   pot_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   pot_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  pot_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, pot_shininess);

        glTranslatef(0.0, 0.9, 0.0);   // sit on top of table
        glutSolidTeapot(0.8);
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
    glutCreateWindow("Shaded Scene: Teapot on a Table");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}