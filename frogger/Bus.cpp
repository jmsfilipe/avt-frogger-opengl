#pragma once

#include "Bus.h"
#include "Lib.h"

Bus::Bus(float* speed, int row, int direction) : DynamicObject(speed, row, direction) {
    float busBodyColor[RGBA] = {224.0/255.0, 31.0/255.0, 31.0/255.0, 1.0};
    float busBodyShininess = 30.0;

    float busWindowsColor[RGBA] = {0.0, 191.0/255.0, 1.0, 1.0};
    float busWindowsShininess = 100.0;

    float busWheelsColor[RGBA] = {0.3, 0.3, 0.3, 1.0};
    float busWheelsShininess = 10.0;

    float busBodySize[XYZ] = {4.0, BUS_BODY_HEIGHT, BUS_WIDTH};
    float busBodyPos[XYZ] = {BUS_BUMPERS_LENGTH, BUS_WHEELS_VISIBLE_HEIGHT, 0.0};

    getBody()->addCubicPart(busBodyColor, busBodyShininess, busBodySize, busBodyPos);

	float busBumperSize[XYZ] = { BUS_BUMPERS_LENGTH, BUS_BUMPERS_HEIGHT, BUS_WIDTH };
	float busFrontBumperPos[XYZ] = { 0.0, BUS_WHEELS_VISIBLE_HEIGHT, 0.0 };
	float busBackBumperPos[XYZ] = { BUS_MAINBODY_LENGTH + BUS_BUMPERS_LENGTH, BUS_WHEELS_VISIBLE_HEIGHT, 0.0 };

	getBody()->addCubicPart(busBodyColor, busBodyShininess, busBumperSize, busFrontBumperPos);
	getBody()->addCubicPart(busBodyColor, busBodyShininess, busBumperSize, busBackBumperPos);

    float busFrontWindowsPos[XYZ] = {BUS_BUMPERS_LENGTH,
        BUS_WHEELS_VISIBLE_HEIGHT + BUS_BUMPERS_HEIGHT, (BUS_WIDTH/2.0) + MARGINAL_SPACE};
	float busBackWindowsPos[XYZ] = { BUS_BUMPERS_LENGTH + BUS_MAINBODY_LENGTH,
        BUS_WHEELS_VISIBLE_HEIGHT + BUS_BUMPERS_HEIGHT, (BUS_WIDTH/2.0) + MARGINAL_SPACE};
    float busWindowsAndWheelsRotAngle = 90.0;
    float busWindowsAndWheelsRotAxis[XYZ] = {1.0, 0.0, 0.0};

    getBody()->addCylindricPart(busWindowsColor, busWindowsShininess,
        BUS_WINDOWS_WIDTH, BUS_WINDOWS_RADIUS, busFrontWindowsPos,
        busWindowsAndWheelsRotAngle, busWindowsAndWheelsRotAxis);

    getBody()->addCylindricPart(busWindowsColor, busWindowsShininess,
        BUS_WINDOWS_WIDTH, BUS_WINDOWS_RADIUS, busBackWindowsPos,
        busWindowsAndWheelsRotAngle, busWindowsAndWheelsRotAxis);

    float busFrontWheelsPos[XYZ] = {BUS_BUMPERS_LENGTH + BUS_WHEELS_RADIUS,
        BUS_WHEELS_VISIBLE_HEIGHT, (BUS_WIDTH/2.0) + MARGINAL_SPACE};
    float busBackWheelsPos[XYZ] = {BUS_BUMPERS_LENGTH + BUS_MAINBODY_LENGTH - BUS_WHEELS_RADIUS,
        BUS_WHEELS_VISIBLE_HEIGHT, (BUS_WIDTH/2.0) + MARGINAL_SPACE};

    getBody()->addCylindricPart(busWheelsColor, busWheelsShininess,
        BUS_WHEELS_WIDTH, BUS_WHEELS_RADIUS, busFrontWheelsPos,
        busWindowsAndWheelsRotAngle, busWindowsAndWheelsRotAxis);

    getBody()->addCylindricPart(busWheelsColor, busWheelsShininess,
        BUS_WHEELS_WIDTH, BUS_WHEELS_RADIUS, busBackWheelsPos,
        busWindowsAndWheelsRotAngle, busWindowsAndWheelsRotAxis);
}

Bus::~Bus() {

}

void Bus::draw() {


	switch(_row){
	case BUS_ONE: 
        _position[Z] = FIRST_BUSROW; 
        break;
	case BUS_TWO: 
        _position[Z] = SCND_BUSROW; 
        break;
	}

	int r = Lib::random(0, 20);

	//left
	if(_direction == LEFT) 
        _position[X] = RIGHT_SPAWN_LIMIT - r;
	else 
        _position[X] = LEFT_SPAWN_LIMIT + r;

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->draw();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	updateBoundingBox();
}

void Bus::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-1, _position[2]);
    _box.setMax(_position[0]+BUS_LENGTH, _position[1]+BUS_BODY_HEIGHT+BUS_WHEELS_VISIBLE_HEIGHT, _position[2]+BUS_WIDTH);
}

void Bus::update() {

	updateBoundingBox();

	//left
    if(_direction == LEFT && _position[X] > LEFT_LIMIT + BUS_LENGTH) {
        int r = Lib::random(0, 30);
        _position[X] = RIGHT_SPAWN_LIMIT - r;
    }

	//right
    if(_direction == RIGHT && _position[X] < RIGHT_LIMIT - BUS_LENGTH) {
        int r = Lib::random(0, 30);
        _position[X] = LEFT_SPAWN_LIMIT + r;
    }

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Bus::move(int delta_t) {
	_position[X] = _position[X] + _speed[X] * delta_t;
}