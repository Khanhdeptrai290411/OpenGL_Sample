#include <GL/glut.h>

// Bi?n toàn c?c ð? lýu tr? t?a ð? tâm và bán kính c?a ðý?ng tr?n
int xc = -1, yc = -1, r = 50; // Bán kính c? ð?nh, b?n có th? thay ð?i theo ? mu?n

// Hàm v? 8 ði?m ð?i x?ng c?a ðý?ng tr?n
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

// Hàm s? d?ng thu?t toán Bresenham ð? v? ðý?ng tr?n
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
        // G?i hàm v? ðý?ng tr?n
        CircleBres(xc, yc, r);
    }

    glFlush();
}

// Hàm x? l? s? ki?n chu?t
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Chuy?n ð?i t?a ð? c?a s? thành t?a ð? OpenGL
        xc = x;
        yc = 400 - y; // Ð?i chi?u y v? OpenGL có g?c t?a ð? ? góc dý?i trái

        // Yêu c?u v? l?i c?a s?
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Màu n?n
    glColor3f(1.0, 0.0, 1.0);         // Màu v? (MAGENTA)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0); // Thi?t l?p h? t?a ð?
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

