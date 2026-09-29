#include <GL/glut.h>
#include <math.h>

// Light source properties
GLfloat light_position[] = { 5.0, 8.0, 5.0, 1.0 };
GLfloat light_ambient[]  = { 0.3, 0.3, 0.35, 1.0 };
GLfloat light_diffuse[]  = { 1.0, 0.95, 0.85, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

// Table top material (wood)
GLfloat table_ambient[]   = { 0.35, 0.18, 0.05, 1.0 };
GLfloat table_diffuse[]   = { 0.65, 0.35, 0.12, 1.0 };
GLfloat table_specular[]  = { 0.25, 0.15, 0.05, 1.0 };
GLfloat table_shininess[] = { 15.0 };

// Leg material (dark wood)
GLfloat leg_ambient[]   = { 0.2, 0.1, 0.03, 1.0 };
GLfloat leg_diffuse[]   = { 0.4, 0.2, 0.05, 1.0 };
GLfloat leg_specular[]  = { 0.2, 0.1, 0.05, 1.0 };
GLfloat leg_shininess[] = { 10.0 };

// Rainbow color bands for the teapot (bottom to top)
#define NUM_BANDS 8
GLfloat rainbow[NUM_BANDS][3] = {
    { 0.85, 0.10, 0.10 },  // red
    { 0.95, 0.50, 0.05 },  // orange
    { 0.95, 0.90, 0.10 },  // yellow
    { 0.15, 0.80, 0.20 },  // green
    { 0.10, 0.70, 0.85 },  // cyan
    { 0.15, 0.25, 0.85 },  // blue
    { 0.55, 0.15, 0.80 },  // indigo
    { 0.85, 0.20, 0.60 }   // magenta
};

// Vertical range of the teapot (from -0.8 to +0.8 around its center)
#define POT_RADIUS 0.8
#define POT_BOTTOM (-0.8)
#define POT_TOP    (0.8)

void init(void)
{
    glClearColor(0.35, 0.55, 0.75, 1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    // Enable one clipping plane (we'll set its equation per band)
    glEnable(GL_CLIP_PLANE0);
}

void drawFloor(void)
{
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

// Draw the colorful teapot using clipping planes for horizontal bands
void drawColorfulTeapot(void)
{
    GLfloat band_height = (POT_TOP - POT_BOTTOM) / NUM_BANDS;

    // Common shiny ceramic specular for all bands
    GLfloat pot_specular[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pot_shininess[] = { 120.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR,  pot_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, pot_shininess);

    for (int i = 0; i < NUM_BANDS; i++) {
        GLfloat y_low  = POT_BOTTOM + i * band_height;
        GLfloat y_high = y_low + band_height;

        // Set material color for this band (used as ambient + diffuse)
        GLfloat amb[] = { rainbow[i][0] * 0.3,
                          rainbow[i][1] * 0.3,
                          rainbow[i][2] * 0.3, 1.0 };
        GLfloat dif[] = { rainbow[i][0],
                          rainbow[i][1],
                          rainbow[i][2], 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

        // Lower clip plane: keep points with y >= y_low  -> plane (0, 1, 0, -y_low)
        GLdouble eqLow[4]  = { 0.0,  1.0, 0.0, -y_low };
        glClipPlane(GL_CLIP_PLANE0, eqLow);
        glEnable(GL_CLIP_PLANE0);

        // We need TWO clipping planes for a band. Enable plane 1 as upper cut.
        GLdouble eqHigh[4] = { 0.0, -1.0, 0.0,  y_high };
        glClipPlane(GL_CLIP_PLANE1, eqHigh);
        glEnable(GL_CLIP_PLANE1);

        glutSolidTeapot(POT_RADIUS);
    }

    // Disable both clip planes after drawing
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(4.5, 5.0, 8.0,
              0.0, 1.0, 0.0,
              0.0, 1.0, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Floor
    drawFloor();

    // ---- Table top ----
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   table_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   table_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  table_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, table_shininess);

        glScalef(4.0, 0.2, 4.0);
        glutSolidCube(1.0);
    glPopMatrix();

    // ---- Table legs ----
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

    // ---- Colorful teapot on the table ----
    glPushMatrix();
        glTranslatef(0.0, 0.9, 0.0);   // sit on table
        drawColorfulTeapot();
    glPopMatrix();

    // ---- Red apple on the left ----
    GLfloat apple_ambient[]   = { 0.4, 0.0, 0.0, 1.0 };
    GLfloat apple_diffuse[]   = { 0.9, 0.1, 0.1, 1.0 };
    GLfloat apple_specular[]  = { 1.0, 0.9, 0.9, 1.0 };
    GLfloat apple_shininess[] = { 80.0 };

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   apple_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   apple_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  apple_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, apple_shininess);

        glTranslatef(-1.2, 0.25, 0.8);
        glutSolidSphere(0.25, 32, 32);
    glPopMatrix();

    // ---- Orange on the right ----
    GLfloat orange_ambient[]   = { 0.5, 0.2, 0.0, 1.0 };
    GLfloat orange_diffuse[]   = { 1.0, 0.55, 0.0, 1.0 };
    GLfloat orange_specular[]  = { 1.0, 1.0, 0.8, 1.0 };
    GLfloat orange_shininess[] = { 60.0 };

    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT,   orange_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   orange_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  orange_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, orange_shininess);

        glTranslatef(1.2, 0.3, 0.8);
        glutSolidSphere(0.3, 32, 32);
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
    glutCreateWindow("Rainbow Teapot on a Table");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}