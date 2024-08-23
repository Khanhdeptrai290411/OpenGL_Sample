#include <GL/glut.h>

// Hàm v? m?t ði?m pixel t?i t?a ð? (x, y)
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Hàm s? d?ng thu?t toán Bresenham ð? v? ðo?n th?ng
void LineBres(int x1, int y1, int x2, int y2) {
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    int const1 = 2 * Dy;
    int const2 = 2 * (Dy - Dx);
    int P = 2 * Dy - Dx;
    int x = x1;
    int y = y1;

    while (x <= x2) {
        setPixel(x, y);
        if (P < 0) {
            P += const1;
        } else {
            P += const2;
            y++;
        }
        x++;
    }
}

// Hàm v? khung bao quanh ðo?n th?ng
void drawBoundingBox(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1 - 5, y1 - 5); // Góc dý?i bên trái
    glVertex2i(x2 + 5, y1 - 5); // Góc dý?i bên ph?i
    glVertex2i(x2 + 5, y2 + 5); // Góc trên bên ph?i
    glVertex2i(x1 - 5, y2 + 5); // Góc trên bên trái
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // T?a ð? c?a ðo?n th?ng
    int x1 = 50, y1 = 50, x2 = 200, y2 = 150;
    
    // G?i hàm v? ðo?n th?ng
        glColor3f(1.0, 0.0, 1.0); // Màu vàng
    LineBres(x1, y1, x2, y2);
    
    // Ð?i màu ð? v? khung bao quanh ðo?n th?ng
    glColor3f(1.0, 1.0, 0.0); // Màu vàng
    drawBoundingBox(x1, y1, x2, y2);
    
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Màu n?n
    glColor3f(1.0, 0.0, 1.0);         // Màu v? (MAGENTA)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 300.0); // Thi?t l?p h? t?a ð?
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing with Bounding Box");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

