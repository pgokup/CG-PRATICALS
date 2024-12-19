#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;


class Shape {
public:
    virtual void draw() = 0; 
    virtual void fill(int x, int y, const float color[3]) = 0; 
};


class ConcavePolygon : public Shape {
public:
    vector<float> vertices; 

    
    ConcavePolygon(const vector<float>& points) {
        vertices = points;
    }

    
    void draw() override {
        glBegin(GL_POLYGON);
        for (size_t i = 0; i < vertices.size(); i += 2) {
            glVertex2f(vertices[i], vertices[i + 1]);
        }
        glEnd();
    }

    
    void fill(int x, int y, const float color[3]) override {
        glColor3fv(color);  
       
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }

    
    void boundaryFill(int x, int y, const float fillColor[3], const float boundaryColor[3]) {
       
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2f(x, y);  
        glEnd();
    }
};

ConcavePolygon* polygon;

void display() {
    glClear(GL_COLOR_BUFFER_BIT); 

    polygon->draw();

    
    float fillColor[3] = {1.0f, 0.0f, 0.0f}; 
    polygon->fill(0, 0, fillColor);

    glFlush(); 
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

int main(int argc, char** argv) {
    
    vector<float> concavePolygonVertices = {-0.5f, -0.5f, 0.5f, -0.5f, 0.2f, 0.2f, -0.2f, 0.6f, -0.5f, 0.3f};
    polygon = new ConcavePolygon(concavePolygonVertices);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Concave Polygon with Boundary Fill");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
