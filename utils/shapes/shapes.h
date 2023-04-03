#define GL_SILENCE_DEPRECATION
#include <GL/gl.h>
#ifdef __APPLE_CC__
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <GL/glext.h>
#include <math.h>
using namespace std;

void materialProperty();

static void getNormal3p(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

void matCurve(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

void drawCube(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawSphere(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawTorus(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLdouble, GLdouble, GLint, GLint, GLfloat);
void drawCylinder(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawpyramid(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawTrapezoid(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawBox();