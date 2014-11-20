#include "Riverside.h"
#include "Lib.h"

Riverside::Riverside(float x, float y, float z) : StaticObject() {
    //(float* color, float shininess, float *pos, float *size)
    float auxAbsPos[XYZ] = {x, y, z};
    float auxSize[XYZ] = {BOARD_LENGTH, 1.0, RIVERSIDE_WIDTH};
    float auxColor[RGBA] = {36.0/255.0, 181.0/255.0, 89.0/255.0, 1.0};

    setPosition(auxAbsPos);
    _shininess = 5.0;
    setSize(auxSize);
    setColor(auxColor);

    getBody()->addCubicPart(getColor(), _shininess, _sizeCoeficient,
        scenarioDefaultRelativePos, scenarioDefaultRotAngle, 
        scenarioDefaultRotAxis);
}

void Riverside::draw() {
    StaticObject::draw();
}

void Riverside::update() {
    StaticObject::update();
}

void Riverside::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-2, _position[2]);
	_box.setMax(_position[0]+60, _position[1]+2, _position[2]+5);
}