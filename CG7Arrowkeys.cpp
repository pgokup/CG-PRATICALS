#include <GL/glut.h>
#include <iostream>
#include<cmath>

using namespace std;


class Shape {
public:
    virtual void draw() = 0;
    virtual void move(float dx, float dy) = 0;
};


class Ball : public Shape {
private:
    float x, y;      
    float radius;   
public:
    Ball(float x = 0.0, float y = 0.0, float radius = 0.1) : x(x), y(y), radius(radius) {}

    
    void draw() override {
        glColor3f(0.2, 0.6, 0.8); 
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); 
        for (int i = 0; i <= 50; i++) {
            float angle = 2.0 * 3.14159 * i / 50;
            glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
        }
        glEnd();
    }

    
    void move(float dx, float dy) override {
        x += dx;
        y += dy;

        
        if (x + radius > 1.0) x = 1.0 - radius;
        if (x - radius < -1.0) x = -1.0 + radius;
        if (y + radius > 1.0) y = 1.0 - radius;
        if (y - radius < -1.0) y = -1.0 + radius;
    }
};

Ball ball(0.0, 0.0, 0.1);

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    ball.draw(); 

    glutSwapBuffers();
}


void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            ball.move(0.0, 0.05);
            break;
        case GLUT_KEY_DOWN:
            ball.move(0.0, -0.05);
            break;
        case GLUT_KEY_LEFT:
            ball.move(-0.05, 0.0);
            break;
        case GLUT_KEY_RIGHT:
            ball.move(0.05, 0.0);
            break;
    }
    glutPostRedisplay(); 
}
void printInstructions() {
    cout << "Use the arrow keys to move the ball:\n";
    cout << "  UP ARROW    : Move up\n";
    cout << "  DOWN ARROW  : Move down\n";
    cout << "  LEFT ARROW  : Move left\n";
    cout << "  RIGHT ARROW : Move right\n";

}

void initOpenGL() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	 printInstructions(); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ball Control with Arrow Keys");

    initOpenGL();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys); 
    glutMainLoop();
    return 0;
}
