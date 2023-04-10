#ifndef OBJECTS_H
#define OBJECTS_H

#include "../../libs.h"

#include "../shapes/shapes.h"
#include "../../bmpLoader.h"


const int nt = 60;
const int ntheta = 20;
const double PI = 3.14159265389;

struct Objects {

    GLboolean switchOne;
    GLboolean switchTwo;
    GLboolean switchThree;
    GLboolean switchFour;

    GLboolean xflag;
    GLboolean yflag;
    GLfloat xf ;
    GLfloat yf ;

    GLboolean controlPointsFlag;

    GLUquadric *quad;

    Objects() {
        switchOne = switchTwo = switchThree = switchFour = false;
        xflag = yflag = false;
        xf = yf = 0;
        controlPointsFlag = false;
    }

    void drawPool();

    void bush();
    void tree();
    void chair();
    void table();
    void DrawUmbrella();
    void diningSet();
    
    void icecreamParlor();
    void pizzaHut();
    void dunkinDonuts();
    void cafeteriaFence();
    void cafeteria();

    void streetLampbody();
    void streetLight1();
    void streetLight2();
    void streetLight3();
    void streetLight4();

    void wall();
    void walls();
    
    void bench1();
    void bench2();

    void setNormal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3);
    long long nCr(int n, int r);
    void BezierCurve(double t, float xy[2], int L, GLfloat ctrlpoints[][3]);
    void showControlPoints(int L, GLfloat ctrlpoints[][3]);
    void balloonBezier();
    void drawFlag();
    void balloon();
    void balloonLine();
    void balloons();
    void cart();
    void balloonCart();
    void flagpole(int seed);
    void flags();

    void animateFlag();
};

#endif

