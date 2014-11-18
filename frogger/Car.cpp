#pragma once

#include "Car.h"
#include "Lib.h"

Car::Car(float* speed, int row, int direction) : DynamicObject(speed, row, direction, 4) {
    _carChassis = getPart(CAR_CHASSIS);
    _carWindow = getPart(CAR_WINDOW);
    _wheels1 = getPart(CAR_FRONT_WHEELS);
    _wheels2 = getPart(CAR_BACK_WHEELS);

    float colorComponents[N_COMPONENTS][RGBA] = {
        {250.0/255.0, 242.0/255.0, 10.0/255.0, 1.0}, //ambient component
        {255.0/255.0, 255.0/255.0, 14.0/255.0, 1.0}, //dffuse component
        {255.0/255.0, 255.0/255.0, 18.0/255.0, 1.0} //specular component
    };
    float shininess = 100;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);

    bodyPartColor[0] = 0;
    bodyPartColor[1] = 191.0/255.0;
    bodyPartColor[2] = 1;
    bodyPartColor[3] = 1;

    wheelsColor[0] = 0.2;
    wheelsColor[1] = 0.2;
    wheelsColor[2] = 0.2;
    wheelsColor[3] = 1;

	
}

Car::~Car(){
}

void Car::draw() {


	switch(_row){
    case CAR_ONE: 
        _position[2] = FIRST_CARROW_Z; 
        break;
	case CAR_TWO: 
        _position[2] = SCND_CARROW_Z;
        break;
	case CAR_THREE: 
        _position[2] = THIRD_CARROW_Z; 
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

    //CHASSIS
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
	//Lib::vsml->translate(_position[0], _position[1], _position[2]);
    //Lib::vsml->scale(CAR_LENGTH,2,CAR_WIDTH);
    _carChassis->createCube();
    _carChassis->setMaterialBlockName("Materials");
	_carChassis->setColor(VSResourceLib::DIFFUSE, _diffColor);
	_carChassis->setColor(VSResourceLib::AMBIENT, _ambColor);
    _carChassis->setColor(VSResourceLib::SPECULAR, _specColor);
    _carChassis->setColor(VSResourceLib::SHININESS, _shininess);
    Lib::vsml->popMatrix(VSMathLib::MODEL);
    
    //WINDOWS
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    _carWindow->createCube();
	_carWindow->setMaterialBlockName("Materials");
    _carWindow->setColor(VSResourceLib::DIFFUSE, bodyPartColor);
    _carWindow->setColor(VSResourceLib::AMBIENT, bodyPartColor);
    _carWindow->setColor(VSResourceLib::SPECULAR, bodyPartColor);
    _carWindow->setColor(VSResourceLib::SHININESS, _shininess);
    Lib::vsml->popMatrix(VSMathLib::MODEL);
    
    //WHEELS FRONT
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    _wheels1->createCylinder(CAR_WIDTH, 0.6, 10);
	_wheels1->setMaterialBlockName("Materials");
    _wheels1->setColor(VSResourceLib::DIFFUSE, wheelsColor);
    _wheels1->setColor(VSResourceLib::AMBIENT, wheelsColor);
    _wheels1->setColor(VSResourceLib::SPECULAR, wheelsColor);
    _wheels1->setColor(VSResourceLib::SHININESS, _shininess);
    Lib::vsml->popMatrix(VSMathLib::MODEL);

	//WHEELS BACK
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    _wheels2->createCylinder(CAR_WIDTH, 0.6, 10);
	_wheels2->setMaterialBlockName("Materials");
    _wheels2->setColor(VSResourceLib::DIFFUSE, wheelsColor);
    _wheels2->setColor(VSResourceLib::AMBIENT, wheelsColor);
    _wheels2->setColor(VSResourceLib::SPECULAR, wheelsColor);
    _wheels2->setColor(VSResourceLib::SHININESS, _shininess);
    Lib::vsml->popMatrix(VSMathLib::MODEL);

    Lib::vsml->popMatrix(VSMathLib::MODEL);

	updateBoundingBox();

}

void Car::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-1, _position[2]);
	_box.setMax(_position[0]+4, _position[1]+1, _position[2]+3.5);
}

void Car::update(){
	
	//left
	if(_direction == 0 && _position[0] > 32){ int r = Lib::random(0,30); _position[0] = -35-r;}

	//right
	if(_direction == 1 && _position[0] < -32){ int r = Lib::random(0,30); _position[0] = 35+r;}

	updateBoundingBox();
	
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[0], _position[1], _position[2]);
	
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(0, 0, 0);
    Lib::vsml->scale(CAR_LENGTH,2,CAR_WIDTH);
	_carChassis->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(CAR_LENGTH/4, 0, 0.1);
    Lib::vsml->scale(CAR_LENGTH/2, 3, CAR_WIDTH-0.2);
	_carWindow->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(3*CAR_LENGTH/4.0f, 0, CAR_WIDTH/2.0f);
    Lib::vsml->scale(1, 1, 1.2);
    Lib::vsml->rotate(90.0, 1, 0, 0);
	_wheels1->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(1*CAR_LENGTH/4.0f, 0, CAR_WIDTH/2.0f);
    Lib::vsml->scale(1, 1, 1.2);
    Lib::vsml->rotate(90.0, 1, 0, 0);
	_wheels2->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Car::move(int delta_t){
	_position[0] = _position[0] + _speed[0] * delta_t;
}