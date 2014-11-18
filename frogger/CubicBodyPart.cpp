#include "CubicBodyPart.h"


CubicBodyPart::CubicBodyPart(float *color, float shininess, 
                             float *size, float *pos, float *rot) : 
    BodyPart(color, shininess, size, pos, rot) { }

CubicBodyPart::CubicBodyPart(float *ambColor, float *diffColor, 
                             float *specColor, float shininess, 
                             float *size, float *pos, float *rot) : 
    BodyPart(ambColor, diffColor, specColor, shininess, size, pos, rot) { }


CubicBodyPart::~CubicBodyPart(void) { }

void CubicBodyPart::draw() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    getSurfRev()->createCube();
    setupMaterials();
    Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void CubicBodyPart::update() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    Lib::vsml->translate(getPosition(X), getPosition(Y), getPosition(Z));
    Lib::vsml->rotate(getRotation(ANGLE), getRotation(AX), getRotation(AY), getRotation(AZ));
    Lib::vsml->scale(getSize(X), getSize(Y), getSize(Z));
    getSurfRev()->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}