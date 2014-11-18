#pragma once

#include "TimberLog.h"
#include "Lib.h"

TimberLog::TimberLog(float* speed, int row, int direction) : DynamicObject(speed, row, direction, 1){
    float colorComponents[N_COMPONENTS][RGBA] = {
        {97.0/255.0, 50.0/255.0, 0.0/255.0, 0.5}, //ambient component
        {106.0/255.0, 55.0/255.0, 36.0/255.0, 0.5}, //dffuse component
        {115.0/255.0, 60.0/255.0, 36.0/255.0, 0.5} //specular component
    };
    float shininess = 5.0;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);


}

TimberLog::~TimberLog(){
}

void TimberLog::draw() {

	switch(_row) {
	case LOG_THREE: 
		_position[2] = THIRD_LOGROW_Z; break;
	case LOG_TWO: 
		_position[2] = SCND_LOGROW_Z; break;
	case LOG_ONE: 
		_position[2] = FIRST_LOGROW_Z; break;
	}
	int r = Lib::random(0, 30);
	//left
	if(_direction == 0) _position[0] = -37-r;
	else _position[0] = 37+r;
	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[0], _position[1], _position[2]);
    getPart(0)->createCylinder(_height,2,10);
	getPart(0)->setMaterialBlockName("Materials");;
	getPart(0)->setColor(VSResourceLib::DIFFUSE, _diffColor);
	getPart(0)->setColor(VSResourceLib::AMBIENT, _ambColor);
    getPart(0)->setColor(VSResourceLib::SPECULAR, _specColor);
    getPart(0)->setColor(VSResourceLib::SHININESS, _shininess);
	Lib::vsml->popMatrix(VSMathLib::MODEL);

	updateBoundingBox();
}

void TimberLog::updateBoundingBox(){
	_box.setMin(_position[0]-1, _position[1]-1, _position[2]-1);
	_box.setMax(_position[0]+_height+2, _position[1]+1, _position[2]+4);
}


void TimberLog::update(){

	updateBoundingBox();

	//left
	if(_direction == 0 && _position[0] > 37){int r = Lib::random(0,30); _position[0] = -37-r;}

	//right
	if(_direction == 1 && _position[0] < -37){ int r = Lib::random(0,30);_position[0] = 37+r;}

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[0], _position[1], _position[2]);
	Lib::vsml->rotate(90,0,0,1);
    getPart(0)->render();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void TimberLog::setHeight(int height){
	_height = height;
}

void TimberLog::move(int delta_t){
	_position[0] = _position[0] + _speed[0] * delta_t;
}