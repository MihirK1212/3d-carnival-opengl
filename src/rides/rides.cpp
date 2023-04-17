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

void Rides::orbiterSeat()
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
            orbiterSeat();
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

        GLfloat radial_x = -0.6*cos(radian(ride_theta)), radial_z = -0.6*sin(radian(ride_theta));

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

void Rides::animateRides(GLboolean orbiterFlag, GLboolean rideFlag, GLboolean doorFlag) {
    
     
    if (rideFlag == true)
    {
        theta += 2;
        if (theta > 360.0)
            theta -= 360.0 * floor(theta / 360.0);

        ride_theta = ((ride_theta - 1)%360 + 360)%360;
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

    if (doorFlag == true)
    {
        alpha += 10;
        if (alpha > 90)
            alpha = 90;
    }
    else if (doorFlag == false)
    {
        alpha -= 10;
        if (alpha < 0)
            alpha = 0;
    }
}