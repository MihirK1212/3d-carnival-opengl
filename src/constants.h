#ifndef CONSTANTS_H
#define CONSTANTS_H


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

static GLUquadric *quad;


static unsigned int ID2[40];



#endif /* CONSTANTS_H */