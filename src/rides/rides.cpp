#include "rides.h"


static GLfloat colors[4][6] =
    {
        {1, 0, 0, 0.5, 0, 0},  // red
        {0, 1, 0, 0, 0.5, 0},  // green
        {0, 0, 1, 0, 0, 0.5},  // blue
        {1, 1, 0, 0.5, 0.5, 0} // yellow
};

double radToDeg(double rad) {
    return rad * 180.0 / M_PI;
}

int sgn(double x) {
    return x>=0 ? 1:-1;
}

vector<double> matrix_mul(vector<vector<double>>&A, vector<double>&p)
{
    int m = A.size() , n = p.size();
    vector<double> res;


    for(int i=0; i<m; i++)
    {
        double sum = 0;

        for(int j=0; j<n; j++)
        {
            sum+=A[i][j]*p[j];
        }

        sum+=A[i][n];

        res.push_back(sum);
    }

    vector<double> ans;
    ans.push_back(res[0]); ans.push_back(res[1]); ans.push_back(res[2]);

    return ans;
}

vector<double> translate(vector<double>&v,double tx,double ty, double tz)
{
    vector<vector<double>> T = {{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
    return matrix_mul(T, v);
}

vector<double> rotate(vector<double>&v,double theta)
{
    theta = radian(theta);
    vector<vector<double>> T = {{cos(theta),0,sin(theta),0},{0,1,0,0},{-sin(theta),0,cos(theta),0},{0,0,0,1}};
    return matrix_mul(T, v);
}

vector<double> scale(vector<double>&v,double sx,double sy, double sz)
{
    vector<vector<double>> T = {{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}};
    return matrix_mul(T, v);
}


vector<double> get_pos(double theta) {

    double pi = 3.14159265359;
    theta = (theta * (pi / 180));

    double x = 10*cos(theta); 
    double z = 10*sin(theta);
    double y = (x*x*x + z*z - 3*x + 4*z)/100;

    return {x,y,z};
}
vector<double> get_tangent(double theta) {


    double pi = 3.14159265359;
    theta = (theta * (pi / 180));

    double x = 10*cos(theta); 
    double z = 10*sin(theta);
    double y = (x*x*x + z*z - 3*x + 4*z)/100;

    double dx = -10*sin(theta);
    double dz =  10*cos(theta);
    double dy = (3*x*x*dx + 2*z*dz - 3*dx + 4*dz)/100;

    return {dx,dy,dz};
}

vector<double> get_angle(double theta) {

    //returns rotation operations to align dx,dy,dz with z axis
    //if we perform reverse of these rotations, then we can align an object which is along z axis with dx,dy,dz

    vector<double> tangent = get_tangent(theta);

    double pi = 3.14159265359;
    theta = (theta * (pi / 180));

    double x = 10*cos(theta); 
    double z = 10*sin(theta);
    double y = (x*x*x + z*z - 3*x + 4*z)/100;

    double dx = tangent[0], dy = tangent[1], dz = tangent[2];

    double norm = sqrt(dx*dx + dy*dy + dz*dz);

    double cos_alpha = abs(dx/norm);
    double cos_gamma = abs(dz/norm);

    double term_x = sqrt(cos_alpha*cos_alpha + cos_gamma*cos_gamma);
    double term_y = cos_gamma/term_x;

    double theta_y =   radToDeg(acos(term_y)); //rotate abt y axis
    double theta_x =   radToDeg(acos(term_x)); //rotate abt x axis

    if(term_x == 0) {
        theta_y = 0;
        theta_x = 90;
    }
    else if(dx>=0 && dz>=0) {
        theta_y = -theta_y; theta_x = sgn(dy)*theta_x; 
    }
    else if(dx>=0) {
        theta_y = -(180 - theta_y); theta_x = sgn(dy)*theta_x; 
    }
    else if(dz>=0) {
        theta_y = theta_y; theta_x = sgn(dy)*theta_x; 
    }
    else {
        theta_y = 180 - theta_y; theta_x = sgn(dy)*theta_x; 
    }

    return {theta_x, theta_y};
}

void Rides::rideFence() {
    
    //fence in the front
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

    //the horizontal lines of the front fence
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

    //fence in the back

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

    // the horizontal lines of the back fence
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

    //fence in the right
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

    //the horizontal lines
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

    //fence in the left
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
}
void Rides::rideGround()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID2[2]); // 2
    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(10, -19.8, 10);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10, -19.8, -10);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-10, -19.8, -10);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-10, -19.8, 10);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

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
    rideGround();
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
    rideGround();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -19.5, 0);
    glScalef(10,0.5,10);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube(0.7, 0.7, 0.7,  0.1,0.1,0.6);
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

    // the sphere
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(2.5, 2.5, 2.5);
    drawSphere(1, 0, 0, 0.5, 0, 0);
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

