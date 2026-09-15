#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Triangle vertices
float triangle[3][2] = {
    {0.0, 0.0},    // Vertex A
    {0.5, 0.0},    // Vertex B
    {0.25, 0.5}    // Vertex C
};

// Fixed point for rotation
float fixedPoint[2] = {0.5, 0.5};

// Rotation angles
float angleOrigin = 0.0;
float angleFixed = 0.0;

// Rotation speed
float speed = 0.5;

void drawTriangle(float vertices[3][2])
{
    glBegin(GL_TRIANGLES);
        glVertex2f(vertices[0][0], vertices[0][1]);
        glVertex2f(vertices[1][0], vertices[1][1]);
        glVertex2f(vertices[2][0], vertices[2][1]);
    glEnd();
}

void drawAxes()
{
    glBegin(GL_LINES);
        // X-axis
        glColor3f(0.6, 0.6, 0.6);
        glVertex2f(-2.0, 0.0);
        glVertex2f(2.0, 0.0);
        // Y-axis
        glVertex2f(0.0, -2.0);
        glVertex2f(0.0, 2.0);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw axes
    drawAxes();
    
    // Draw fixed point as a small red dot
    glPointSize(6.0);
    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(fixedPoint[0], fixedPoint[1]);
    glEnd();
    
    // -------- Triangle 1: Rotation about ORIGIN --------
    glPushMatrix();
        glTranslatef(-0.8, 0.0, 0.0);       // Move to left side
        glRotatef(angleOrigin, 0.0, 0.0, 1.0); // Rotate about origin
        glColor3f(0.0, 1.0, 0.0);
        drawTriangle(triangle);
    glPopMatrix();
    
    // -------- Triangle 2: Rotation about FIXED POINT --------
    glPushMatrix();
        glTranslatef(0.8, 0.0, 0.0);        // Move to right side
        
        // Translate fixed point to origin, rotate, translate back
        glTranslatef(fixedPoint[0], fixedPoint[1], 0.0);
        glRotatef(angleFixed, 0.0, 0.0, 1.0);
        glTranslatef(-fixedPoint[0], -fixedPoint[1], 0.0);
        
        glColor3f(0.0, 0.5, 1.0);
        drawTriangle(triangle);
        
        // Draw fixed point in local coordinates
        glPointSize(6.0);
        glBegin(GL_POINTS);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(fixedPoint[0], fixedPoint[1]);
        glEnd();
    glPopMatrix();
    
    // Labels
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-1.0, 1.5);
    char *label1 = "Rotation about Origin";
    while (*label1) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *label1++);
    
    glRasterPos2f(0.5, 1.5);
    char *label2 = "Rotation about Fixed Point";
    while (*label2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *label2++);
    
    glutSwapBuffers();
}

void update(int value)
{
    angleOrigin += speed;
    angleFixed += speed;
    
    if (angleOrigin > 360.0) angleOrigin -= 360.0;
    if (angleFixed > 360.0) angleFixed -= 360.0;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // ~60 FPS
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Triangle Rotation - Origin vs Fixed Point");
    
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}