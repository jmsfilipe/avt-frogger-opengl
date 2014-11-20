#include "Road.h"

#include "Lib.h"

Road::Road(float x, float y, float z) : StaticObject() {
    //(float* color, float shininess, float *pos, float *size)
    float auxAbsPos[XYZ] = {x, y, z};
    float auxSize[XYZ] = {BOARD_LENGTH, 1.0, ROAD_WIDTH};
    float auxColor[RGBA] = {45.0/255.0, 48.0/255.0, 46.0/255.0, 1.0};

    setPosition(auxAbsPos);
    _shininess = 100;
    setSize(auxSize);
    setColor(auxColor);
    setTexture(0, "textures/street.jpg");

    getBody()->addCubicPart(getColor(), _shininess, _sizeCoeficient,
        scenarioDefaultRelativePos, scenarioDefaultRotAngle, 
        scenarioDefaultRotAxis);
}

void Road::draw() {
    getBody()->getBodyPart(SCENARIO)->getSurfRev()->addTexture(_iTex, _texPath);
    StaticObject::draw();
}

void Road::update() {
    StaticObject::update();
}