#ifndef RIDES_H
#define RIDES_H

#include "../../libs.h"

#include "../shapes/shapes.h"
#include "../../bmpLoader.h"
#include "../human/human.h"

struct Rides {

    GLfloat alpha;
    GLfloat theta;

    GLfloat orbiterAlpha;
    GLfloat orbiterTheta;
    
    GLfloat ride_x;
    bool ride_right;

    int ride_theta;

    Rides() {

        alpha = 0.0; 
        theta = 0.0;

        orbiterAlpha = -45.0;
        orbiterTheta = 0.0;

        ride_theta = 0;
    }

    void rideGround();
    void rideFence();

    void orbiterSeat();
    void rings();
    void orbiter();

    void coasterRide();
    void track();
    void coasterSegment(double theta);
    void pole(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine, GLfloat height);
    void coasterPole(double theta);
    vector<double> getRollerCoasterViewRef();
    void rollerCoaster(Human* human);

    void animateRides(GLboolean orbiterFlag, GLboolean rideFlag, GLboolean doorFlag);
};



#endif 