void Rides::coasterRide()
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
void Rides::track() {

    //left bound
    glPushMatrix();
    glScalef(0.1,0.1,0.1);
    drawCylinder(0.9, 0.9, 0.9, 0.25, 0.25, 0.25);
    glPopMatrix();

    //right bound
    glPushMatrix();
    glTranslatef(2,0,0);
    glScalef(0.1,0.1,0.1);
    drawCylinder(0.9, 0.9, 0.9, 0.25, 0.25, 0.25);
    glPopMatrix();

    double z = 0;

    while(z<2) {
        glPushMatrix();
        glTranslatef(0,0,z);
        glRotatef(90,0,1,0);
        glScalef(0.1,0.1,0.1);
        drawCylinder(0.9, 0.9, 0.9, 0.25, 0.25, 0.25);
        glPopMatrix();
        z++;
    }
}
void Rides::coasterSegment(double theta) {

    vector<double> pos = get_pos(theta);
    vector<double> angle = get_angle(theta);

    glPushMatrix();
    glTranslatef(pos[0],pos[1],pos[2]);

    glRotatef(-angle[1], 0, 1, 0);
    glRotatef(-angle[0], 1, 0, 0);
    glScalef(0.8, 0.8, 0.08);
    glTranslatef(-1,0,0);
    track();
    glPopMatrix();
}
void Rides::pole(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine, GLfloat height)
{
    GLfloat no_mat[] =   {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1.5, 1.5, height, 32, 32);
}
void Rides::coasterPole(double theta) {

    vector<double> pos = get_pos(theta);
    
    glPushMatrix();
    glTranslatef(pos[0],pos[1],pos[2]);
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 0.5, abs(pos[1]+20)/19);
    drawCylinder(0.6, 0.3, 0.4,  0.2725,0.1355,0.0375);
    glPopMatrix();
}
vector<double> Rides::getRollerCoasterViewRef() {
    
    vector<double> pos = get_pos(ride_theta);
    vector<double> tangent = get_tangent(ride_theta);

    double x = pos[0], y = pos[1], z = pos[2];
    double dx = tangent[0], dy = tangent[1], dz = tangent[2];

    double eyeX = x + 0.4*dx;
    double eyeY = y + 0.4*dy;
    double eyeZ = z + 0.4*dz;
    double refX = x - 0.4*dx;
    double refY = y - 0.4*dy;
    double refZ = z - 0.4*dz;

    vector<double> eye = {eyeX, eyeY, eyeZ};
    vector<double> ref = {refX, refY, refZ};

    eye = rotate(eye, 180);
    eye = scale(eye, 1.5, 1.5, 1.5);
    eye = translate(eye, -70, 3, 40);

    ref = rotate(ref, 180);
    ref = scale(ref, 1.5, 1.5, 1.5);
    ref = translate(ref, -70, 3, 40);

    eye[1]+=7;
    ref[1]-=2;

    return {eye[0], eye[1], eye[2], ref[0], ref[1], ref[2]};
}
void Rides::rollerCoaster(Human* human) {

    
    glPushMatrix();

        glRotatef(180,0,1,0);
        
        glPushMatrix();
        glTranslatef(0,5,0);
        glScalef(2, 1, 2);
        rideGround();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,5,0);
        glTranslatef(0, -19.5, 0);
        glScalef(10,0.5,10);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube(0.7, 0.7, 0.7,  0.1,0.1,0.6);
        glPopMatrix(); 

        double poleTheta = 0;

        while(poleTheta<=360) {
            glPushMatrix();
            coasterPole(poleTheta);
            glPopMatrix();

            poleTheta+=57;
        }

        double theta = 0;

        while(theta<=360) {
            
            glPushMatrix();
            coasterSegment(theta);
            glPopMatrix();

            theta+=1;
        }

        vector<double> pos = get_pos(ride_theta);
        vector<double> angle = get_angle(ride_theta);

        GLfloat radial_x = -0.4*cos(radian(ride_theta)), radial_z = -0.4*sin(radian(ride_theta));

        if(human) {
            glPushMatrix();
            glTranslatef(pos[0],pos[1],pos[2]);
            glTranslatef(radial_x, 0 , radial_z);
            glRotatef(-angle[1], 0, 1, 0);
            glRotatef(-angle[0], 1, 0, 0);
            glScalef(0.2,0.2,0.2);
            human->drawHuman();
            glPopMatrix();
        }

        
        //align the boat along the tangent to the track
        glPushMatrix();
        glTranslatef(pos[0],pos[1],pos[2]);
        glRotatef(-angle[1], 0, 1, 0);
        glRotatef(-angle[0], 1, 0, 0);
        glRotatef(90,0,1,0);
        glScalef(0.4,0.4,0.4);
        coasterRide();
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
    rideGround();
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
    rideGround();
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
    rideGround();
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

        ride_theta = ((ride_theta - 1)%360 + 360)%360;
        // ride_theta = (ride_theta + 1)%360;
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