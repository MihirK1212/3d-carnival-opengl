#include "../constants.h"

void materialProperty();

static void getNormal3p(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

void matCurve(GLfloat , GLfloat, GLfloat);

void drawCube(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawSphere(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawTorus(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLdouble, GLdouble, GLint, GLint);
void drawCylinder(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawTrapezoid(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawpyramid(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void drawBox();