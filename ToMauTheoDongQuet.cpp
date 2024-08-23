#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glEnd();
}

void scanlineFill(vector<Point>& vertices) {
    // T?m t?a ð? y t?i ða và y t?i thi?u c?a h?nh vuông
    int minY = vertices[0].y, maxY = vertices[0].y;
    for (int i = 1; i < vertices.size(); ++i) {
        if (vertices[i].y < minY) minY = vertices[i].y;
        if (vertices[i].y > maxY) maxY = vertices[i].y;
    }

    // Quét t?ng d?ng (scanline) t? minY ð?n maxY
    for (int y = minY; y <= maxY; ++y) {
        vector<int> intersections;

        // T?m các ði?m giao nhau v?i d?ng quét
        for (int i = 0; i < vertices.size(); ++i) {
            int next = (i + 1) % vertices.size();
            int y1 = vertices[i].y, y2 = vertices[next].y;

            // Ki?m tra xem có giao v?i d?ng quét hay không
            if ((y1 <= y && y < y2) || (y2 <= y && y < y1)) {
                int x = vertices[i].x + (y - y1) * (vertices[next].x - vertices[i].x) / (y2 - y1);
                intersections.push_back(x);
            }
        }

        // S?p x?p các ði?m giao nhau theo t?a ð? x tãng d?n
        sort(intersections.begin(), intersections.end());

        // Tô màu t?ng ðo?n ngang gi?a các c?p ði?m giao nhau
        for (int i = 0; i < intersections.size(); i += 2) {
            int startX = intersections[i];
            int endX = intersections[i + 1];
            glBegin(GL_LINES);
            glVertex2i(startX, y);
            glVertex2i(endX, y);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // V? h?nh vuông
    vector<Point> square;
    square.push_back(Point(100, 100));
    square.push_back(Point(200, 100));
    square.push_back(Point(200, 200));
    square.push_back(Point(100, 200));

    glColor3f(1.0, 0.0, 0.0); // Màu ð?
    scanlineFill(square);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Màu n?n tr?ng
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Square with Scanline Fill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

