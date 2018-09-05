/*rainbow.cpp 
 *Ian Feekes
 *ifeekes@unix.ucsc.edu
 *#1474914
 */ 

/*Makes an executable called rainbow. It displays seven vertical 
 *rectangles, the complete height of the window and 1/7 of the width
 *of the window. The colours, in order from left to right are: 
 *red, orange, yellow, green, blue, indigo, violet. The default size
 *of the window is 384*256px, but resizing windows should still allow
 *for the proportions to survive*/ 

/*NOTE: large amounts of this code have been modified from the
 *ciao mondo code, especially the resizing and the draw loop*/

#include <cmath> 
#include <iostream> 
#include <vector> 
using namespace std; 
#include <GL/freeglut.h> 
#include <libgen.h> 

/*Window structure with default size fields*/ 
struct{
   int width = 385; 
   int height = 231; 
}window; 

/*Colour field initializations necessary for designing a rainbow*/ 
const GLubyte red[] {255,0,0}; 
const GLubyte orange[] {255, 127, 0}; 
const GLubyte yellow[] {255,255,0}; 
const GLubyte green[] {0,255,0};//{0x00, 0x92, 0x46}; 
const GLubyte blue[] {0,0,255}; 
const GLubyte indigo[] {75, 0, 130}; 
const GLubyte violet[] {148, 0, 211}; 
//vector containing all the colours in their respective order
const vector<const GLubyte*> colors {red,orange,yellow,
                                     green,blue,indigo,violet};
//aspect ratio used for proportioning of the lines
constexpr GLfloat aspect_ratio = 3.0 / 5.0;

/*Draws 7 vertical lines with the colour from the vector initiated
 *above, incrementing the coordinates of each line as needed based on
 *the fields of the window height and window width*/ 
void draw_rainbow()
{
   for(size_t i=0;i<7;++i)
   {
      glBegin(GL_POLYGON); 
      glColor3ubv(colors[i]);
      glVertex2f(window.width*i/7.0, 0);
      glVertex2f(window.width*(i+1)/7.0, 0); 
      glVertex2f(window.width*(i+1)/7.0,window.height);
      glVertex2f(window.width*i/7.0,window.height);
      glEnd(); 
   }
} 

void display()
{
   glClearColor(0.0,0.0,0.0,0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   draw_rainbow();
   glutSwapBuffers(); 
}

void reshape(int width, int height)
{
   window.height = height; 
   window.width = width; 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity(); 
   gluOrtho2D(0,window.width, 0, window.height);
   glMatrixMode(GL_MODELVIEW);
   glViewport(0,0,window.width, window.height); 
   glutPostRedisplay(); 
}

int main(int argc, char**argv)
{
   glutInit(&argc, argv);
   glutInitWindowSize(window.width,window.height);
   glutCreateWindow(basename(argv[0]));
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0; 
}
