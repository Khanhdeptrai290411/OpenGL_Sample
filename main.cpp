#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated;
GLfloat red=0.8, green = 0.2, blue = 0.1;
GLdouble size = 1.0;

int lastX, lastY;
bool isDragging = false;

void display(void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -4.5);
    glColor3f(red,green,blue);
    glRotatef(xRotated, 1.0, 0.0, 0.0);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    glScalef(size, size, size);
    glutSolidTeapot(2.0);
    glFlush();
    glutSwapBuffers();
}

void reshapeFunc(int x, int y) {
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glViewport(0, 0, x, y);
}

void idleFunc(void) {
    yRotated += 0.0;
    display();
}

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastX = x;
            lastY = y;
            isDragging = true;
        } else if (state == GLUT_UP) {
            isDragging = false;
        }
    } else if (button == 3) { // Scroll up
        size += 0.1;
        if (size > 3.0) size = 3.0;
    } else if (button == 4) { // Scroll down
        size -= 0.1;
        if (size < 0.1) size = 0.1;
    }
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
		case 'b': 
		    red= 0.1f;
		    green=0.2f;
		    blue=0.8f;
		    	 glutPostRedisplay();
		    break;
		    		case 'r': 
		    red= 0.8f;
		    green=0.2f;
		    blue=0.1f;
		    	 glutPostRedisplay();
		    break;
		      		case 'g': 
		    red= 0.1f;
		    green=0.8f;
		    blue=0.2f;
		    	 glutPostRedisplay();
		    break;
	}
	 glutPostRedisplay();
}

void motionFunc(int x, int y) {
    if (isDragging) {
        xRotated += (y - lastY);
        yRotated += (x - lastX);
        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Teapot Interaction");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    xRotated = yRotated = zRotated = 30.0;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

