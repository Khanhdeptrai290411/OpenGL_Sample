#include <GL/glut.h>

// Bi?n to�n c?c �? l�u tr? t?a �? t�m v� b�n k�nh c?a ��?ng tr?n
int xc = -1, yc = -1, r = 50; // B�n k�nh c? �?nh, b?n c� th? thay �?i theo ? mu?n

// H�m v? 8 �i?m �?i x?ng c?a ��?ng tr?n
void put8pixel(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// H�m s? d?ng thu?t to�n Bresenham �? v? ��?ng tr?n
void CircleBres(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;

    while (x <= y) {
        put8pixel(xc, yc, x, y);
        if (p < 0) {
            p += 4 * x + 6;
        } else {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (xc != -1 && yc != -1) {
        // G?i h�m v? ��?ng tr?n
        CircleBres(xc, yc, r);
    }

    glFlush();
}

// H�m x? l? s? ki?n chu?t
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Chuy?n �?i t?a �? c?a s? th�nh t?a �? OpenGL
        xc = x;
        yc = 400 - y; // �?i chi?u y v? OpenGL c� g?c t?a �? ? g�c d�?i tr�i

        // Y�u c?u v? l?i c?a s?
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // M�u n?n
    glColor3f(1.0, 0.0, 1.0);         // M�u v? (MAGENTA)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0); // Thi?t l?p h? t?a �?
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle Drawing with Mouse");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

