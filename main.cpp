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

#include "bmpLoader.h"
#include "src/shapes/shapes.h"
#include "src/light/light.h"
#include "src/features/rides.h"
#include "src/features/objects.h"
#include "src/features/human.h"


const int nt = 60;
const int ntheta = 20;
const double PI = 3.14159265389;

class point1
{
public:
    point1()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];

void setNormal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(-Nx, -Ny, -Nz);
}

long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

void BezierCurve(double t, float xy[2], int L, GLfloat ctrlpoints[][3])
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i <= L; i++)
    {
        int ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i][0];
        y += coef * ctrlpoints[i][1];
    }
    xy[0] = float(x);
    xy[1] = float(y);

    // return y;
}

void showControlPoints(int L, GLfloat ctrlpoints[][3])
{
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <= L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}

void balloonBezier()
{
    int L = 5;
    GLfloat balloonctrlpoints[6][3] =
        {
            {0.0, 0.0, 0.0}, {0.7, 0.8, 0}, {2, 0.9, 0}, {2.3, 0.5, 0}, {2.5, 0.1, 0}, {2.4, 0, 0}};

    int i, j;
    float x, y, z, r;     // current coordinates
    float x1, y1, z1, r1; // next coordinates
    float theta;

    const float startx = 0, endx = balloonctrlpoints[L][0];
    // number of angular slices
    const float dx = (endx - startx) / nt; // x step size
    const float dtheta = 2 * PI / ntheta;  // angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];
    BezierCurve(t, xy, 5, balloonctrlpoints);
    x = xy[0];
    r = xy[1];
    // rotate about z-axis
    float p1x, p1y, p1z, p2x, p2y, p2z;
    for (i = 0; i < nt; ++i) // step through x
    {
        theta = 0;
        t += dt;
        BezierCurve(t, xy, 5, balloonctrlpoints);
        x1 = xy[0];
        r1 = xy[1];

        // draw the surface composed of quadrilaterals by sweeping theta
        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= ntheta; ++j)
        {
            theta += dtheta;
            double cosa = cos(theta);
            double sina = sin(theta);
            y = r * cosa;
            y1 = r1 * cosa; // current and next y
            z = r * sina;
            z1 = r1 * sina; // current and next z

            // edge from point at x to point at next x
            glVertex3f(x, y, z);

            if (j > 0)
            {
                setNormal(p1x, p1y, p1z, p2x, p2y, p2z, x, y, z);
            }
            else
            {
                p1x = x;
                p1y = y;
                p1z = z;
                p2x = x1;
                p2y = y1;
                p2z = z1;
            }
            glVertex3f(x1, y1, z1);

            // forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } // for i

    if (show == true)
    {
        showControlPoints(L, balloonctrlpoints);
    }
}

void drawFlag()
{
    int L = 3;
    GLfloat ctrlpoints1[4][3] =
        {
            {0, 0, 0}, {3.5, 0 + yf, 0}, {3.5, 0 - yf, 0}, {7 + xf, 0, 0}};

    GLfloat ctrlpoints2[4][3] =
        {
            {0, 5, 0}, {3.5, 5 + yf, 0}, {3.5, 5 - yf, 0}, {7 + xf, 5, 0}};
    int i;
    float x1, y1, x2, y2; // current coordinates
    // float x1, y1, z1, r1;            //next coordinates
    const float startx = 0, endx = ctrlpoints1[L][0];
    float t = 0;
    float xy1[2];
    float xy2[2];
    float dt = 1.0 / nt;
    // glColor3f(0, 0, 1);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < nt; i++)
    {
        BezierCurve(t, xy1, L, ctrlpoints1);
        x1 = xy1[0];
        y1 = xy1[1];
        glVertex3f(x1, y1, 0);
        BezierCurve(t, xy2, L, ctrlpoints2);
        x2 = xy2[0];
        y2 = xy2[1];
        glVertex3f(x2, y2, 0);
        t += dt;
    }

    glEnd();

    if (show == true)
    {
        showControlPoints(L, ctrlpoints1);
        showControlPoints(L, ctrlpoints2);
    }
}

void balloon()
{
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glScalef(2, 2.5, 2);
    balloonBezier();
    glPopMatrix();
}

void balloonLine()
{
    matCurve(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(1, 10);
    glVertex2f(1, 1);
    glEnd();
}

void balloons()
{
    matCurve(1, 0, 0);
    glPushMatrix();
    glTranslatef(3, -10, 0.6);
    balloon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, -19, 0.6);
    balloonLine();
    glPopMatrix();

    matCurve(0, 0, 1);
    glPushMatrix();
    glTranslatef(6.2, -11, 0.6);
    balloon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, -18, 0.6);
    glRotatef(-22, 0, 0, 1);
    balloonLine();
    glPopMatrix();

    matCurve(1, 1, 0);
    glPushMatrix();
    glTranslatef(0, -11, 0.6);
    balloon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, -18, 0.6);
    glRotatef(22, 0, 0, 1);
    balloonLine();
    glPopMatrix();

    matCurve(1, 0.5, 0);
    glPushMatrix();
    glTranslatef(3, -13, 2.6);
    balloon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, -20, 0.6);
    glRotatef(16, 1, 0, 0);
    balloonLine();
    glPopMatrix();

    matCurve(1, 0, 1);
    glPushMatrix();
    glTranslatef(3, -13, -1.8);
    balloon();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, -20, 0.6);
    glRotatef(-14, 1, 0, 0);
    balloonLine();
    glPopMatrix();
}

