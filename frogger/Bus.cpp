#pragma once

#include "Bus.h"
#include "Lib.h"

Bus::Bus(float* speed, int row, int direction) : DynamicObject(speed, row, direction, 5) {
	_body = getPart(0);
	_frontwindow = getPart(1);
	_frontwheels = getPart(2);
	_backwindow = getPart(3);
	_backwheels = getPart(4);

    float bodyColor[RGBA] = {130.0/255.0, 0, 0, 1.0};
    float shininess = 100;

	float windowColor[RGBA] = {0.0, 191.0/255.0, 1.0, 1.0};
	float wheelsColor[RGBA] = {0.3, 0.3, 0.3, 1.0};

	estimateColors(bodyColor);
    setShininess(shininess);

	estimateColors(windowColor, _windowColor[AMBIENT], _windowColor[DIFFUSE], _windowColor[AMBIENT]);
	estimateColors(wheelsColor, _wheelsColor[AMBIENT], _wheelsColor[DIFFUSE], _wheelsColor[AMBIENT]);
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
	else //right
        _position[0] = 35 + r;

	Lib::vsml->pushMatrix(VSMathLib::MODEL);

    _body->createCube();
	_body->setMaterialBlockName("Materials");
	_body->setColor(VSResourceLib::DIFFUSE, _diffColor);
	_body->setColor(VSResourceLib::AMBIENT, _ambColor);
    _body->setColor(VSResourceLib::SPECULAR, _specColor);
    _body->setColor(VSResourceLib::SHININESS, _shininess);

	_frontwindow->createCylinder(BUS_WIDTH - 2*MARGINAL_SPACE, BUS_HEIGHT/2.0, 10);
	_frontwindow->setMaterialBlockName("Materials");
	_frontwindow->setColor(VSResourceLib::AMBIENT, _windowColor[AMBIENT]);
	_frontwindow->setColor(VSResourceLib::DIFFUSE, _windowColor[DIFFUSE]);
	_frontwindow->setColor(VSResourceLib::SPECULAR, _windowColor[SPECULAR]);
	_frontwindow->setColor(VSResourceLib::SHININESS, _shininess);
	
	_frontwheels->createCylinder(BUS_WIDTH - 2*MARGINAL_SPACE, BUS_HEIGHT/6.0, 10);
	_frontwheels->setMaterialBlockName("Materials");
	_frontwheels->setColor(VSResourceLib::AMBIENT, _wheelsColor[AMBIENT]);
	_frontwheels->setColor(VSResourceLib::AMBIENT, _wheelsColor[DIFFUSE]);
	_frontwheels->setColor(VSResourceLib::AMBIENT, _wheelsColor[SPECULAR]);
	_frontwheels->setColor(VSResourceLib::SHININESS, _shininess);

	_backwindow->createCylinder(BUS_WIDTH - 2*MARGINAL_SPACE, BUS_HEIGHT/2.0, 10);
	_backwindow->setMaterialBlockName("Materials");
	_backwindow->setColor(VSResourceLib::AMBIENT, _windowColor[AMBIENT]);
	_backwindow->setColor(VSResourceLib::DIFFUSE, _windowColor[DIFFUSE]);
	_backwindow->setColor(VSResourceLib::SPECULAR, _windowColor[SPECULAR]);
	_backwindow->setColor(VSResourceLib::SHININESS, _shininess);
	
	_backwheels->createCylinder(BUS_WIDTH - 2*MARGINAL_SPACE, BUS_HEIGHT/6.0, 10);
	_backwheels->setMaterialBlockName("Materials");
	_backwheels->setColor(VSResourceLib::AMBIENT, _wheelsColor[AMBIENT]);
	_backwheels->setColor(VSResourceLib::AMBIENT, _wheelsColor[DIFFUSE]);
	_backwheels->setColor(VSResourceLib::AMBIENT, _wheelsColor[SPECULAR]);
	_backwheels->setColor(VSResourceLib::SHININESS, _shininess);

	Lib::vsml->popMatrix(VSMathLib::MODEL);

	updateBoundingBox();
}

void Bus::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-1, _position[2]);
	_box.setMax(_position[0]+BUS_LENGTH, _position[1]+BUS_HEIGHT+0.8, _position[2]+BUS_WIDTH);
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

	//chassis
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate((BUS_LENGTH - BUS_BODYLENGTH)/2.0, 0.5, 0.0);
	Lib::vsml->scale(BUS_BODYLENGTH, BUS_HEIGHT, BUS_WIDTH);
    _body->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	//front window
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(BUS_HEIGHT/2.0, 
		(BUS_HEIGHT/2.0) + 0.6, 
		MARGINAL_SPACE + ((BUS_WIDTH - 2*MARGINAL_SPACE)/2.0));
	Lib::vsml->rotate(90.0, 1,0,0);
	_frontwindow->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	//front wheels
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(BUS_HEIGHT/6.0 + (BUS_HEIGHT/2.0) + 0.2, 
		BUS_HEIGHT/6.0, 
		MARGINAL_SPACE + ((BUS_WIDTH - 2*MARGINAL_SPACE)/2.0));
    Lib::vsml->rotate(90.0, 1,0,0);
	_frontwheels->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	//back window
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate((BUS_HEIGHT/2.0) + BUS_BODYLENGTH, 
		(BUS_HEIGHT/2.0) + 0.5, 
		MARGINAL_SPACE + ((BUS_WIDTH - 2*MARGINAL_SPACE)/2.0));
	Lib::vsml->rotate(90.0, 1,0,0);
	_frontwindow->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	//back wheels
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(BUS_HEIGHT/6.0 + (BUS_HEIGHT/2.0) + BUS_BODYLENGTH-0.2, 
		BUS_HEIGHT/6.0, 
		MARGINAL_SPACE + ((BUS_WIDTH - 2*MARGINAL_SPACE)/2.0));
    Lib::vsml->rotate(90.0, 1, 0, 0);
	_backwheels->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);


	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Bus::move(int delta_t) {
	_position[0] = _position[0] + _speed[0] * delta_t;
}