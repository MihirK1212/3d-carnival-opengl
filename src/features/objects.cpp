#include "objects.h"

void drawPool()
{

    // glColor3f(0.2,0.2,0.2);

    int tx = -175, ty = 5, tz = 10;

    // right side
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[32]);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(200, -20, 25);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(200, -40, 25);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(200, -40, -25);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(200, -20, -25);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // left side
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[32]);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(175, -20, 25);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(175, -40, 25);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(175, -40, -25);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(175, -20, -25);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // front side
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[32]);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(175, -20, 25);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(175, -40, 25);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(200, -40, 25);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(200, -20, 25);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // back side
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[32]);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(175, -20, -25);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(175, -40, -25);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(200, -40, -25);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(200, -20, -25);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // bottom
    // glColor4f(0.5,0.77,0.87,0.8);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[32]);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(175, -40, 25);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(175, -40, -25);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(200, -40, -25);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(200, -40, 25);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // water
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[33]);
    glPushMatrix();
    glTranslatef(tx,ty,tz);
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(175, -20, 25);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(175, -20, -25);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(200, -20, -25);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(200, -20, 25);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void bush()
{
    quad = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[24]);

    glPushMatrix();
    gluQuadricTexture(quad, 1);
    gluSphere(quad, 1, 100, 100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void tree()
{
    quad = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID2[30]);

    // glPushMatrix();
    // glScalef(1, 2, 1);
    // gluQuadricTexture(quad, 1);
    // gluSphere(quad, 4, 100, 100);
    // glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[29]);
    glPushMatrix();
    glTranslatef(0, -7, 0);
    glRotatef(90, 1, 0, 0);
    gluQuadricTexture(quad, 1);
    gluCylinder(quad, 1, 1, 10, 32, 32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void chair()
{
    // seat part
    glPushMatrix();
    glScalef(0.5, 0.05, 0.5);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();

    // seat left back
    glPushMatrix();
    glTranslatef(0, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();

    // seat right back
    glPushMatrix();
    glTranslatef(1.35, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();

    // seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();

    // seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();

    // seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();

    // seat left front leg
    glPushMatrix();
    glTranslatef(0, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();

    // seat right front leg
    glPushMatrix();
    glTranslatef(1.35, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube(0.8, 0.2, 0.4, 0.4, 0.1, 0.2);
    glPopMatrix();
}

void table()
{
    // // table
    // glPushMatrix();
    // glScalef(4, 0.3, 4);
    // drawSphere(0.8, 0.4, 0.00, 0.4, 0.2, 0);
    // glPopMatrix();

    // table
    glPushMatrix();
    // glScalef(4, 0.3, 4);
    // drawSphere(0.8, 0.4, 0.00, 0.4, 0.2, 0);
    glTranslatef(-2.5, 0, -2);
    glScalef(1.6, 0.3, 1.6);
    drawCube(0.8, 0.4, 0.00, 0.4, 0.2, 0);
    glPopMatrix();

    // stand
    glPushMatrix();
    glScalef(0.1, -1, -0.1);
    drawCube(0, 0, 0, 0, 0, 0.5);
    glPopMatrix();

    // stand bottom
    glPushMatrix();
    glTranslatef(0, -2.8, 0);
    glScalef(1, 0.2, 1);
    drawSphere(1, 0.549, 0.00, 0.5, 0.2745, 0);
    glPopMatrix();
}

void diningSet()
{
    glPushMatrix();
    glTranslatef(0, -16, 0);
    table();
    glPopMatrix();

    for (int i = 0; i <= 360; i += 72)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        glTranslatef(0, -17, -4);
        chair();
        glPopMatrix();
    }
}

void quad1()
{
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(10, 4, 3);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 4, 3);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 3);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10, 0, 3);
    glEnd();
}

void quad2()
{
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0, 8, 5);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 8, 0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0, 0, 5);
    glEnd();
}