void cart()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID2[26]);
    glPushMatrix();
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[4]);
    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.25, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void balloonCart()
{
    balloons();

    glPushMatrix();
    glTranslatef(0, -20, 0);
    glScalef(0.5, 0.5, 1);
    cart();
    glPopMatrix();
}

void flagpole()
{
    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 1.5);
    drawCylinder(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glScalef(0.5, 0.5, 0.5);
    drawSphere(.502, 0, 0, 0.26, 0, 0);
    glPopMatrix();

    matCurve(0, 0, 1);
    drawFlag();
}

void flagpole1(int seed)
{
    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 1.5);
    drawCylinder(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glScalef(0.5, 0.5, 0.5);
    drawSphere(.502, 0, 0, 0.26, 0, 0);
    glPopMatrix();

    srand(seed);

    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    matCurve(r1, r2, r3);
    drawFlag();
}

void flagpole2()
{
    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 1.5);
    drawCylinder(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glScalef(0.5, 0.5, 0.5);
    drawSphere(.502, 0, 0, 0.26, 0, 0);
    glPopMatrix();

    matCurve(1, 0.5, 0);
    drawFlag();
}

void flagpole3()
{
    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 1.5);
    drawCylinder(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glScalef(0.5, 0.5, 0.5);
    drawSphere(.502, 0, 0, 0.26, 0, 0);
    glPopMatrix();

    matCurve(1, 0, 1);
    drawFlag();
}

void trees()
{
    
    for (float i = -40; i <= 55; i += 15)
    {
        glPushMatrix();
        glTranslatef(-70, -2, i);
        flagpole1(i);
        glPopMatrix();
    }

    for (float i = -40; i <= 55; i += 15)
    {
        glPushMatrix();
        glTranslatef(100, -2, i);
        flagpole1(i);
        glPopMatrix();
    }
}

