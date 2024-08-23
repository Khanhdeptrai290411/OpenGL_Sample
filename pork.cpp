#include <GL/glut.h>

void drawTrident() {
    glBegin(GL_LINES);

    // Draw the handle of the trident
    glVertex2f(-0.1, -0.5);
    glVertex2f(-0.1, 0.5);

    glVertex2f(0.1, -0.5);
    glVertex2f(0.1, 0.5);

    // Draw the left prong
    glVertex2f(-0.3, 0.5);
    glVertex2f(-0.3, 0.8);

    glVertex2f(-0.3, 0.8);
    glVertex2f(-0.2, 0.8);

    glVertex2f(-0.2, 0.8);
    glVertex2f(-0.2, 0.5);

    // Draw the middle prong
    glVertex2f(-0.05, 0.5);
    glVertex2f(-0.05, 0.8);

    glVertex2f(-0.05, 0.8);
    glVertex2f(0.05, 0.8);

    glVertex2f(0.05, 0.8);
    glVertex2f(0.05, 0.5);

    // Draw the right prong
    glVertex2f(0.2, 0.5);
    glVertex2f(0.2, 0.8);

    glVertex2f(0.2, 0.8);
    glVertex2f(0.3, 0.8);

    glVertex2f(0.3, 0.8);
    glVertex2f(0.3, 0.5);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0); // Set color to white

    drawTrident();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Trident");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

