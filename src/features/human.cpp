#include "human.h"

void drawHuman()
{
    drawCube(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
}

double radian(double angle)
{
    double pi = 3.14159265359;
    return (angle * (pi / 180));
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

    // //balloon body
    // matCurve(1, 0, 0);
    // glPushMatrix();
    // glTranslatef(body_x, body_y, body_z);
    // glRotatef(-(90-angle_x),0,1,0);
    // glTranslatef(3, 15, -2);
    // balloon();
    // glPopMatrix();

    // //balloon rope
    // glPushMatrix();
    // glTranslatef(body_x, body_y, body_z);
    // glRotatef(-(90-angle_x),0,1,0);
    // glTranslatef(2, 4, -2);
    // glScalef(1,1.5,1);
    // balloonLine();
    // glPopMatrix();
}

