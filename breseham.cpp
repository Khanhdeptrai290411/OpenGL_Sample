#include <GL/glut.h>

// H�m v? m?t �i?m pixel t?i t?a �? (x, y)
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// H�m s? d?ng thu?t to�n Bresenham �? v? �o?n th?ng
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

// H�m v? khung bao quanh �o?n th?ng
void drawBoundingBox(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1 - 5, y1 - 5); // G�c d�?i b�n tr�i
    glVertex2i(x2 + 5, y1 - 5); // G�c d�?i b�n ph?i
    glVertex2i(x2 + 5, y2 + 5); // G�c tr�n b�n ph?i
    glVertex2i(x1 - 5, y2 + 5); // G�c tr�n b�n tr�i
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // T?a �? c?a �o?n th?ng
    int x1 = 50, y1 = 50, x2 = 200, y2 = 150;
    
    // G?i h�m v? �o?n th?ng
        glColor3f(1.0, 0.0, 1.0); // M�u v�ng
    LineBres(x1, y1, x2, y2);
    
    // �?i m�u �? v? khung bao quanh �o?n th?ng
    glColor3f(1.0, 1.0, 0.0); // M�u v�ng
    drawBoundingBox(x1, y1, x2, y2);
    
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // M�u n?n
    glColor3f(1.0, 0.0, 1.0);         // M�u v? (MAGENTA)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 300.0); // Thi?t l?p h? t?a �?
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

