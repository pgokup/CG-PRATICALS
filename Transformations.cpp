#include <iostream>
#include <GL/glut.h>

using namespace std;


struct Point {
    float x, y;

   
    Point(float x = 0.0, float y = 0.0) : x(x), y(y) {}

    
    Point operator+(const Point& p) {
        return Point(x + p.x, y + p.y);
    }

    
    Point operator*(float scaleFactor) {
        return Point(x * scaleFactor, y * scaleFactor);
    }

    
    void draw() {
        glVertex2f(x, y);
    }
};


void drawTriangle() {
    glBegin(GL_POLYGON);
    Point p1(100, 100), p2(200, 100), p3(150, 200);
    p1.draw();
    p2.draw();
    p3.draw();
    glEnd();
}


void scaleTriangle(Point& p1, Point& p2, Point& p3, float scaleFactor) {
    p1 = p1 * scaleFactor;
    p2 = p2 * scaleFactor;
    p3 = p3 * scaleFactor;
}


void translateTriangle(Point& p1, Point& p2, Point& p3, const Point& translationVector) {
    p1 = p1 + translationVector;
    p2 = p2 + translationVector;
    p3 = p3 + translationVector;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);  

    
    Point p1(100, 100), p2(200, 100), p3(150, 200);

  
    glColor3f(1.0, 0.0, 0.0);  
    drawTriangle();

    
    scaleTriangle(p1, p2, p3, 1.5);
    glColor3f(0.0, 1.0, 0.0); 
    glBegin(GL_POLYGON);
    p1.draw();
    p2.draw();
    p3.draw();
    glEnd();

   
    Point translationVector(50, 50);
    translateTriangle(p1, p2, p3, translationVector);
    glColor3f(0.0, 0.0, 1.0);  
    glBegin(GL_POLYGON);
    p1.draw();
    p2.draw();
    p3.draw();
    glEnd();

    glFlush();
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  
    glMatrixMode(GL_PROJECTION);        
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);  


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("2D Object with Transformations");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