void human() 
{
    int body_x = human_x , body_y = human_y, body_z = human_z;

    //mainbody
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glScalef(1.5, 5, 1);
    drawHuman();
    glPopMatrix();

    //hand1
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z); //translate to actual position of the human
    glRotatef(-(90-angle_x),0,1,0); //rotate w.r.t y axis to simulate orientation of human
    glTranslatef(1.5,5,1); //translate relative to the main body of the human
    glRotatef(hand_angle_1,1,0,0); //rotate w.r.t x axis to simulate hand movement
    glScalef(0.5, 0.5, 1.5); //scaling
    glTranslatef(-3,-3,-3); //take top right corner of box to origin
    drawHuman();
    glPopMatrix();

    //hand2
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glTranslatef(4,5,1);
    glRotatef(hand_angle_2,1,0,0);
    glScalef(0.5, 0.5, 1.5);
    glTranslatef(-3,-3,-3);
    drawHuman();
    glPopMatrix();

    //leg1
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glTranslatef(1.5,0,2);
    glRotatef(leg_angle_1,1,0,0);
    glScalef(0.5, 2, 0.5);
    glTranslatef(-3,-3,-3);
    drawHuman();
    glPopMatrix();

    //leg2
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glTranslatef(4,0,2);
    glRotatef(leg_angle_2,1,0,0);
    glScalef(0.5, 2, 0.5);
    glTranslatef(-3,-3,-3);
    drawHuman();
    glPopMatrix();

    //balloon body
    matCurve(1, 0, 0);
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glTranslatef(3, 15, -2);
    balloon();
    glPopMatrix();

    //balloon rope
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glTranslatef(2, 4, -2);
    glScalef(1,1.5,1);
    balloonLine();
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0);

    // glViewport(0, 0, 800, 600);

    glEnable(GL_LIGHTING);

    glPushMatrix();
    sky(eyeX + (0.05 * refX), eyeY + (0.05 * refY), eyeZ + (0.05 * refZ), 250, 250, 250);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);

    spotLight1();
    spotLight2();
    spotLight3();
    spotLight4();
    ground();
    walls();
    trees();
    human();
    drawPool();

    for (float i = -70; i <= -10; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench1();
        glPopMatrix();
    }

    for (float i = -60; i <= -20; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench2();
        glPopMatrix();
    }

    for (float i = 30; i <= 100; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench1();
        glPopMatrix();
    }

    for (float i = 40; i <= 90; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench2();
        glPopMatrix();
    }


    glPushMatrix();
    glTranslatef(-25, 0, 0);
    streetLight1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, 0, 0);
    streetLight2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, 0, 30);
    streetLight3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, 0, 30);
    streetLight4();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 10);
    cafeteria();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65, 0, -30);
    ferrisWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,10);
    glTranslatef(-60, 0, -50);
    orbiter();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, 0, -30);
    complexOrbiter();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, 0, 10);
    pirateBoat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, -20, -40);
    skyDrop();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 0, 40);
    balloonCart();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60, 0, 40);
    balloonCart();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(45, 0, 48);
    balloonCart();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(80, 0, 48);
    balloonCart();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, 0, -3);
    flagpole();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 0, -3);
    flagpole1(0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, 0, -3);
    flagpole2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5, 0, -3);
    flagpole3();
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w': // move eye point upwards along Y axis
        eyeY += 1.0;
        break;
    case 's': // move eye point downwards along Y axis
        eyeY -= 1.0;
        break;
    case 'a': // move eye point left along X axis
        eyeX -= 1.0;
        break;
    case 'd': // move eye point right along X axis
        eyeX += 1.0;
        break;
    case 'o': // zoom out
        eyeZ += 1;
        break;
    case 'i': // zoom in
        eyeZ -= 1;
        break;
    case 'q': // back to default eye point and ref point
        eyeX = 0.0;
        eyeY = 2.0;
        eyeZ = 30.0;
        refX = 0.0;
        refY = 0.0;
        refZ = 0.0;
        break;
    case 'j': // move ref point upwards along Y axis
        refY += 1.0;
        break;
    case 'n': // move ref point downwards along Y axis
        refY -= 1.0;
        break;
    case 'b': // move ref point left along X axis
        refX -= 1.0;
        break;
    case 'm': // move eye point right along X axis
        refX += 1.0;
        break;
    case 'k': // move ref point away from screen/ along z axis
        refZ += 1;
        break;
    case 'l': // move ref point towards screen/ along z axis
        refZ -= 1;
        break;
    case '1': // orbiter
        if (orbiterFlag == false)
        {
            orbiterFlag = true;
            break;
        }
        else if (orbiterFlag == true)
        {
            orbiterFlag = false;
            break;
        }
    case '2': // ferriswheel
        if (fanSwitch == false)
        {
            fanSwitch = true;
            break;
        }
        else
        {
            fanSwitch = false;
            break;
        }
    case '3': // skydrop
        if (skyDropFlag == false)
        {
            skyDropFlag = true;
            break;
        }
        else if (skyDropFlag == true)
        {
            skyDropFlag = false;
            break;
        }
    case '4': // complex orbiter
        if (cmOrbiterFlag == false)
        {
            cmOrbiterFlag = true;
            break;
        }
        else if (cmOrbiterFlag == true)
        {
            cmOrbiterFlag = false;
            break;
        }
    case '5': // pirate boat
        if (pirateBoatFlag == false)
        {
            pirateBoatFlag = true;
            break;
        }
        else if (pirateBoatFlag == true)
        {
            pirateBoatFlag = false;
            break;
        }
    case '6': // spot light 1
        if (switchOne == false)
        {
            switchOne = true;
            glEnable(GL_LIGHT1);
            break;
        }
        else if (switchOne == true)
        {
            switchOne = false;
            glDisable(GL_LIGHT1);
            break;
        }
    case '7': // spot light 2
        if (switchTwo == false)
        {
            switchTwo = true;
            glEnable(GL_LIGHT2);
            break;
        }
        else if (switchTwo == true)
        {
            switchTwo = false;
            glDisable(GL_LIGHT2);
            break;
        }
    case '8': // spot light 3
        if (switchThree == false)
        {
            switchThree = true;
            glEnable(GL_LIGHT3);
            break;
        }
        else if (switchThree == true)
        {
            switchThree = false;
            glDisable(GL_LIGHT3);
            break;
        }
    case '9': // spot light 4
        if (switchFour == false)
        {
            switchFour = true;
            glEnable(GL_LIGHT4);
            break;
        }
        else if (switchFour == true)
        {
            switchFour = false;
            glDisable(GL_LIGHT4);
            break;
        }
    case 'z': // turn on/off fan
        if (show == false)
        {
            show = true;
            break;
        }
        else if (show == true)
        {
            show = false;
            break;
        }
    case 'g': // turn on/off fan
        if (door1 == false)
        {
            door1 = true;
            break;
        }
        else
        {
            door1 = false;
            break;
        }

    case '0': // day/night
        if (day == false)
        {
            day = true;
            glEnable(GL_LIGHT0);
            break;
        }
        else if (day == true)
        {
            day = false;
            glDisable(GL_LIGHT0);
            break;
        }
    case 27: // Escape key
        exit(1);
    }

    glutPostRedisplay();
}

