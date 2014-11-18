#include "CylindricalBodyPart.h"


CylindricalBodyPart::CylindricalBodyPart(float *color, float shininess, 
                             float *size, float *pos, float *rot) : 
    BodyPart(color, shininess, size, pos, rot) { }

CylindricalBodyPart::CylindricalBodyPart(float *ambColor, float *diffColor, 
                             float *specColor, float shininess, 
                             float *size, float *pos, float *rot) : 
    BodyPart(ambColor, diffColor, specColor, shininess, size, pos, rot) { }


CylindricalBodyPart::~CylindricalBodyPart(void) {}

void CylindricalBodyPart::draw() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    getSurfRev()->createCylinder(getSize(HEIGHT), getSize(RADIUS), _sides);
    setupMaterials();
    Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void CylindricalBodyPart::update() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    Lib::vsml->translate(getPosition(X), getPosition(Y), getPosition(Z));
    Lib::vsml->rotate(getRotation(ANGLE), getRotation(AX), getRotation(AY), getRotation(AZ));
    //Lib::vsml->scale(getSize(Z), getSize(Z), getSize(Z)); //makes no sense for cylinders, just alter the radius or height
    getSurfRev()->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}
