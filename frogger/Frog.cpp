#pragma once

#include "Frog.h"

Frog::Frog(float* speed) : DynamicObject(speed, 2){
    _frogBody = getPart(0);
    _frogHead = getPart(1);

    float colorComponents[N_COMPONENTS][RGBA] = {
        {10.0/255.0, 163.0/255.0, 56.0/255.0, 1.0}, //ambient component
        {11.0/255.0, 179.0/255.0, 61.0/255.0, 1.0}, //dffuse component
        {12.0/255.0, 185.0/255.0, 66.0/255.0, 1.0} //specular component
    };
    float shininess = 5.0;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);

	bodyPartColor[0] = 11.0/255.0;
    bodyPartColor[1] = 179.0/255.0;
    bodyPartColor[2] = 61.0/255.0;
    bodyPartColor[3] = 1.0;

	
}

void Frog::draw() {

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
    Lib::vsml->translate(_position[0], _position[1], _position[2]);

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(0, 1, 0);
    _frogBody->createSphere(1.0f, 10);
	_frogBody->setMaterialBlockName("Materials");
	_frogBody->setColor(VSResourceLib::DIFFUSE, bodyPartColor);
	_frogBody->setColor(VSResourceLib::AMBIENT, bodyPartColor);
    _frogBody->setColor(VSResourceLib::SPECULAR, bodyPartColor);
    _frogBody->setColor(VSResourceLib::SHININESS, _shininess);
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(0, 2.0f, 0);
    _frogHead->createSphere(0.8f, 10);
	_frogHead->setMaterialBlockName("Materials");
	_frogHead->setColor(VSResourceLib::DIFFUSE, _diffColor);
	_frogHead->setColor(VSResourceLib::AMBIENT, _ambColor);
    _frogHead->setColor(VSResourceLib::SPECULAR, _specColor);
    _frogHead->setColor(VSResourceLib::SHININESS, _shininess);
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->popMatrix(VSMathLib::MODEL);

	_position[2] = ORIG_POS_Z;

	updateBoundingBox();
}

void Frog::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-1, _position[2]);
	_box.setMax(_position[0]+1, _position[1]+1, _position[2]+1);
}


void Frog::update(){

	updateBoundingBox();


	Lib::vsml->pushMatrix(VSMathLib::MODEL);

	Lib::vsml->translate(_position[0], _position[1], _position[2]);

    //frogBody update
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(0, 1, 0);
	_frogBody->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

    //froghead update
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(0, 2, 0);
	_frogHead->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Frog::moveRight(int delta_t) {

	if (_position[0] > RIGHT_LIMIT) 
		_position[0] = _position[0] - _speed[0] * delta_t;
}

void Frog::moveLeft(int delta_t) {

	if (_position[0] < LEFT_LIMIT) 
		_position[0] = _position[0] + _speed[0] * delta_t;
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