#include "Body.h"


Body::Body() {
    _bodyParts = std::vector<BodyPart *>();

    defaultPos[X] = 0.0;
    defaultPos[Y] = 0.0;
    defaultPos[Z] = 0.0;

    defaultSize[X] = 1.0;
    defaultSize[Y] = 1.0;
    defaultSize[Z] = 1.0;

    defaultRot[ANGLE] = 0.0;
    defaultRot[AX] = 1.0;
    defaultRot[AY] = 0.0;
    defaultRot[AZ] = 0.0;
}

Body::~Body(void) { }

BodyPart *Body::getBodyPart(int part) {
    return _bodyParts.at(part);
}


void Body::addCubicPart(float *baseColor, float shininess, float *size, float *posInBody, float rotAngle, float *rot) {
    float auxRot[AXYZ];
    auxRot[ANGLE] = rotAngle;
    auxRot[AX] = rot[X];
    auxRot[AY] = rot[Y];
    auxRot[AZ] = rot[Z];

    _bodyParts.push_back(new CubicBodyPart(baseColor, shininess, size, posInBody, auxRot));
}

void Body ::addCubicPart(float *baseColor, float shininess, float *size, float *posInBody) {
    _bodyParts.push_back(new CubicBodyPart(baseColor, shininess, size, posInBody, defaultRot));
}

void Body ::addCubicPart(float *baseColor, float shininess, float *size) {
    _bodyParts.push_back(new CubicBodyPart(baseColor, shininess, size, defaultPos, defaultRot));
}

void Body::addSphericalPart(float *baseColor, float shininess , float radius, float *posInBody) {
    float auxSize[XYZ];
    auxSize[RADIUS] = radius;
    auxSize[FILLER] = 1.0;
    auxSize[MORE_FILLER] = 1.0;

    baseColor[G];

    float defaultRot[AXYZ];
    defaultRot[ANGLE] = 0.0;
    defaultRot[AX] = 1.0;
    defaultRot[AY] = 0.0;
    defaultRot[AZ] = 0.0;

    _bodyParts.push_back(new SphericalBodyPart(baseColor, shininess, auxSize, posInBody, defaultRot));
}

void Body::addCylindricPart(float *baseColor, float shininess, float height, float radius, float *posInBody, float rotationAngle, float *rotationAxis) {
    float auxSize[XYZ];
    auxSize[RADIUS] = radius;
    auxSize[HEIGHT] = height;
    auxSize[FILLER] = 1.0;

    float auxRot[AXYZ];
    auxRot[ANGLE] = rotationAngle;
    auxRot[AX] = rotationAxis[X];
    auxRot[AY] = rotationAxis[Y];
    auxRot[AZ] = rotationAxis[Z];

    _bodyParts.push_back(new CylindricalBodyPart(baseColor, shininess, auxSize, posInBody, auxRot));
}

void Body::addCylindricPart(float *baseColor, float shininess, float height, float radius, float *posInBody) {
    float auxSize[XYZ];
    auxSize[RADIUS] = radius;
    auxSize[HEIGHT] = height;
    auxSize[FILLER] = 1.0;

    float auxRot[AXYZ] = {0.0, 1.0, 0.0, 0.0};

    _bodyParts.push_back(new CylindricalBodyPart(baseColor, shininess, auxSize, posInBody, auxRot));
}

void Body::addCylindricPart(float *baseColor, float shininess, float height, float radius) {
    float auxSize[XYZ];
    auxSize[RADIUS] = radius;
    auxSize[HEIGHT] = height;
    auxSize[FILLER] = 1.0;

    float auxRot[AXYZ] = {0.0, 1.0, 0.0, 0.0};
    float auxPos[XYZ] = {0.0, 0.0, 0.0};

    _bodyParts.push_back(new CylindricalBodyPart(baseColor, shininess, auxSize, auxPos, auxRot));
}

void Body::draw() {
    for(int i = 0; i < _bodyParts.size(); i++) {
        _bodyParts.at(i)->draw();
    }
}

void Body::update() {
    for(int i = 0; i < _bodyParts.size(); i++) {
        _bodyParts.at(i)->update();
    }
}



