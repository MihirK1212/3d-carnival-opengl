#include "human.h"

double radian(double angle)
{
    double pi = 3.14159265359;
    return (angle * (pi / 180));
}

void Human::drawCubeBodyPart()
{
    drawCube(0.545, 0.271, 0.075, 0.2725, 0.1355, 0.0375);
}

void Human::drawHuman()
{
    int body_x = human_x, body_y = human_y, body_z = human_z;

    // mainbody
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90 - angle_x), 0, 1, 0);
    glScalef(1.5, 5, 1);
    drawCubeBodyPart();
    glPopMatrix();

    // hand1
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z); // translate to actual position of the human
    glRotatef(-(90 - angle_x), 0, 1, 0);  // rotate w.r.t y axis to simulate orientation of human
    glTranslatef(1.5, 5, 1);              // translate relative to the main body of the human
    glRotatef(hand_angle_1, 1, 0, 0);     // rotate w.r.t x axis to simulate hand movement
    glScalef(0.5, 0.5, 1.5);              // scaling
    glTranslatef(-3, -3, -3);             // take top right corner of box to origin
    drawCubeBodyPart();
    glPopMatrix();

    // hand2
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90 - angle_x), 0, 1, 0);
    glTranslatef(4, 5, 1);
    glRotatef(hand_angle_2, 1, 0, 0);
    glScalef(0.5, 0.5, 1.5);
    glTranslatef(-3, -3, -3);
    drawCubeBodyPart();
    glPopMatrix();

    // leg1
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90 - angle_x), 0, 1, 0);
    glTranslatef(1.5, 0, 2);
    glRotatef(leg_angle_1, 1, 0, 0);
    glScalef(0.5, 2, 0.5);
    glTranslatef(-3, -3, -3);
    drawCubeBodyPart();
    glPopMatrix();

    // leg2
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90 - angle_x), 0, 1, 0);
    glTranslatef(4, 0, 2);
    glRotatef(leg_angle_2, 1, 0, 0);
    glScalef(0.5, 2, 0.5);
    glTranslatef(-3, -3, -3);
    drawCubeBodyPart();
    glPopMatrix();

    Objects obj;

    //balloon body
    matCurve(1, 0, 0);
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glTranslatef(3, 15, -2);
    obj.balloon();
    glPopMatrix();

    //balloon rope
    glPushMatrix();
    glTranslatef(body_x, body_y, body_z);
    glRotatef(-(90-angle_x),0,1,0);
    glTranslatef(2, 4, -2);
    glScalef(1,1.5,1);
    obj.balloonLine();
    glPopMatrix();
}

void Human::move(int key, int x, int y)
{
    double delta_hand = 5, delta_leg = 10;

    switch (key)
    {
        case GLUT_KEY_UP:

            human_x += (cos(radian(angle_x)));
            human_z -= (sin(radian(angle_x)));

            if (!leg_flag)
            {
                if (!leg_coming_back)
                {
                    leg_angle_1 += delta_leg;
                    hand_angle_1 -= (delta_hand);
                    hand_angle_2 += (delta_hand);
                }
                else
                {
                    leg_angle_1 -= delta_leg;
                    hand_angle_1 += (delta_hand);
                    hand_angle_2 -= (delta_hand);
                }

                if (leg_angle_1 <= 0 && leg_coming_back)
                {
                    leg_angle_1 = leg_angle_2 = 0;
                    leg_flag = 1;
                    leg_coming_back = 0;
                }
                else if (leg_angle_1 >= 90 && !leg_coming_back)
                {
                    leg_angle_1 = 90;
                    leg_angle_2 = 0;
                    leg_flag = 0;
                    leg_coming_back = 1;
                }
            }
            else
            {
                if (!leg_coming_back)
                {
                    leg_angle_2 += delta_leg;
                    hand_angle_1 += (delta_hand);
                    hand_angle_2 -= (delta_hand);
                }
                else
                {
                    leg_angle_2 -= delta_leg;
                    hand_angle_1 -= (delta_hand);
                    hand_angle_2 += (delta_hand);
                }

                if (leg_angle_2 <= 0 && leg_coming_back)
                {
                    leg_angle_1 = leg_angle_2 = 0;
                    leg_flag = 0;
                    leg_coming_back = 0;
                }
                else if (leg_angle_2 >= 90 && !leg_coming_back)
                {
                    leg_angle_1 = 0;
                    leg_angle_2 = 90;
                    leg_flag = 1;
                    leg_coming_back = 1;
                }
            }
            break;
            
        case GLUT_KEY_DOWN:
            human_x -= (cos(radian(angle_x)));
            human_z += (sin(radian(angle_x)));
            break;
        case GLUT_KEY_LEFT:
            angle_x = angle_x + 5;
            if (angle_x <= -360 || angle_x >= 360)
            {
                angle_x = 0;
            }
            break;
        case GLUT_KEY_RIGHT:
            angle_x = (angle_x - 5);
            if (angle_x <= -360 || angle_x >= 360)
            {
                angle_x = 0;
            }
            break;
    }
}