#include "rides.h"


static GLfloat colors[4][6] =
    {
        {1, 0, 0, 0.5, 0, 0},  // red
        {0, 1, 0, 0, 0.5, 0},  // green
        {0, 0, 1, 0, 0, 0.5},  // blue
        {1, 1, 0, 0.5, 0.5, 0} // yellow
};

void Rides::ferrisWheelSeat()
{
    // seat
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glScalef(0.5, 0.2, 1.5);
    drawCube(0.804, 0.361, 0.361, 0.403, 0.1805, 0.1805);
    glPopMatrix();

    // seat belt rod
    glPushMatrix();
    glTranslatef(1.3, 0.7, 0);
    glScalef(0.02, 0.02, 1.5);
    drawCube(0, 0, 0, 0, 0, 0.0);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[4]);

    // back
    glPushMatrix();
    glScalef(0.2, 0.5, 1.5);
    drawBox();
    glPopMatrix();

    // seat right side
    glPushMatrix();
    glScalef(0.5, 0.5, 0.02);
    drawBox();
    glPopMatrix();

    // seat left side
    glPushMatrix();
    glTranslatef(0, 0, 4.445);
    glScalef(0.5, 0.5, 0.02);
    drawBox();
    glPopMatrix();

    // bottom bent part
    glPushMatrix();
    glTranslatef(1.48, -0.5, 0);
    glRotatef(-45, 0, 0, 1);
    glScalef(0.15, 0.02, 1.5);
    drawBox();
    glPopMatrix();

    // bottom straight part
    glPushMatrix();
    glTranslatef(1.8, -0.8, 0);
    // glRotatef(-20, 0, 0, 1);
    glScalef(0.16, 0.02, 1.5);
    drawBox();
    glPopMatrix();

    // bottom farthest part
    glPushMatrix();
    glTranslatef(2.25, -0.8, 0);
    glScalef(0.02, 0.1, 1.5);
    drawBox();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
