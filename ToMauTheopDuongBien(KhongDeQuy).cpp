#include <GL/glut.h>
#include <stdlib.h> // for calloc and free

struct LIST {
    int x, y;
    struct LIST *next;
};

struct LIST *top = NULL;

void push(int x, int y) {
    struct LIST *P;
    P = (LIST *) calloc(1, sizeof(LIST));
    P->x = x;
    P->y = y;
    P->next = NULL;
    if (top != NULL) {
        P->next = top;
    }
    top = P;
}

void pop(int *x, int *y) {
    if (top != NULL) {
        struct LIST *P = top;
        top = top->next;
        *x = P->x;
        *y = P->y;
        free(P);
    }
}

int isEmpty() {
    return top == NULL;
}

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
    push(x, y);

    while (!isEmpty()) {
        int cx, cy;
        pop(&cx, &cy);

        unsigned char color[3];
        getpixel(cx, cy, color);

        // Chuy?n d?i màu thành giá tr? float
        float currentR = color[0] / 255.0;
        float currentG = color[1] / 255.0;
        float currentB = color[2] / 255.0;

        if ((currentR != boundaryR || currentG != boundaryG || currentB != boundaryB) &&
            (currentR != fillR || currentG != fillG || currentB != fillB)) {
            putpixel(cx, cy, fillR, fillG, fillB);

            // Ð?y các di?m lân c?n vào ngan x?p
            push(cx + 1, cy);
            push(cx - 1, cy);
            push(cx, cy + 1);
            push(cx, cy - 1);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // V? hình ch? nh?t
    glColor3f(0.0, 0.0, 0.0); // Màu den cho du?ng vi?n
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(200, 100);
    glVertex2i(200, 200);
    glVertex2i(100, 200);
    glEnd();
    glFlush();

    // Tô màu hình ch? nh?t
    BoundaryFill(150, 150, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0); // Tô màu d?
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Màu n?n tr?ng
    glColor3f(0.0, 0.0, 0.0); // Màu v? den
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
    glutCreateWindow("Boundary Fill Algorithm (Non-Recursive with Stack)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

