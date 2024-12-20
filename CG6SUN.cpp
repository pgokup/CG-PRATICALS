#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

float sunY = -0.8; 
bool isRising = true; 

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    
    if (isRising) {
        glClearColor(0.0, 0.5, 1.0, 1.0); 
    } else {
        glClearColor(0.1, 0.1, 0.2, 1.0); 
    }
    glClear(GL_COLOR_BUFFER_BIT);

   
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        glVertex2f(0.1 * cos(theta), sunY + 0.1 * sin(theta));
    }
    glEnd();

    
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, -0.5);
    glVertex2f(-1.0, -0.5);
    glEnd();

    glFlush();
}

void update(int value) {
    if (isRising) {
        sunY += 0.01;
        if (sunY >= 0.8) {
            isRising = false; 
        }
    } else {
        sunY -= 0.01;
        if (sunY <= -0.8) {
            isRising = true; 
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sunrise and Sunset Simulation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(50, update, 0);
    glutMainLoop();

    return 0;
}
