#pragma once

#include "Bus.h"
#include "Lib.h"

Bus::Bus(float* speed, int row, int direction) : DynamicObject(speed, row, direction, 1) {
    float colorComponents[N_COMPONENTS][RGBA] = {
        {130.0/255.0, 0, 0, 1.0}, //ambient component
        {237.0/255.0, 36.0/255.0, 36.0/255.0, 1.0}, //dffuse component
        {255.0/255.0, 36.0/255.0, 36.0/255.0, 1.0} //specular component
    };
    float shininess = 100;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);

}

Bus::~Bus() {

}

void Bus::draw() {


	switch(_row){
	case BUS_ONE: 
        _position[2] = -16.9; 
        break;
	case BUS_TWO: 
        _position[2] = -8.9; 
        break;
	}

	int r = Lib::random(0, 30);

	//left
	if(_direction == 0) 
        _position[0] = -35 + r;
	else 
        _position[0] = 35 + r;

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[0], _position[1], _position[2]);
    getPart(0)->createCube();
	getPart(0)->setMaterialBlockName("Materials");
	getPart(0)->setColor(VSResourceLib::DIFFUSE, _diffColor);
	getPart(0)->setColor(VSResourceLib::AMBIENT, _ambColor);
    getPart(0)->setColor(VSResourceLib::SPECULAR, _specColor);
    getPart(0)->setColor(VSResourceLib::SHININESS, _shininess);
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	updateBoundingBox();
}

void Bus::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-1, _position[2]);
	_box.setMax(_position[0]+5, _position[1]+1, _position[2]+3.8);
}

void Bus::update() {

	updateBoundingBox();

	//left
	if(_direction == 0 && _position[0] > 32) {
        int r = Lib::random(0, 30); 
        _position[0] = -35-r;
    }

	//right
	if(_direction == 1 && _position[0] < -32) {
        int r = Lib::random(0, 30);
        _position[0] = 35-r;
    }

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[0], _position[1], _position[2]);
	Lib::vsml->scale(5, 3, 3.8);
    getPart(0)->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Bus::move(int delta_t) {
	_position[0] = _position[0] + _speed[0] * delta_t;
}