void Rides::wheel()
{
    glPushMatrix();
    glScalef(1, 1, 2);
    drawSphere(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    drawTorus(1, 1, 0.3, 0.5, 0.5, 0.15, 0.5, 10.0, 32, 64); // 0.859,0.439,0.576, 0.4295,0.2195,0.288
    glPopMatrix();

    // the big lines
    for (int i = 0; i < 180; i += 30)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glScalef(6.6, 0.1, 0.5);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.867, 0.627, 0.867, 0.4335, 0.3135, 0.4335);
        glPopMatrix();
    }
}
void Rides::bulbsOnFerrisWheel()
{
    for (int i = 0; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        drawSphere(1, 1, 1, 0.5, 0.5, 0.5);
        glPopMatrix();
    }

    for (int i = 15; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        drawSphere(1, 0, 0, 0.5, 0, 0);
        glPopMatrix();
    }

    for (int i = 30; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0);
        glScalef(0.5, 0.5, 0.5);
        drawSphere(0, 0, 1, 0, 0, 0.5);
        glPopMatrix();
    }
}
void Rides::ferrisWheel()
{
    // right stand on the back
    glPushMatrix();
    glTranslatef(-.2, 0, -1);
    glRotatef(-75, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    // glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();

    // left stand on the back
    glPushMatrix();
    glTranslatef(-0.6, 0, -1);
    glRotatef(-105, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    // glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();

    // right stand on the front
    glPushMatrix();
    glTranslatef(-.2, 0, 6);
    glRotatef(-75, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    drawCube(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();

    // left stand on the front
    glPushMatrix();
    glTranslatef(-0.6, 0, 6);
    glRotatef(-105, 0, 0, 1);
    glScalef(7, 0.28, 0.1);
    // glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.545, 0.000, 0.545, 0.2725, 0.0, 0.2725);
    glPopMatrix();

    // base stand
    glPushMatrix();
    glTranslatef(0, -19.5, 2.5);
    // glRotatef(-105, 0, 0, 1);
    glScalef(4, 0.5, 3);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
    glPopMatrix();

    // fence in the front
    for (float j = -9; j <= 19; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, 11);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, -16.1, 11);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    /// the horizontal lines of the front fence
    glPushMatrix();
    glTranslatef(4, -17, 11);
    glScalef(10, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, -18, 11);
    glScalef(10, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, -19, 11);
    glScalef(10, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // gate
    glPushMatrix();
    glTranslatef(-15, -20, 11);
    glRotatef(-alpha, 0, 1, 0);
    for (float j = 0; j <= 4; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, 0, 0);
        glScalef(0.1, 1.5, 0.1);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, 4.4, 0.2);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    for (float j = 1; j <= 3; j += 1)
    {
        glPushMatrix();
        glTranslatef(0, j, 0);
        glScalef(1.5, 0.05, 0.1);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();
    }
    glPopMatrix();

    // fence in the back

    for (float j = -15; j <= 19; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, -5);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, -16.1, -5);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(2, -17, -5);
    glScalef(11.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, -18, -5);
    glScalef(11.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, -19, -5);
    glScalef(11.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // fence in the left
    for (float j = -3; j <= 9; j += 2)
    {
        glPushMatrix();
        glTranslatef(-15, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-15, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(-15, -17, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15, -18, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15, -19, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // fence in the right
    for (float j = -3; j <= 9; j += 2)
    {
        glPushMatrix();
        glTranslatef(19, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(19, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(19, -17, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19, -18, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19, -19, 3);
    glScalef(.1, 0.05, 5.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // rotating part
    glPushMatrix();
    glRotatef(-theta, 0, 0, 1);
    glScalef(1.5, 1.5, 1);
    wheel();
    glPushMatrix();
    glTranslatef(0, 0, 5);
    wheel();
    glPopMatrix();

    // bulbs
    glPushMatrix();
    glTranslatef(0, 0, 5.5);
    bulbsOnFerrisWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -0.5);
    bulbsOnFerrisWheel();
    glPopMatrix();

    // the middle line between two spheres
    glPushMatrix();
    glScalef(0.1, 0.05, 1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // the smaller lines in between
    for (int j = 0; j <= 360; j += 30)
    {
        glPushMatrix();
        glRotatef(j, 0, 0, 1);
        for (int i = 1; i <= 7; i++)
        {
            glPushMatrix();
            glTranslatef(i, 0, 0);
            glScalef(0.1, 0.05, 1.5);
            drawCube(0.780, 0.082, 0.522, 0.39, 0.041, 0.261);
            glPopMatrix();
        }
        glPopMatrix();
    }

    // the seats
    for (int i = 0; i < 360; i += 30)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glTranslatef(10, 0, 0.9);
        glRotatef(-i, 0, 0, 1);
        glRotatef(theta, 0, 0, 1);
        glScalef(1, 1, 0.8);
        ferrisWheelSeat();
        glPopMatrix();
    }

    glPopMatrix();

    // ground
    glPushMatrix();
    glTranslatef(2, 0, 0);
    glScalef(2, 1, 1.5);
    ground2();
    glPopMatrix();
}

void Rides::rings()
{
    for (float i = -3.5; i >= -17.5; i -= 1)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(90, 1, 0, 0);
        glScalef(0.2, 0.2, 0.2);
        drawTorus(1, 0, 0, 0.5, 0, 0, 1.5, 7.5, 32, 64);
        glPopMatrix();
    }

    for (float i = -3; i >= -17; i -= 1)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(90, 1, 0, 0);
        glScalef(0.2, 0.2, 0.2);
        drawTorus(1, 1, 1, 0.5, 0.5, 0.5, 1.5, 7.5, 32, 64);
        glPopMatrix();
    }
}
void Rides::orbiter()
{

    glPushMatrix();
    glScalef(2, 1, 2);
    ground2();
    glPopMatrix();
    //the base
    glPushMatrix();
    glTranslatef(0, -19.5, 0);
    glScalef(10,0.5,10);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix(); 

    // the 1st torus at the bottom

    rings();

    glPushMatrix();
    glTranslatef(0, -18, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(1, 1, 1, 0.5, 0.5, 0.5, 2, 8, 32, 64);
    glPopMatrix();

    // the 2nd torus at the bottom
    glPushMatrix();
    glTranslatef(0, -18.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(1, 0, 0, 0.5, 0, 0, 2, 10, 32, 64);
    glPopMatrix();

    /*  //the cylinder stand
      glPushMatrix();
      glTranslatef(0, -3, 0);
      glRotatef(90, 1, 0, 0);
      drawCylinder(0, 1, 0, 0, 0.5, 0);
      glPopMatrix(); */

    // the sphere
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(2.5, 2.5, 2.5);
    drawSphere(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    // fence in the front
    for (float j = -10; j <= 16; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, 17);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, -16.1, 17);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    // the horizontal lines of the front fence
    glPushMatrix();
    glTranslatef(2.5, -17, 17);
    glScalef(9, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, -18, 17);
    glScalef(9, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, -19, 17);
    glScalef(9, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // gate
    glPushMatrix();
    glTranslatef(-15.5, -20, 17);
    glRotatef(-alpha, 0, 1, 0);
    for (float j = 0; j <= 4; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, 0, 0);
        glScalef(0.1, 1.5, 0.1);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, 4.4, 0.2);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    for (float j = 1; j <= 3; j += 1)
    {
        glPushMatrix();
        glTranslatef(0, j, 0);
        glScalef(1.5, 0.05, 0.1);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();
    }
    glPopMatrix();

    // fence in the back

    for (float j = -14; j <= 16; j += 2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, -17);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(j, -16.1, -17);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    /// the horizontal lines of the back fence
    glPushMatrix();
    glTranslatef(0, -17, -17);
    glScalef(10.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -18, -17);
    glScalef(10.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -19, -17);
    glScalef(10.5, 0.05, 0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // fence in the right
    for (float j = -17; j <= 15; j += 2)
    {
        glPushMatrix();
        glTranslatef(16, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(16, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    // the horizontal lines
    glPushMatrix();
    glTranslatef(16, -17, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16, -18, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16, -19, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // fence in the left
    for (float j = -17; j <= 17; j += 2)
    {
        glPushMatrix();
        glTranslatef(-16, -19.5, j);
        glScalef(0.1, 2.5, 0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-16, -16.1, j);
        glScalef(.4, .4, .4);
        drawSphere(0.855, 0.439, 0.839, 0.4275, 0.2195, 0.4195);
        glPopMatrix();
    }

    //
    glPushMatrix();
    glTranslatef(-16, -17, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16, -18, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16, -19, 0);
    glScalef(.1, 0.05, 11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // translating the rotating part down
    glPushMatrix();
    glTranslatef(0, -5, 0);

    // rotating part
    glPushMatrix();
    glRotatef(orbiterTheta, 0, 1, 0);
    // seat
    for (int i = 0; i <= 360; i += 45)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);

        glPushMatrix();
        glRotatef(orbiterAlpha, 0, 0, 1);
        glRotatef(0, 0, 1, 0);
        glTranslatef(15, 0, -2);
        glRotatef(-0, 0, 1, 0);
        glRotatef(-orbiterAlpha, 0, 0, 1);
        ferrisWheelSeat();
        glPopMatrix();

        glPushMatrix();
        glRotatef(orbiterAlpha, 0, 0, 1);
        glScalef(5.1, 0.2, 0.2);
        drawCube(0, 0, 1, 0, 0, 0.5);
        glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();

    glPopMatrix();
}

void Rides::boatBody()
{
    glPushMatrix();
    glTranslatef(-1.3, 0, 0);
    glScalef(3.7, 0.1, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.5, 1.5);
    glScalef(5.5, 1, 0.1);
    glRotatef(180, 0, 0, 1);
    glTranslatef(-1.25, -1.5, -1.25);
    drawTrapezoid(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    // drawTrapezoid(0.4,0.4,0.4, 0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.5, -1.5);
    glScalef(5.5, 1, 0.1);
    glRotatef(180, 0, 0, 1);
    glTranslatef(-1.25, -1.5, -1.25);
    drawTrapezoid(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.5, 1.5, 0);
    glRotatef(-42, 0, 0, 1);
    glScalef(0.1, 1.3, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.1, 1.5, 0);
    glRotatef(42, 0, 0, 1);
    glScalef(0.1, 1.3, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
    glPopMatrix();

    for (float i = -6; i <= 2; i += 2)
    {
        glPushMatrix();
        glTranslatef(i, 0, -1.5);
        glScalef(0.1, 1, 1);
        drawCube(0.412, 0.412, 0.412, 0.0, 0.0, 0.0);
        glPopMatrix();
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[3]);
    glPushMatrix();
    glTranslatef(-6.9, 0, 1.7);
    glScalef(3.7, 1, 0.01);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.9, 0, -1.7);
    glScalef(3.7, 1, 0.01);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void Rides::pirateBoat()
{
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glScalef(1.3, 1, 1.3);
    ground2();
    glPopMatrix();
    // base
    // base stand
    glPushMatrix();
    glTranslatef(0.5, -19.5, 0);
    // glRotatef(-105, 0, 0, 1);
    glScalef(6, 0.5, 4);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
    glPopMatrix();

    // translate down
    glPushMatrix();
    glTranslatef(0, -5.5, 0);

    glPushMatrix();
    glTranslatef(0, 0, -4);
    glScalef(0.2, 0.2, 0.5);
    drawCylinder(1, 0, 0, 0.5, 0, 0.5);
    glPopMatrix();

    // boat body
    glPushMatrix();
    glRotatef(pirateBoatTheta, 0, 0, 1);
    glTranslatef(1.5, -12, 0);
    boatBody();
    glPopMatrix();

    // stand on the front
    glPushMatrix();
    glTranslatef(0, 0, 1.4);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    // left stand
    glPushMatrix();
    glRotatef(-55, 0, 0, 1);
    glScalef(4, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // right stand
    glPushMatrix();
    glRotatef(-125, 0, 0, 1);
    glScalef(4, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPopMatrix();

    // stand on the back
    glPushMatrix();
    glTranslatef(0, 0, -1.6);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    // left stand
    glPushMatrix();
    glRotatef(-55, 0, 0, 1);
    glScalef(4, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // right stand
    glPushMatrix();
    glRotatef(-125, 0, 0, 1);
    glScalef(4, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPopMatrix();

    // base stand at the front
    glPushMatrix();
    glTranslatef(0, 0, 5);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    // left stand
    glPushMatrix();
    glRotatef(-60, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // right stand
    glPushMatrix();
    glRotatef(-120, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.055);
    glPopMatrix();
    glPopMatrix();

    // base stand at the back
    glPushMatrix();
    glTranslatef(0, 0, -5);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    // left stand
    glPushMatrix();
    glRotatef(-60, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // right stand
    glPushMatrix();
    glRotatef(-120, 0, 0, 1);
    glScalef(6, 0.28, 0.1);
    drawCube(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

void Rides::complexOrbiterUnit()
{
    glPushMatrix();
    drawSphere(0, 0, 1, 0, 0, 0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(cmOrbiterTheta, 0, 1, 0);

    int j = 0;
    for (int i = 0; i < 360; i += 90)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);

        glPushMatrix();
        glRotatef(-45, 0, 0, 1);
        glTranslatef(4, 0, -2.4);
        glRotatef(45, 0, 0, 1);
        ferrisWheelSeat();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, -0.5);
        glRotatef(-45, 0, 0, 1);
        glScalef(1.6, 0.2, 0.2);
        drawCube(colors[j][0], colors[j][1], colors[j][2], colors[j][3], colors[j][4], colors[j][5]);
        glPopMatrix();

        glPopMatrix();

        j++;
    }
    glPopMatrix();
}
void Rides::complexOrbiter()
{
    glPushMatrix();
    // glTranslatef(1, 0, 0);
    glScalef(2, 1, 2);
    ground2();
    glPopMatrix();
    /* //the base
     glPushMatrix();
     glTranslatef(0, -19.5, 0);
     glScalef(11,0.5,11);
     glTranslatef(-1.5, -1.5, -1.5);
     //drawBox();
     drawCube(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
     glPopMatrix(); */

    // the sphere
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(2, 2, 2);
    drawSphere(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    // the cylinder stand
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    drawCylinder(0, 1, 0, 0, 0.5, 0.5);
    glPopMatrix();

    // the ride
    glPushMatrix();
    glRotatef(cmOrbiterAlpha, 0, 1, 0);

    for (int i = 0; i < 360; i += 72)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);

        glPushMatrix();
        glTranslatef(0, 0, -0.5);
        glRotatef(-45, 0, 0, 1);
        glScalef(5.8, 0.2, 0.2);
        drawCube(1, 0, 0, 0.5, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(12, -12, 0);
        complexOrbiterUnit();
        glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();
}

void Rides::skyDropStructure()
{
    for (float i = 0; i <= 90; i += 2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glScalef(0.1, 0.1, -1.5);
        drawCube(1, 0, 0, 0.5, 0, 0);
        glPopMatrix();
    }

    for (float i = 0; i <= 87.2; i += 2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(32, 1, 0, 0);
        glScalef(0.1, 0.1, -1.8);
        drawCube(1, 0, 0, 0.5, 0, 0);
        glPopMatrix();
    }

    for (float i = 2.8; i <= 90; i += 2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(-32, 1, 0, 0);
        glScalef(0.1, 0.1, -1.8);
        drawCube(1, 0, 0, 0.5, 0, 0);
        glPopMatrix();
    }
}
void Rides::skyDropSeat()
{
    glPushMatrix();
    glTranslatef(-6, 3.2, 1);

    glPushMatrix();
    glScalef(6, 1.8, 0.2);
    drawCube(1, 1, 0, 0.5, 0.5, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(6, 0.2, 1.2);
    drawCube(1, 1, 0, 0.5, 0.5, 0.5);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 2, 0);
    glScalef(2.2, 0.4, 0.5);
    drawCube(1, 0, 1, 0.5, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 0.5, 0);
    glScalef(0.3, 3, 0.5);
    drawCube(0, 0, 1, 0, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.2, 0.5, 0);
    glScalef(0.3, 3, 0.5);
    drawCube(0, 0, 1, 0, 0.5, 0.5);
    glPopMatrix();

    for (float i = -5.5; i <= 13; i += 2.1)
    {
        glPushMatrix();
        glTranslatef(i, 8, 1.5);
        glRotatef(25, 1, 0, 0);
        glScalef(0.1, 0.1, 0.15);
        drawCylinder(0.412, 0.412, 0.412, 0.2, 0.2, 0.2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i, 6.8, 4);
        glRotatef(90, 1, 0, 0);
        glScalef(0.1, 0.1, 0.19);
        drawCylinder(0.412, 0.412, 0.412, 0.2, 0.2, 0.2);
        glPopMatrix();
    }
}
void Rides::skyDropTexture()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[12]);
    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(2, 0, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2, 20, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void Rides::skyDropLogo()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[13]);
    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(3, 0, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(3, 5, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 5, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void Rides::skyDrop()
{
    for (float i = 0; i <= 5; i += 5)
    {
        glPushMatrix();
        glTranslatef(i, 0, 0);
        glScalef(0.2, 30, 0.2);
        drawCube(0, 0, 1, 0, 0, 0.5);
        glPopMatrix();
    }

    for (float i = 0; i <= 5; i += 5)
    {
        glPushMatrix();
        glTranslatef(i, 0, -5);
        glScalef(0.2, 30, 0.2);
        drawCube(0, 0, 1, 0, 0, 0.5);
        glPopMatrix();
    }

    skyDropStructure();

    glPushMatrix();
    glTranslatef(5, 0, 0);
    skyDropStructure();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7, 0, -5);
    glRotatef(-90, 0, 1, 0);
    skyDropStructure();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, skyDropPos, 0);
    // glTranslatef(-6, 0, 1);
    skyDropSeat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0, 0);
    glScalef(2, 4.5, 1);
    skyDropTexture();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 90, 1);
    glScalef(2.5, 2, 1);
    skyDropLogo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 20, 0);
    ground2();
    glPopMatrix();
}

void Rides::animateRides(GLboolean skyDropFlag, GLboolean upFlag, GLboolean downFlag1, GLboolean downFlag2, GLboolean downFlag3,
                        GLboolean cmOrbiterFlag, GLboolean pirateBoatFlag, GLboolean pirateBoatCheck, GLboolean fanSwitch, GLboolean orbiterFlag, GLboolean door1) {
    
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
}