void specialKeyboardFunc(int key, int x, int y)
{
    double delta_hand = 5, delta_leg = 10;

    switch(key)
    {
        
        case GLUT_KEY_UP:

            human_x+=(cos(radian(angle_x)));
            human_z-=(sin(radian(angle_x)));

            if(!leg_flag) {
                if(!leg_coming_back){
                    leg_angle_1+=delta_leg;
                    hand_angle_1-=(delta_hand);
                    hand_angle_2+=(delta_hand);
                }
                else{
                    leg_angle_1-=delta_leg;
                    hand_angle_1+=(delta_hand);
                    hand_angle_2-=(delta_hand);
                }
                
                if(leg_angle_1<=0 && leg_coming_back) {
                    leg_angle_1 = leg_angle_2 = 0;
                    leg_flag = 1;
                    leg_coming_back = 0;
                }
                else if(leg_angle_1>=90 && !leg_coming_back) {
                    leg_angle_1 = 90; leg_angle_2 = 0;
                    leg_flag = 0;
                    leg_coming_back = 1;
                }
            }
            else {
                if(!leg_coming_back){
                    leg_angle_2+=delta_leg;
                    hand_angle_1+=(delta_hand);
                    hand_angle_2-=(delta_hand);
                }
                else{
                    leg_angle_2-=delta_leg;
                    hand_angle_1-=(delta_hand);
                    hand_angle_2+=(delta_hand);
                }
                
                if(leg_angle_2<=0 && leg_coming_back) {
                    leg_angle_1 = leg_angle_2 = 0;
                    leg_flag = 0;
                    leg_coming_back = 0;
                }
                else if(leg_angle_2>=90 && !leg_coming_back) {
                    leg_angle_1 = 0; leg_angle_2 = 90;
                    leg_flag = 1;
                    leg_coming_back = 1;
                }
            }
        break;
        case GLUT_KEY_DOWN:
            human_x-=(cos(radian(angle_x)));
            human_z+=(sin(radian(angle_x)));
        break;
        case GLUT_KEY_LEFT:
            angle_x = angle_x + 5;
            if(angle_x<=-360 || angle_x>=360){angle_x = 0;}
        break;
        case GLUT_KEY_RIGHT:
            angle_x = (angle_x - 5);
            if(angle_x<=-360 || angle_x>=360){angle_x = 0;}
        break;
    }

    glutPostRedisplay();
}

