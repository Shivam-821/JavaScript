#include <GL/glut.h>
#include <math.h>

/* ---------- LIGHT ---------- */
GLfloat light_position[] = { 5.0, 8.0, 6.0, 1.0 };
GLfloat light_ambient[]  = { 0.25, 0.25, 0.30, 1.0 };
GLfloat light_diffuse[]  = { 1.0, 0.95, 0.90, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

/* ---------- TABLE TOP (rich mahogany) ---------- */
GLfloat table_ambient[]   = { 0.25, 0.10, 0.03, 1.0 };
GLfloat table_diffuse[]   = { 0.55, 0.22, 0.08, 1.0 };
GLfloat table_specular[]  = { 0.55, 0.30, 0.15, 1.0 };
GLfloat table_shininess[] = { 60.0 };

/* ---------- LEGS (dark walnut) ---------- */
GLfloat leg_ambient[]   = { 0.12, 0.05, 0.02, 1.0 };
GLfloat leg_diffuse[]   = { 0.30, 0.12, 0.04, 1.0 };
GLfloat leg_specular[]  = { 0.30, 0.15, 0.08, 1.0 };
GLfloat leg_shininess[] = { 40.0 };

/* ---------- RAINBOW BANDS FOR THE TEAPOT ---------- */
#define NUM_BANDS 12
GLfloat rainbow[NUM_BANDS][3] = {
    { 0.95, 0.10, 0.10 },  // red
    { 0.98, 0.35, 0.05 },  // orange-red
    { 0.98, 0.60, 0.05 },  // orange
    { 0.98, 0.85, 0.05 },  // yellow
    { 0.55, 0.90, 0.10 },  // lime
    { 0.10, 0.85, 0.25 },  // green
    { 0.05, 0.85, 0.65 },  // teal
    { 0.05, 0.75, 0.95 },  // cyan
    { 0.10, 0.35, 0.95 },  // blue
    { 0.45, 0.15, 0.90 },  // indigo
    { 0.80, 0.15, 0.75 },  // purple
    { 0.95, 0.20, 0.55 }   // magenta
};

#define POT_RADIUS 0.8
#define POT_BOTTOM (-0.8)
#define POT_TOP    (0.8)

void init(void)
{
    /* BLACK background as requested */
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /* Two-sided lighting so inner surfaces of handle/spout also shade */
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* IMPORTANT: do NOT enable GL_COLOR_MATERIAL here.
       We use glMaterialfv explicitly for full control. */

    glShadeModel(GL_SMOOTH);

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
}

/* Helper: set material properties in one call */
void setMaterial(const GLfloat *amb, const GLfloat *dif,
                 const GLfloat *spec, const GLfloat *shin)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
}

/* ---------- RAINBOW TEAPOT using clipping planes ---------- */
void drawColorfulTeapot(void)
{
    GLfloat band_height = (POT_TOP - POT_BOTTOM) / NUM_BANDS;

    GLfloat pot_specular[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pot_shininess[] = { 110.0 };

    for (int i = 0; i < NUM_BANDS; i++) {
        GLfloat y_low  = POT_BOTTOM + i * band_height;
        GLfloat y_high = y_low + band_height;

        GLfloat amb[4] = { rainbow[i][0] * 0.3f,
                           rainbow[i][1] * 0.3f,
                           rainbow[i][2] * 0.3f, 1.0f };
        GLfloat dif[4] = { rainbow[i][0],
                           rainbow[i][1],
                           rainbow[i][2], 1.0f };

        setMaterial(amb, dif, pot_specular, pot_shininess);

        /* keep y >= y_low */
        GLdouble eqLow[4]  = { 0.0,  1.0, 0.0, -y_low };
        glClipPlane(GL_CLIP_PLANE0, eqLow);

        /* keep y <= y_high */
        GLdouble eqHigh[4] = { 0.0, -1.0, 0.0,  y_high };
        glClipPlane(GL_CLIP_PLANE1, eqHigh);

        glutSolidTeapot(POT_RADIUS);
    }

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

    /* ---------- TABLE TOP ---------- */
    glPushMatrix();
        setMaterial(table_ambient, table_diffuse,
                    table_specular, table_shininess);
        glScalef(4.0, 0.2, 4.0);
        glutSolidCube(1.0);
    glPopMatrix();

    /* ---------- TABLE LEGS ---------- */
    setMaterial(leg_ambient, leg_diffuse, leg_specular, leg_shininess);

    GLfloat legX[4] = { 1.7, -1.7,  1.7, -1.7 };
    GLfloat legZ[4] = { 1.7,  1.7, -1.7, -1.7 };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
            glTranslatef(legX[i], -1.0, legZ[i]);
            glScalef(0.3, 2.0, 0.3);
            glutSolidCube(1.0);
        glPopMatrix();
    }

    /* ---------- COLORFUL TEAPOT ---------- */
    glPushMatrix();
        glTranslatef(0.0, 0.9, 0.0);
        drawColorfulTeapot();
    glPopMatrix();

    /* ---------- RED APPLE (left) ---------- */
    GLfloat apple_amb[]   = { 0.30, 0.00, 0.00, 1.0 };
    GLfloat apple_dif[]   = { 0.90, 0.10, 0.10, 1.0 };
    GLfloat apple_spec[]  = { 1.00, 0.90, 0.90, 1.0 };
    GLfloat apple_shine[] = { 90.0 };

    glPushMatrix();
        setMaterial(apple_amb, apple_dif, apple_spec, apple_shine);
        glTranslatef(-1.2, 0.25, 0.8);
        glutSolidSphere(0.25, 40, 40);
    glPopMatrix();

    /* ---------- ORANGE (right) ---------- */
    GLfloat org_amb[]   = { 0.40, 0.18, 0.00, 1.0 };
    GLfloat org_dif[]   = { 1.00, 0.55, 0.00, 1.0 };
    GLfloat org_spec[]  = { 1.00, 1.00, 0.80, 1.0 };
    GLfloat org_shine[] = { 70.0 };

    glPushMatrix();
        setMaterial(org_amb, org_dif, org_spec, org_shine);
        glTranslatef(1.2, 0.30, 0.8);
        glutSolidSphere(0.30, 40, 40);
    glPopMatrix();

    /* ---------- GREEN LIME (back) ---------- */
    GLfloat lime_amb[]   = { 0.10, 0.30, 0.05, 1.0 };
    GLfloat lime_dif[]   = { 0.35, 0.90, 0.15, 1.0 };
    GLfloat lime_spec[]  = { 0.90, 1.00, 0.90, 1.0 };
    GLfloat lime_shine[] = { 80.0 };

    glPushMatrix();
        setMaterial(lime_amb, lime_dif, lime_spec, lime_shine);
        glTranslatef(0.0, 0.22, -1.3);
        glutSolidSphere(0.22, 40, 40);
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
    glutCreateWindow("Colorful Teapot on a Table");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}