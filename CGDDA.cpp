#include <iostream>
#include <GL/glut.h>
#include<cmath>

using namespace std;

int a1 , b1,a2,b2,a3,b3;
int s;
float h ;

int xc , yc , r1 , r2;


int Round(int a)
{
  return (int)(a + 0.5);
}


void dda(int x1 ,int Y1 , int X2 , int y2)
{ 

  int dx , dy , steps;
  
  dx = X2 - x1;
  dy = y2 - Y1;
  
  if (abs(dx)>abs(dy))
  {
    steps = abs(dx);
  }
  else 
  {
    steps = abs(dy);
  }
  float xinc , yinc;
  xinc = dx/float(steps);
  yinc = dy/float(steps);
  
  float x = x1;
  float y = Y1;
  glBegin(GL_POINTS);
  glVertex2d(x,y);
  
for (int i = 0; i<steps;i++)
{
    x += xinc;
    y += yinc;
    glVertex2d( Round(x), Round(y));
}
    glEnd();
    glFlush();
}

void BreshenhamCircle(int xc ,int yc, int r)
{
  int d , x , y;
  
  d = 3 - 2*r;
  x=0;
  y=r;
  
  do {
        glBegin(GL_POINTS);
        glVertex2d(xc + x , yc + y);
        glVertex2d(xc - x , yc + y);
        glVertex2d(xc + x , yc - y);
        glVertex2d(xc - x , yc - y);
        glVertex2d(xc + y , yc + x);
        glVertex2d(xc - y , yc + x);
        glVertex2d(xc + y , yc - x);
        glVertex2d(xc - y , yc - x);
        glEnd();
        glFlush();
        if(d<0)
        {
          d = d + 4*x + 6;
          x = x+ 1;
          
        }
        else
        {
          d = d + 4*(x-y) + 10;
          x = x+ 1;
          y = y-1;
          
        }

      }while(x<=y);  

}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //glBegin(GL_POINTS);

    // Drawing multiple points for better testing
    
    dda(a1,b1,a2,b2);
    dda(a2,b2,a3,b3);
    dda(a3,b3,a1,b1);
    BreshenhamCircle(xc , yc , r1);
    BreshenhamCircle(xc , yc , r2);
    
    //glEnd();
    //glFlush();
}

int main(int argc, char **argv)
{
    cout<<"Enter the length of the equi. triangle";

    cin>>s;

    cout<<"Enter the co-ordinates: x1 , y1 ";
    cin>>a1>>b1;
    
    a2 = a1 + s;
    b2 = b1;
    a3 = a1 + s/2;
    h = s*sqrt(3)/2;
    b3 = b1 + h;
    
    
//Centre of circle:
  xc = (a1 + a2 + a3)/3;
  yc = (b1 + b2 + b3)/3;
  
//Radius of Incircle:
  r1 = s/(2* (sqrt(3)) );

//Radius of Circumcircle :
  r2 = s/(sqrt(3));
     
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100); // Set window position on screen
    glutInitWindowSize(640, 480);     // Set window size

    glutCreateWindow("CG Practical");


    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);


    gluOrtho2D(0, 640, 0, 480);


    glutDisplayFunc(Draw);
    glutMainLoop();

    return 0;
}