void icecreamParlor()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID2[16]);
    glPushMatrix();
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.5, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[17]);
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[18]);

    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, -2);
    glRotatef(90, 1, 0, 0);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[5]);
    glPushMatrix();
    glTranslatef(0, 6, 1);
    glScalef(1, 0.5, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void pizzaHut()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID2[15]);
    glPushMatrix();
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.5, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[22]);
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[4]);
    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, -2);
    glRotatef(90, 1, 0, 0);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[6]);
    glPushMatrix();
    glTranslatef(0, 6, 1);
    glScalef(1, 0.5, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void dunkinDonuts()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID2[19]);
    glPushMatrix();
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.5, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[21]);
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[20]);
    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, -2);
    glRotatef(90, 1, 0, 0);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID2[7]);
    glPushMatrix();
    glTranslatef(0, 6, 1);
    glScalef(1, 0.5, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void cafeteriaFence()
{
    for (float i = -12; i <= 24; i += 4)
    {
        glPushMatrix();
        glTranslatef(-15.5, -17, i);
        glScalef(1, 2, 1);
        bush();
        glPopMatrix();
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[25]);

    glPushMatrix();
    glTranslatef(-17, -20, -16.5);
    glScalef(1, 0.5, 15);
    drawBox();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void cafeteria()
{
    for (float i = -4; i <= 32; i += 12)
    {
        for (float j = 2; j <= 26; j += 12)
        {
            glPushMatrix();
            glTranslatef(40,0,-60);
            glTranslatef(i, 10, j);
            glScalef(1, 1.5, 1);
            diningSet();
            glPopMatrix();
        }
    }

    glPushMatrix();
    glTranslatef(85,0,-40);
    glTranslatef(5, -18, -10);
    glScalef(1.5, 2, 1);
    glRotatef(-90,0,1,0);
    pizzaHut();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12, -18, -10);
    glScalef(1.5, 2, 1);
    icecreamParlor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22, -18, -10);
    glScalef(1.5, 2, 1);
    dunkinDonuts();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13, 0, 5);
    glScalef(2.9, 1, 2.4);
    ground2();
    glPopMatrix();

    cafeteriaFence();

    glPushMatrix();
    glTranslatef(58, 0, 0);
    cafeteriaFence();
    glPopMatrix();
}

void wall()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[31]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(10, 10, 3);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 10, 3);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 3);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10, 0, 3);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void walls()
{
    for (float i = 20; i <= 100; i += 10)
    {
        glPushMatrix();
        glTranslatef(i, -20, 60);
        wall();
        glPopMatrix();
    }

    for (float i = -80; i <= -10; i += 10)
    {
        glPushMatrix();
        glTranslatef(i, -20, 60);
        wall();
        glPopMatrix();
    }

    for (float i = -80; i <= 100; i += 10)
    {
        glPushMatrix();
        glTranslatef(i, -20, -70);
        wall();
        glPopMatrix();
    }

    for (float i = -57; i <= 63; i += 10)
    {
        glPushMatrix();
        glTranslatef(-83, -20, i);
        glRotatef(90, 0, 1, 0);
        wall();
        glPopMatrix();
    }

    for (float i = -57; i <= 63; i += 10)
    {
        glPushMatrix();
        glTranslatef(107, -20, i);
        glRotatef(90, 0, 1, 0);
        wall();
        glPopMatrix();
    }
}

void streetLampbody()
{
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 0.5, 1);
    drawCylinder(0.1, 0.1, 0.1, 0.05, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -19, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(0.1, 0.1, 0.1, 0.05, 0.05, 0.05, 2, 5, 32, 64);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(0.1, 0.1, 0.1, 0.05, 0.05, 0.05, 2, 5, 32, 64);
    glPopMatrix();
}


void streetLight1()
{

    GLfloat no_mat[] = {0.4, 0.3, 0.2, 1.0};
    GLfloat mat_ambient[] = {0.5, 0.2, 0.6, 1.0};
    GLfloat mat_ambient_color[] = {0.2, 0.5, 0.4, 1.0};
    GLfloat mat_diffuse[] = {1.000, 0.443, 0.100, 1.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {1, 1, 1, 1.0};

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(2, 2, 2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchOne == true)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
    
    streetLampbody();
}

void streetLight2()
{
    GLfloat no_mat[] = {0.4, 0.2, 0.0, 1.0};
    GLfloat mat_ambient[] = {0.3, 0.3, 0.5, 1.0};
    GLfloat mat_ambient_color[] = {0.5, 0.5, 0.0, 1.0};
    GLfloat mat_diffuse[] = {0.000, 0.543, 0.100, 1.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {1, 1, 1, 1.0};

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(2, 2, 2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchTwo == true)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

    streetLampbody();
}

void streetLight3()
{

    GLfloat no_mat[] = {0.0, 1.0, 0.4, 1.0};
    GLfloat mat_ambient[] = {0.2, 0.2, 0.1, 1.0};
    GLfloat mat_ambient_color[] = {0.4, 0.6, 0.5, 1.0};
    GLfloat mat_diffuse[] = {0.000, 0.843, 0.000, 1.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {1, 1, 1, 1.0};

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(2, 2, 2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchThree == true)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

    streetLampbody();
}

void streetLight4()
{
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
    GLfloat mat_diffuse[] = {1.000, 0.843, 0.000, 1.0};
    GLfloat high_shininess[] = {100.0};
    GLfloat mat_emission[] = {1, 1, 1, 1.0};

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(2, 2, 2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if (switchFour == true)
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

    streetLampbody();
}

void bench1()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[16]);
    glScalef(2, 0.5, 0.5);
    drawBox();
    glDisable(GL_TEXTURE_2D);
}

void bench2()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[19]);
    glScalef(2, 0.5, 0.5);
    drawBox();
    glDisable(GL_TEXTURE_2D);
}
