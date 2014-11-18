#include "SphericalBodyPart.h"

SphericalBodyPart::SphericalBodyPart(float *color, float shininess, 
                                     float *size, float *pos, float *rot) : 
BodyPart(color, shininess, size, pos, rot) { }

SphericalBodyPart::SphericalBodyPart(float *ambColor, float *diffColor,
                                     float *specColor, float shininess,
                                     float *size, float *pos, float *rot) : 
BodyPart(ambColor, diffColor, specColor, shininess, size, pos, rot) { }

SphericalBodyPart::~SphericalBodyPart(void) {}

float SphericalBodyPart::getRadius() {
    return getSize(RADIUS);
}

int SphericalBodyPart::getSides() {
    return _sides;
}

void SphericalBodyPart::draw() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    getSurfRev()->createSphere(getRadius(), getSides());
    setupMaterials();
    Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void SphericalBodyPart::update() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    Lib::vsml->translate(getPosition(X), getPosition(Y), getPosition(Z));
    //Lib::vsml->rotate(getRotation(ANGLE), getRotation(AX), getRotation(AY), getRotation(AZ)); //makes no sense for spheres
    //Lib::vsml->scale(getSize(Z), getSize(Z), getSize(Z)); //makes no sense for spheres, just alter the radius
    getSurfRev()->render();
    Lib::vsml->popMatrix(VSMathLib::MODEL);
}
