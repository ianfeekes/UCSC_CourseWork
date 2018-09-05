// $Id: hello-world.cpp,v 1.21 2018-08-06 13:38:43-07 - - $

/*Ian Feekes
 *#1474914
 *ifeekes@ucsc.edu
 *cmps109 asg5
 *All work for this assignment done without a partner*/ 

/*NOTE: source code originally taken from hello-world in labGL*/ 

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include <GL/freeglut.h>
#include <libgen.h>

// Characteristics of the window.
struct window {
   string name;
   int width {640};
   int height {480};
} window;

template <typename item_t>
struct cycle_iterator {
   const vector<item_t> items;
   size_t curr_item {0};
   cycle_iterator (initializer_list<item_t> list):
               items(vector<item_t> (list)) {}
   const item_t& operator*() { return items[curr_item]; }
   const item_t& operator[] (size_t index) {
      return items[(curr_item + index) % items.size()];
   }
   cycle_iterator& operator++() { 
      curr_item = (curr_item + 1) % items.size();
      return *this;
   }
};

GLubyte BLACK[] = {0,0,0};
GLubyte WHITE[] = {255,255,255};
GLubyte BLUE[] = {0,0,255};
GLubyte CYAN[] = {0,255,255}; 
GLubyte GREEN[] = {0,255,0}; 
GLubyte RED[] = {255,0,0}; 
/*Added colour for the background*/ 
GLubyte Grey[] = {211,211,211}; 
/*Default index for which two colours to draw from*/ 
int colorIndex = 0; 
const vector<const GLubyte*> colors{BLACK,WHITE,BLUE,CYAN,RED,GREEN};
/*Background processing doesn't need modification: Only thing changed
 *is the colour argument in the function call for draw_rectangle*/ 
void draw_rectangle (const GLubyte* color) {
   glBegin (GL_POLYGON);
   glColor3ubv (color);
   glVertex2f (0, 0);
   glVertex2f (window.width, 0);
   glVertex2f (window.width, window.height);
   glVertex2f (0, window.height);
   glEnd();
}

/*Draw chess grid has two colour arguments*/ 
void draw_chess_grid(const GLubyte* c1, const GLubyte* c2)
{
   for(size_t i=0;i<8;++i)
   {
      for(size_t j=0;j<8;++j)
      {
         glBegin(GL_POLYGON);
         if(i%2==0)
         {
            if(j%2==0) glColor3ubv(c2);
            else glColor3ubv(c1); 
         }
         else
         {
            if(j%2==0) glColor3ubv(c1);
            else glColor3ubv(c2); 
         }
         int minDim = min(window.width, window.height); 
         float boardDim = minDim*7/8; 
         glVertex2f((minDim-boardDim)/2+i*(boardDim/8),
                    (minDim-boardDim)/2+j*(boardDim/8));
         glVertex2f((minDim-boardDim)/2+i*(boardDim/8),
                    (minDim- boardDim)/2+(j+1)*(boardDim/8));
         glVertex2f((minDim-boardDim)/2+(i+1)*(boardDim/8),
                    (minDim-boardDim)/2+(j+1)*(boardDim/8));
         glVertex2f((minDim-boardDim)/2+(i+1)*(boardDim/8), 
                    (minDim-boardDim)/2+(j)*(boardDim/8)); 
         glEnd(); 
      }
   }
}

int min(int x, int y)
{
   if(x<y) return x; 
   return y; 
}

/*Clears colours first, draws background rectangle, draws chessboard*/
void display() {
   glClearColor (0.15, 0.15, 0.15, 1.0);
   glClear (GL_COLOR_BUFFER_BIT);
   /*Changes to drawing the rectangle background of grey*/ 
   draw_rectangle (Grey);
   draw_chess_grid(colors[colorIndex], colors[colorIndex+1]); 
   glutSwapBuffers();
}

/*keyboard processing: k = black&white, b=blue&cyan, g=green&red*/
void keyboard (GLubyte key, int, int) {
   enum{ESC = 27};
   switch (key) {
      case 'k': case 'K': 
         colorIndex = 0;
         break;
      case 'b': case 'B':
         colorIndex = 2;
         break;
      case 'g': case 'G':
         colorIndex = 4;
         break;
      case 'q': case 'Q': case ESC: 
         exit(EXIT_SUCCESS); 
   }
   glutPostRedisplay();
}

/*This is already good and doesn't need to be changed*/ 
void reshape (int width, int height) {
   window.width = width;
   window.height = height;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0, window.width, 0, window.height);
   glMatrixMode (GL_MODELVIEW);
   glViewport (0, 0, window.width, window.height);
   glutPostRedisplay();
}

int main (int argc, char** argv) {
   window.name = basename (argv[0]);
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize (window.width, window.height);
   glutCreateWindow (window.name.c_str());
   glutDisplayFunc (display);
   glutReshapeFunc (reshape);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}

