#pragma once

#include "Turtle.h"
#include "Lib.h"

Turtle::Turtle(float* speed, int row, int direction) : DynamicObject(speed, row, direction){
    float shellColor[RGBA] = {2.0/255.0, 79.0/255.0, 17.0/255.0, 1.0};
    float shellShininess = 20.0;

    float headColor[RGBA] = {95.0/255.0, 240.0/255.0, 70.0/255.0, 1.0};
    float headShininess = 8.0;

    float shellBodyPos[XYZ] = {0.0, -(SHELL_HEIGHT/2.0) + 2*MARGINAL_SPACE, 0.0};

    getBody()->addCylindricPart(shellColor, shellShininess, SHELL_HEIGHT, SHELL_RADIUS, shellBodyPos);

    float headDirection = (1 + (-direction * 2)) * (SHELL_RADIUS + 0.5*TURTLE_HEAD_RADIUS);
    float headBodyPos[XYZ] = {headDirection, SHELL_HEIGHT/4.0, 0.0};

    getBody()->addSphericalPart(headColor, headShininess, TURTLE_HEAD_RADIUS, headBodyPos);
}

Turtle::~Turtle(){
}

void Turtle::draw() {

	switch(_row){
    case TURTLE_ONE: 
        _position[Z] = FIRST_TURTLEROW_Z + SHELL_RADIUS;
        break;
	case TURTLE_TWO: 
        _position[Z] = SCND_TURTLEROW_Z + SHELL_RADIUS;
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

	updateBoundingBox();
}

void Turtle::updateBoundingBox(){

/*	_box.setMin(_position[0], _position[1]-1, _position[2]-0.5);
	_box.setMax(_position[0]+4, _position[1]+1, _position[2]+5.3); */
    _box.setMin(_position[X] - SHELL_RADIUS, _position[Y]-SHELL_HEIGHT, _position[Z]);
    _box.setMax(_position[X]+ SHELL_RADIUS, _position[Y] + (2 * MARGINAL_SPACE), _position[Z] + SHELL_RADIUS);
}

void Turtle::update(){

	updateBoundingBox();

	//left
    if(_direction == LEFT && _position[X] > LEFT_LIMIT + TURTLE_TOTAL_LENGTH) {
        int r = Lib::random(0,30); 
        _position[X] = RIGHT_SPAWN_LIMIT - r;
    }

	//right
	if(_direction == RIGHT && _position[X] < RIGHT_LIMIT -TURTLE_TOTAL_LENGTH) {
        int r = Lib::random(0,30); 
        _position[X] = LEFT_SPAWN_LIMIT + r;
    }

	Lib::vsml->pushMatrix(VSMathLib::MODEL);
	Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    getBody()->update();
	Lib::vsml->popMatrix(VSMathLib::MODEL);
}

void Turtle::move(int delta_t){
	_position[X] = _position[X] + _speed[X] * delta_t;
}