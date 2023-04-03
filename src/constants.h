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

static double Txval = 0, Tyval = 0, Tzval = 0;
static double windowHeight = 1000, windowWidth = 1000;
static double  human_x = 10, human_y = -15 , human_z = 50, angle_x = 0, leg_angle_1 = 0, leg_angle_2 = 0, leg_flag = 0, leg_coming_back = 0, hand_angle_1 = 0, hand_angle_2 = 0;
static GLfloat alpha = 0.0, theta = 0.0, orbiterAlpha = -45.0, orbiterTheta = 0.0, testTheta = -45.0, pirateBoatTheta = 0.0, cmOrbiterAlpha = 0.0, cmOrbiterTheta = 0.0, skyDropPos = 0.0;
static double eyeX = -10, eyeY = 5.0, eyeZ = 100, refX = 0, refY = 0, refZ = 0;
static GLboolean bRotate = false, uRotate = false, fanSwitch = false, door1 = false, orbiterFlag = false, testFlag = true, pirateBoatFlag = false, pirateBoatCheck = false, cmOrbiterFlag = false, skyDropFlag = false, upFlag = true, downFlag1 = true, downFlag2 = false, downFlag3 = false, show = false, day = true, switchOne = false, switchTwo = false, switchThree = false, switchFour = false;
static unsigned int ID;
static unsigned int ID2[40];

static GLfloat yf = 0, xf = 0;
static GLboolean yflag = false, xflag = false;

#endif /* CONSTANTS_H */