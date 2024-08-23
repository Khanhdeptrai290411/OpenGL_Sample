#include <GL/glut.h>
#include <queue>
#include <utility>  // std::pair

void putpixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getpixel(int x, int y, unsigned char *color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
}

void BoundaryFill(int x, int y, float fillR, float fillG, float fillB, float boundaryR, float boundaryG, float boundaryB) {
    std::queue<std::pair<int, int> > q;
    q.push({x, y});

    while (!q.empty()) {
        std::pair<int, int> p = q.front();
        q.pop();
        int cx = p.first;
        int cy = p.second;

        unsigned char color[3];
        getpixel(cx, cy, color);

        // Chuy?n ð?i màu thành giá tr? float
        float currentR = color[0] / 255.0;
        float currentG = color[1] / 255.0;
        float currentB = color[2] / 255.0;

        if ((currentR != boundaryR || currentG != boundaryG || currentB != boundaryB) &&
            (currentR != fillR || currentG != fillG || currentB != fillB)) {
            putpixel(cx, cy, fillR, fillG, fillB);

            // Ð?y các ði?m lân c?n vào hàng ð?i
            q.push({cx + 1, cy});
            q.push({cx - 1, cy});
            q.push({cx, cy + 1});
            q.push({cx, cy - 1});
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // V? h?nh ch? nh?t
    glColor3f(0.0, 0.0, 0.0); // Màu ðen cho ðý?ng vi?n
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(200, 100);
    glVertex2i(200, 200);
    glVertex2i(100, 200);
    glEnd();
    glFlush();

    // Tô màu h?nh ch? nh?t
    BoundaryFill(150, 150, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0); // Tô màu ð?
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Màu n?n tr?ng
    glColor3f(0.0, 0.0, 0.0); // Màu v? ðen
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary Fill Algorithm (Non-Recursive)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

