#include "StaticObject.h"

StaticObject::StaticObject() : GameObject() {
    scenarioDefaultRelativePos[X] = 0.0;
    scenarioDefaultRelativePos[Y] = 0.0;
    scenarioDefaultRelativePos[Z] = 0.0;

    scenarioDefaultRotAngle = 0.0;
    scenarioDefaultRotAxis[X] = 1.0;
    scenarioDefaultRotAxis[Y] = 0.0;
    scenarioDefaultRotAxis[Z] = 0.0;
}

StaticObject::~StaticObject() {}

void StaticObject::setSize(float *dimensions) {
    _sizeCoeficient[X] = dimensions[X];
    _sizeCoeficient[Y] = dimensions[Y];
    _sizeCoeficient[Z] = dimensions[Z];
}

float StaticObject::getSize(int dimension) {
    return _sizeCoeficient[dimension];
}

float *StaticObject::getColor() {
    return _color;
}

void StaticObject::setColor(float *color) {
    _color[R] = color[R];
    _color[G] = color[G];
    _color[B] = color[B];
    _color[A] = color[A];
}



void StaticObject::setTexture(int i, std::string path) {
	_iTex=i;
	_texPath = path;
}

void StaticObject::draw() {
    getBody()->draw();
}

void StaticObject::update() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    
    Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->update();

    Lib::vsml->popMatrix(VSMathLib::MODEL);
}