void animate()
{
    if (skyDropFlag == true)
    {
        if (upFlag == true)
        {
            skyDropPos += 0.5;
            if (skyDropPos >= 80)
            {
                upFlag = false;
            }
        }
        else
        {
            if (downFlag1 == true && downFlag2 == false && downFlag3 == false)
            {
                skyDropPos -= 2;
                if (skyDropPos <= 5)
                {
                    upFlag = true;
                    downFlag1 = false;
                    downFlag2 = true;
                    downFlag3 = false;
                }
            }
            else if (downFlag1 == false && downFlag2 == true && downFlag3 == false)
            {
                skyDropPos -= 3;
                if (skyDropPos <= 45)
                {
                    upFlag = true;
                    downFlag1 = false;
                    downFlag2 = false;
                    downFlag3 = true;
                }
            }
            else if (downFlag1 == false && downFlag2 == false && downFlag3 == true)
            {
                skyDropPos -= 4;
                if (skyDropPos <= 15)
                {
                    upFlag = true;
                    downFlag1 = true;
                    downFlag2 = false;
                    downFlag3 = false;
                }
            }
        }
    }
    else
    {
        skyDropPos -= 2;
        if (skyDropPos <= 2)
        {
            skyDropPos = 2;
        }
    }

    if (cmOrbiterFlag == true)
    {
        cmOrbiterTheta += 10;
        cmOrbiterAlpha += 1;
    }

    if (pirateBoatFlag == true)
    {
        if (pirateBoatCheck == true)
        {
            pirateBoatTheta += 2;
            if (pirateBoatTheta == 60)
            {
                pirateBoatCheck = false;
            }
        }
        else
        {
            pirateBoatTheta -= 2;
            if (pirateBoatTheta == -70)
            {
                pirateBoatCheck = true;
            }
        }
    }
    else
    {
        if (pirateBoatTheta < 0)
        {
            pirateBoatTheta += 1;
            if (pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
        else if (pirateBoatTheta > 0)
        {
            pirateBoatTheta -= 1;
            if (pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
    }

    if (fanSwitch == true)
    {
        theta += 2;
        if (theta > 360.0)
            theta -= 360.0 * floor(theta / 360.0);
    }

    if (orbiterFlag == true)
    {
        orbiterTheta += 3;
        if (orbiterTheta > 360.0)
            orbiterTheta -= 360.0 * floor(theta / 360.0);

        orbiterAlpha += 2;
        if (orbiterAlpha >= 45)
            orbiterAlpha = 45;
    }
    else
    {
        orbiterAlpha -= 1;
        if (orbiterAlpha <= -45)
            orbiterAlpha = -45;

        orbiterTheta += 3;
        if (orbiterAlpha == -45)
            orbiterTheta = 0;
    }

    if (door1 == true)
    {
        alpha += 10;
        if (alpha > 90)
            alpha = 90;
    }
    else if (door1 == false)
    {
        alpha -= 10;
        if (alpha < 0)
            alpha = 0;
    }

    if (yflag == true)
    {
        yf += 0.1;
        if (yf >= 2)
        {
            yflag = false;
        }
    }
    else
    {
        yf -= 0.1;
        if (yf <= -2)
        {
            yflag = true;
        }
    }

    if (xflag == true)
    {
        xf += 0.1;
        if (xf >= 0.6)
        { for (float i = -70; i <= -10; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench1();
        glPopMatrix();
    }

    for (float i = -60; i <= -20; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench2();
        glPopMatrix();
    }

    for (float i = 30; i <= 100; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench1();
        glPopMatrix();
    }

    for (float i = 40; i <= 90; i += 20)
    {
        glPushMatrix();
        glTranslatef(i, -20, 55);
        bench2();
        glPopMatrix();
    }
            xflag = false;
        }
    }
    else
    {
        xf -= 0.1;
        if (xf <= -0.6)
        {
            xflag = true;
        }
    }

    glutPostRedisplay();
}

void fullScreen(int w, int h) 
{
    // Prevent a divide by zero, when window is too short;you cant make a window of zero width.
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h; // Calculate aspect ratio of the window

    // Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION); // Use the Projection Matrix
    glLoadIdentity();            // Reset Matrix

    glViewport(0, 0, w, h);            // Set the viewport to be the entire window
    gluPerspective(60, ratio, 1, 500); // Set the correct perspective.
    // glFrustum(-2.5,2.5,-2.5,2.5, ratio, 200);
    glMatrixMode(GL_MODELVIEW); // Get Back to the Modelview
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Demo");

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    // glEnable(GL_LIGHTING);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    light();

    cout << "To move Eye point:" << endl;
    cout << "w: up" << endl;
    cout << "s: down" << endl;
    cout << "a: left" << endl;
    cout << "d: right" << endl;
    cout << "i: zoom in" << endl;
    cout << "o: zoom out" << endl;
    cout << "      " << endl;
    cout << "To move Camera point:" << endl;
    cout << "j: up" << endl;
    cout << "n: down" << endl;
    cout << "b: left" << endl;
    cout << "m: right" << endl;
    cout << "l: move nearer" << endl;
    cout << "k: move far" << endl;
    cout << "      " << endl;
    cout << "Press q to move to default position" << endl;
    cout << "      " << endl;
    cout << "To control Rides: " << endl;
    cout << "1: Orbiter" << endl;
    cout << "2: Ferris Wheel" << endl;
    cout << "3: Sky Drop" << endl;
    cout << "4: Complex Orbiter" << endl;
    cout << "5: Pirate Boat" << endl;
    cout << "      " << endl;
    cout << "To control lights: " << endl;
    cout << "6: Spotlight 1" << endl;
    cout << "7: Spotlight 2" << endl;
    cout << "8: Spotlight 3" << endl;
    cout << "9: Spotlight 4" << endl;
    cout << "      " << endl;
    cout << "Other controls: " << endl;
    cout << "0: Day/Night" << endl;
    cout << "Z: To show control points" << endl;

    LoadTexture2("sgi images/whiteground.sgi", 2);

    LoadTexture2("sgi images/whiteground.sgi", 3);

    LoadTexture2("sgi images/pirate-copy.sgi", 4);

    // LoadTexture2("sgi images/red-metal.sgi", 5);
    LoadTexture2("sgi images/blue_gradient.sgi", 5);

    LoadTexture2("sgi images/baskinrobbinslogo.sgi", 6);
    
    // LoadTexture2("sgi images/pizzahut.sgi", 7);
    LoadTexture2("sgi images/iitindore.sgi", 7);

    LoadTexture2("sgi images/dunkindonuts.sgi", 8);

    // //sky
    // LoadTexture2("sgi images/front.sgi", 9);
    // LoadTexture2("sgi images/left.sgi", 12);
    // LoadTexture2("sgi images/right.sgi", 11);
    // LoadTexture2("sgi images/back.sgi", 10);
    // LoadTexture2("sgi images/up.sgi", 28);
    // LoadTexture2("sgi images/nightsky.sgi", 29);


    LoadTexture2("sgi images/whiteground.sgi", 9);
    LoadTexture2("sgi images/whiteground.sgi", 12);
    LoadTexture2("sgi images/whiteground.sgi", 11);
    LoadTexture2("sgi images/whiteground.sgi", 10);
    LoadTexture2("sgi images/whiteground.sgi", 28);
    LoadTexture2("sgi images/whiteground.sgi", 29);

    LoadTexture2("sgi images/skydrop.sgi", 13);

    LoadTexture2("sgi images/skydroplogo.sgi", 14);

    // LoadTexture2("sgi images/grass.sgi", 15);
    // LoadTexture2("sgi images/whiteground.sgi", 15);
    LoadTexture2("sgi images/sand.sgi", 15);

    // LoadTexture2("sgi images/blackred.sgi", 16);
    LoadTexture2("sgi images/blue_gradient.sgi", 16);

    LoadTexture2("sgi images/pinkblue.sgi", 17);

    LoadTexture2("sgi images/baskin-robin-ad.sgi", 18);

    LoadTexture2("sgi images/de5b9e.sgi", 19);

    LoadTexture2("sgi images/pinkorange.sgi", 20);

    LoadTexture2("sgi images/ff6d0d.sgi", 21);

    LoadTexture2("sgi images/dd.sgi", 22);

    // LoadTexture2("sgi images/pizzahutad.sgi", 23);
    LoadTexture2("sgi images/abhinandan.sgi", 23);

    LoadTexture2("sgi images/bush.sgi", 24);

    LoadTexture2("sgi images/bushflower.sgi", 25);

    LoadTexture2("sgi images/brickwall.sgi", 26);

    LoadTexture2("sgi images/redwhite.sgi", 27);


    

    LoadTexture2("sgi images/treebark.sgi", 30);

    LoadTexture2("sgi images/bush.sgi", 31);

    // LoadTexture2("sgi images/purplewall.sgi", 32);
    LoadTexture2("sgi images/iitindore.sgi", 32);

        LoadTexture2("sgi images/tiles.sgi", 33);

    LoadTexture2("sgi images/water.sgi", 34);

    glutReshapeFunc(fullScreen);
    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(specialKeyboardFunc);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
