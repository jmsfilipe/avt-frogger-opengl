#pragma once

#include "Turtle.h"
#include "Lib.h"

Turtle::Turtle(float* speed, int row, int direction) : DynamicObject(speed, row, direction, 1){
    float bodyColor[RGBA] = {2.0/255.0, 79.0/255.0, 17.0/255.0, 1.0};
    float shininess = 9.0;

	estimateColors(bodyColor);
    setShininess(shininess);
}

Turtle::~Turtle(){
}

void Turtle::draw() {

	switch(_row){
    case TURTLE_ONE: 
        _position[2] = FIRST_TURTLEROW_Z; break;
	case TURTLE_TWO: 
        _position[2] = SCND_TURTLEROW_Z; break;
	}

	int r = Lib::random(0, 30);

	//left
	if(_direction == 0) _position[0] = -35 + r;
	else _position[0] = 35 + r;

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[0], _position[1], _position[2]);
	getPart(0)->createCylinder(2.0, RIVER_ROW_WIDTH/2.0, 15);
	getPart(0)->setMaterialBlockName("Materials");
	getPart(0)->setColor(VSResourceLib::DIFFUSE, _diffColor);
	getPart(0)->setColor(VSResourceLib::AMBIENT, _ambColor);
    getPart(0)->setColor(VSResourceLib::SPECULAR, _specColor);
    getPart(0)->setColor(VSResourceLib::SHININESS, _shininess);
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	updateBoundingBox();
}

void Turtle::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-1, _position[2]-0.5);
	_box.setMax(_position[0]+4, _position[1]+1, _position[2]+5.3);
}

void Turtle::update(){

	updateBoundingBox();

	//left
	if(_direction == 0 && _position[0] > 32){int r = Lib::random(0,30); _position[0] = -35-r;}

	//right
	if(_direction == 1 && _position[0] < -32){int r = Lib::random(0,30); _position[0] = 35+r;}

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[0], _position[1], _position[2]);
    getPart(0)->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Turtle::move(int delta_t){
	_position[0] = _position[0] + _speed[0] * delta_t;
}