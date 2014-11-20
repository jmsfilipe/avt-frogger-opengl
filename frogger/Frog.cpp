#pragma once

#include "Frog.h"

Frog::Frog(float* speed) : DynamicObject(speed){
    float frogBodyColor[RGBA] = {10.0/255.0, 163.0/255.0, 56.0/255.0, 1.0};
    float frogBodyShininess = 8.0;

    float frogEyeColor[RGBA] = {1.0, 1.0, 1.0, 1.0};
    float frogIrisColor[RGBA] = {0.0, 0.0, 0.0, 1.0};
    float frogEyeShininess = 30.0;

    float frogBodyPos[XYZ] = {0.0, 0.0, 0.0};

    float frogLeftEyePos[XYZ] = {-0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS};
    float frogRightEyePos[XYZ] = {0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS};

    float frogLeftIris[XYZ] = {-0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS + 0.6*FROG_EYE_RADIUS};
    float frogRightIris[XYZ] = {0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS, 0.75*FROG_BODY_RADIUS + 0.6*FROG_EYE_RADIUS};

    getBody()->addSphericalPart(&frogBodyColor[0], frogBodyShininess, FROG_BODY_RADIUS, frogBodyPos);

    getBody()->addSphericalPart(frogEyeColor, frogEyeShininess, FROG_EYE_RADIUS, frogLeftEyePos);
    getBody()->addSphericalPart(frogEyeColor, frogEyeShininess, FROG_EYE_RADIUS, frogRightEyePos);

    getBody()->addSphericalPart(frogIrisColor, frogEyeShininess, FROG_IRIS_RADIUS, frogLeftIris);
    getBody()->addSphericalPart(frogIrisColor, frogEyeShininess, FROG_IRIS_RADIUS, frogRightIris);

    _box.setMin(_position[0]+FROG_BODY_RADIUS, _position[1]-FROG_BODY_RADIUS, _position[2]-FROG_BODY_RADIUS);
	_box.setMax(_position[0]-FROG_BODY_RADIUS, _position[1]+FROG_BODY_RADIUS, _position[2]+FROG_BODY_RADIUS);
}

void Frog::draw() {

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
    Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->draw();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	_position[2] = ORIG_POS_Z;

	updateBoundingBox();
}

void Frog::updateBoundingBox() {
	_box.setMin(_position[0]-FROG_BODY_RADIUS, _position[1]-FROG_BODY_RADIUS, _position[2]-FROG_BODY_RADIUS);
	_box.setMax(_position[0]+FROG_BODY_RADIUS, _position[1]+FROG_BODY_RADIUS, _position[2]+FROG_BODY_RADIUS);
}


void Frog::update() {
	updateBoundingBox();

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Frog::moveRight(int delta_t) {

	if (_position[0] > RIGHT_LIMIT) 
		_position[0] = _position[0] - _speed[0] * delta_t;
}

void Frog::moveLeft(int delta_t) {

	if (_position[0] < LEFT_LIMIT) 
		_position[X] = _position[X] + _speed[X] * delta_t;
}

void Frog::moveUp(int delta_t) {

	if (_position[2] < UP_LIMIT) 
		_position[2] = _position[2] + _speed[2] * delta_t;
}

void Frog::moveDown(int delta_t) {

	if (_position[2] > DOWN_LIMIT) 
		_position[2] = _position[2] - _speed[2] * delta_t;
}

void Frog::move(double x, double y, double z) {
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
}

void Frog::initialPos() {

	_position[0] = ORIG_POS_X;
	_position[1] = ORIG_POS_Y;
	_position[2] = ORIG_POS_Z;
}

void Frog::assumeSpeed(float x) {

	_speed[0] = x;
	_speed[1] = 0;
	_speed[2] = FROG_SPEED;
}

void Frog::resetSpeed() {

	_speed[0] = FROG_SPEED;
	_speed[1] = 0;
	_speed[2] = FROG_SPEED;
}