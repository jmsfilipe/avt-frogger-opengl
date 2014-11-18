#include "BodyParts.h"


BodyParts::BodyParts() {
    _parts = std::vector<BodyPart *>();
}

BodyParts::~BodyParts(void) { }

void BodyParts::addCubicPart(float *baseColor, float shininess, float *size, float *posInBody, float rotAngle, float *rot) {
    float auxRot[AXYZ];
    auxRot[ANGLE] = rotAngle;
    auxRot[AX] = rot[X];
    auxRot[AY] = rot[Y];
    auxRot[AZ] = rot[Z];

    _parts.push_back(new CubicBodyPart(baseColor, shininess, size, posInBody, auxRot));
}

void BodyParts::addSphericalPart(float *baseColor, float shininess , float radius, float *posInBody) {
    float auxSize[XYZ];
    auxSize[RADIUS] = radius;
    auxSize[FILLER] = 1.0;
    auxSize[MORE_FILLER] = 1.0;

    float defaultRot[AXYZ];
    defaultRot[ANGLE] = 0.0;
    defaultRot[X] = 1.0;
    defaultRot[Y] = 0.0;
    defaultRot[Z] = 0.0;

    _parts.push_back(new SphericalBodyPart(baseColor, shininess, auxSize, posInBody, defaultRot));
}

void BodyParts::addCylindricPart(float *baseColor, float shininess, float height, float radius, float *posInBody, float rotationAngle, float *rotationAxis) {
    float auxSize[XYZ];
    auxSize[RADIUS] = radius;
    auxSize[HEIGHT] = height;
    auxSize[FILLER] = 1.0;

    float auxRot[AXYZ];
    auxRot[ANGLE] = rotationAngle;
    auxRot[X] = rotationAxis[X];
    auxRot[Y] = rotationAxis[Y];
    auxRot[Z] = rotationAxis[Z];

    _parts.push_back(new CylindricalBodyPart(baseColor, shininess, auxSize, posInBody, auxRot));
}

void BodyParts::draw() {
    for(int i = 0; i < _parts.size(); i++) {
        _parts.at(i)->draw();
    }
}

void BodyParts::update() {
    for(int i = 0; i < _parts.size(); i++) {
        _parts.at(i)->update();
    }
}



