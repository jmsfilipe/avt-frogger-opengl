#pragma once

#include "TimberLog.h"
#include "Lib.h"

TimberLog::TimberLog(float* speed, int row, int direction) : DynamicObject(speed, row, direction) {
    float timberlogColor[RGBA] = {97.0/255.0, 50.0/255.0, 0.0/255.0, 0.5};
    float timberlogShininess = 5.0;
    _height = Lib::random(3,8);
    
    float pos[XYZ] = {0.0, 0.0, 0.0};
    float ang = 90.0;
    float rot[XYZ] = {0.0, 0.0, 1.0};

    getBody()->addCylindricPart(timberlogColor, timberlogShininess, _height, LOG_RADIUS, pos, ang, rot);
}

TimberLog::~TimberLog(){
}

void TimberLog::draw() {

	switch(_row) {
	case LOG_THREE: 
		_position[Z] = THIRD_LOGROW_Z; break;
	case LOG_TWO: 
		_position[Z] = SCND_LOGROW_Z; break;
	case LOG_ONE: 
		_position[Z] = FIRST_LOGROW_Z; break;
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

	updateBoundingBox();
}

void TimberLog::updateBoundingBox(){
	//_box.setMin(_position[0]-1, _position[1]-1, _position[2]-1);
	//_box.setMax(_position[0]+_height+2, _position[1]+1, _position[2]+4);
	_box.setMin(_position[X]-1, _position[Y]-(LOG_RADIUS/2.0), _position[Z]-1);
    	_box.setMax(_position[X]+_height+2, _position[Y]+(LOG_RADIUS/2.0), _position[Z]+LOG_RADIUS);
}


void TimberLog::update(){

	updateBoundingBox();

    if(_direction == LEFT && _position[X] > LEFT_LIMIT + _height) {
        int r = Lib::random(0, 30);
        _position[X] = RIGHT_SPAWN_LIMIT - r;
    }

    if(_direction == RIGHT && _position[X] < RIGHT_LIMIT - _height) {
        int r = Lib::random(0, 30);
        _position[X] = LEFT_SPAWN_LIMIT + r;
    }

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void TimberLog::setHeight(int height){
	_height = height;
}

void TimberLog::move(int delta_t){
	_position[X] = _position[X] + _speed[X] * delta_t;
}