#ifndef RIDES_H
#define RIDES_H

#include "../../libs.h"

#include "../shapes/shapes.h"
#include "../../bmpLoader.h"

struct Rides {

    GLfloat alpha;
    GLfloat theta;
    GLfloat orbiterAlpha;
    GLfloat orbiterTheta;
    GLfloat testTheta; 
    GLfloat pirateBoatTheta;
    GLfloat cmOrbiterAlpha;
    GLfloat cmOrbiterTheta; 
    GLfloat skyDropPos;

    Rides() {
        alpha = 0.0; 
        theta = 0.0;
        orbiterAlpha = -45.0;
        orbiterTheta = 0.0;
        testTheta = -45.0;
        pirateBoatTheta = 0.0;
        cmOrbiterAlpha = 0.0;
        cmOrbiterTheta = 0.0;
        skyDropPos = 0.0;
    }

    void rideGround();

    void ferrisWheelSeat();
    void wheel();
    void bulbsOnFerrisWheel();
    void ferrisWheel();

    void rings();
    void orbiter();

    void boatBody();
    void pirateBoat();

    void complexOrbiterUnit();
    void complexOrbiter();

    void skyDropStructure();
    void skyDropSeat();
    void skyDropTexture();
    void skyDropLogo();
    void skyDrop();

    void animateRides(GLboolean skyDropFlag, GLboolean upFlag, GLboolean downFlag1, GLboolean downFlag2, GLboolean downFlag3,
                        GLboolean cmOrbiterFlag, GLboolean pirateBoatFlag, GLboolean pirateBoatCheck, GLboolean fanSwitch, GLboolean orbiterFlag, GLboolean door1);
};



#endif 