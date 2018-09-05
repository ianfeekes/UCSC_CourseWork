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

GLubyte RED[] = {0xFF, 0x00, 0x00};
GLubyte GREEN[] = {0x00, 0xFF, 0x00};
GLubyte BLUE[] = {0x00, 0x00, 0xFF};
/*Added colour for the background*/ 
GLubyte Grey[] = {211,211,211}; 
cycle_iterator<GLubyte*> colors {BLUE, GREEN, RED};
/*Compute the main diameter*/ 
float mainD = min(window.width, window.height)*9/20;

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

void draw_ellipse1 (const GLubyte* color) {
   glBegin (GL_POLYGON);
   glColor3ubv (color);
   const GLfloat delta = 2 * M_PI / 64;
   const GLfloat width = mainD; 
   const GLfloat height = mainD;
   const GLfloat xoffset = window.width / 2.0;
   const GLfloat yoffset = window.height / 2.0;
   for (GLfloat theta = 0; theta < 2 * M_PI; theta += delta) {
      GLfloat xpos = width * cos (theta) + xoffset;
      GLfloat ypos = height * sin (theta) + yoffset;
      glVertex2f (xpos, ypos);
   }
   glEnd();
}

void draw_ellipse2 (const GLubyte* color) {
   glBegin (GL_POLYGON);
   glColor3ubv (color);
   const GLfloat delta = 2 * M_PI / 64;
   const GLfloat width = mainD*2/3;
   const GLfloat height = mainD*2/3;
   const GLfloat xoffset = window.width / 2.0;
   const GLfloat yoffset = window.height / 2.0;
   for (GLfloat theta = 0; theta < 2 * M_PI; theta += delta) {
      GLfloat xpos = width * cos (theta) + xoffset;
      GLfloat ypos = height * sin (theta) + yoffset;
      glVertex2f (xpos, ypos);
   }
   glEnd();
}

void draw_ellipse3 (const GLubyte* color) {
   glBegin (GL_POLYGON);
   glColor3ubv (color);
   const GLfloat delta = 2 * M_PI / 64;
   const GLfloat width = mainD*1/3;
   const GLfloat height = mainD*1/3;
   const GLfloat xoffset = window.width /2.0;
   const GLfloat yoffset = window.height / 2.0;
   for (GLfloat theta = 0; theta < 2 * M_PI; theta += delta) {
      GLfloat xpos = width * cos (theta) + xoffset;
      GLfloat ypos = height * sin (theta) + yoffset;
      glVertex2f (xpos, ypos);
   }
   glEnd();
}

/*Clears colours first*/ 
void display() {
   glClearColor (0.15, 0.15, 0.15, 1.0);
   glClear (GL_COLOR_BUFFER_BIT);
   /*Changes to drawing the rectangle background of grey*/ 
   draw_rectangle (Grey);
   draw_ellipse1 (colors[0]);
   draw_ellipse2 (colors[1]); 
   draw_ellipse3 (colors[2]);
   glutSwapBuffers();
}

/*Colour inversion has already been implemented for us*/ 
void invert_colors() {
   for (size_t color = 0; color < 3; ++color) {
      for (size_t rgb = 0; rgb < 3; ++rgb) {
         colors[color][rgb] ^= 0xFF;
      }
   }
}

/*keyboard processing: q quits, s inverts, c cycles*/ 
void keyboard (GLubyte key, int, int) {
   enum{ESC = 27};
   switch (key) {
      case 's': case 'S': 
         invert_colors();
         break;
      case 'c': case 'C':
         ++colors;
         break;
      case 'q': case 'Q': case ESC: 
         exit (EXIT_SUCCESS);
   }
   glutPostRedisplay();
}

/*This is already good and doesn't need to be changed*/ 
void reshape (int width, int height) {
   window.width = width;
   window.height = height;
   /*Recompute main diameter after resizing height and width var*/ 
   mainD = min(window.width, window.height)*9/20;
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

