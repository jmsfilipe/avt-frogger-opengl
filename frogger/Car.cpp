#pragma once

#include "Car.h"
#include "Lib.h"


Car::Car(float* speed, int row, int direction) : DynamicObject(speed, row, direction) {
    //body parts colors//////////////////////////////////////////////
    float carBodyColor[RGBA] = {250.0/255.0, 242.0/255.0, 10.0/255.0, 1.0};
    float carBodyShininess = 60.0;
    
    float carWindowsColor[RGBA] = {0.0, 191.0/255.0, 1.0, 1.0};
    float carWindowsShininess = 100.0;

    float carWheelsColor[RGBA] = {0.3, 0.3, 0.3, 1.0};
    float carWheelsShininess = 20.0;

	float carHeadlightsColor[RGBA] = { 1.0, 1.0, 1.0, 1.0 };
	float carHeadlightsShininess = 20.0;

    //body parts spatial properties//////////////////////////////////
    //car chassis////////////////////////////////////////////////////
    float carChassisSize[XYZ] = {CAR_LENGTH, CAR_CHASSIS_HEIGHT, CAR_CHASSIS_WIDTH};
    float carChassisBodyPos[XYZ] = {0.0, CAR_WHEELS_VISIBLE_HEIGHT, 0.0};

    getBody()->addCubicPart(carBodyColor, carBodyShininess, carChassisSize, carChassisBodyPos);

    //car sides//////////////////////////////////////////////////////
    float carSideRadius = CAR_SIDE_WIDTH;
    float carSideLength = CAR_LENGTH;
    float carSideRotAngle = 90.0;
    float carSideRot[XYZ] = {0.0, 0.0, 1.0};
	float carLeftSideBodyPos[XYZ] = { carSideLength / 2.0, CAR_SIDE_HEIGTH, (0.2*CAR_CHASSIS_WIDTH) };
    float carRightSideBodyPos[XYZ] = {carSideLength/2.0, CAR_SIDE_HEIGTH, (0.8*CAR_CHASSIS_WIDTH)};

    getBody()->addCylindricPart(carBodyColor, carBodyShininess,
        carSideLength, carSideRadius, carLeftSideBodyPos,
        carSideRotAngle, carSideRot);

    getBody()->addCylindricPart(carBodyColor, carBodyShininess,
        carSideLength, carSideRadius, carRightSideBodyPos,
		carSideRotAngle, carSideRot); 

    //car windows////////////////////////////////////////////////////
    float carWindowsSize[XYZ] = {(2.0/3.0) * CAR_LENGTH, CAR_WINDOWS_HEIGHT, CAR_WINDOWS_WIDTH};
    float carWindowsBodyPos[XYZ] = {((1.0/3.0) * CAR_LENGTH)/2.0, CAR_WHEELS_VISIBLE_HEIGHT + CAR_CHASSIS_HEIGHT, MARGINAL_SPACE};

    getBody()->addCubicPart(carWindowsColor, carWindowsShininess, 
        carWindowsSize, carWindowsBodyPos);

    //car wheels/////////////////////////////////////////////////////
    float carWheelsRadius = CAR_WHEELS_HEIGHT/2.0;
    float carWheelsWidth = CAR_CHASSIS_WIDTH;
    float carWheelsRotAngle = 90.0;
    float carWheelsRot[XYZ] = {1.0, 0.0, 0.0};
    float carFrontWheelsBodyPos[XYZ] = {(0.5/4.0) * CAR_LENGTH, CAR_WHEELS_HEIGHT/2.0, (CAR_CHASSIS_WIDTH/2.0)};
    float carBackWheelsBodyPos[XYZ] = {(3.5/4.0) * CAR_LENGTH, CAR_WHEELS_HEIGHT/2.0, (CAR_CHASSIS_WIDTH/2.0)};

    getBody()->addCylindricPart(carWheelsColor, carWheelsShininess, 
        carWheelsWidth, carWheelsRadius, carFrontWheelsBodyPos, 
        carWheelsRotAngle, carWheelsRot);

    getBody()->addCylindricPart(carWheelsColor, carWheelsShininess, 
        carWheelsWidth, carWheelsRadius, carBackWheelsBodyPos, 
        carWheelsRotAngle, carWheelsRot);

	//car headlights/////////////////////////////////////////////////////
	float carHeadlightsRadius = CAR_WHEELS_HEIGHT / 4.0;
	float carFrontHeadlight1BodyPos[XYZ] = { CAR_LENGTH, CAR_WHEELS_HEIGHT, (9.0/100.0)*CAR_CHASSIS_WIDTH };
	float carFrontHeadlight2BodyPos[XYZ] = {  CAR_LENGTH, CAR_WHEELS_HEIGHT, (91.0 / 100.0)*CAR_CHASSIS_WIDTH };
	float carBackHeadlight1BodyPos[XYZ] = { (1.0/100.0) * CAR_LENGTH, CAR_WHEELS_HEIGHT, (9.0 / 100.0)*CAR_CHASSIS_WIDTH };
	float carBackHeadlight2BodyPos[XYZ] = { (1.0/100.0) * CAR_LENGTH, CAR_WHEELS_HEIGHT, (91.0/100.0)*CAR_CHASSIS_WIDTH };


	getBody()->addSphericalPart(carHeadlightsColor, carHeadlightsShininess,
		carHeadlightsRadius, carFrontHeadlight1BodyPos);

	getBody()->addSphericalPart(carHeadlightsColor, carHeadlightsShininess,
		carHeadlightsRadius, carFrontHeadlight2BodyPos);

	getBody()->addSphericalPart(carHeadlightsColor, carHeadlightsShininess,
		carHeadlightsRadius, carBackHeadlight1BodyPos);

	getBody()->addSphericalPart(carHeadlightsColor, carHeadlightsShininess,
		carHeadlightsRadius, carBackHeadlight2BodyPos);
}

Car::~Car(){
}

void Car::draw() {


	switch(_row){
    case CAR_ONE: 
        _position[Z] = FIRST_CARROW_Z; 
        break;
	case CAR_TWO: 
        _position[Z] = SCND_CARROW_Z;
        break;
	case CAR_THREE: 
        _position[Z] = THIRD_CARROW_Z; 
        break;
	}

	int r = Lib::random(0, 30);

	if(_direction == LEFT) 
        _position[X] = RIGHT_SPAWN_LIMIT - r;
	else 
        _position[X] = LEFT_SPAWN_LIMIT + r;

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->draw();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Car::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-1, _position[2]);
    _box.setMax(_position[0]+CAR_LENGTH, _position[1]+CAR_WHEELS_VISIBLE_HEIGHT+CAR_CHASSIS_HEIGHT, _position[2]+CAR_WIDTH);
}

void Car::update() {
	updateBoundingBox();

    //left
	if(_direction == LEFT && _position[X] > LEFT_LIMIT + CAR_LENGTH) {
        int r = Lib::random(0, 30);
        _position[X] = RIGHT_SPAWN_LIMIT - r;
    }

	//right
	if(_direction == RIGHT && _position[X] < RIGHT_LIMIT - CAR_LENGTH) {
        int r = Lib::random(0, 30);
        _position[X] = LEFT_SPAWN_LIMIT + r;
    }

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Car::move(int delta_t){
	_position[X] = _position[X] + _speed[X] * delta_t;
}