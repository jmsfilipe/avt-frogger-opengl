#include "DynamicObject.h"

DynamicObject::DynamicObject() : GameObject() {
	_speed[0] = 0; _speed[1] = 0; _speed[2] = 0;
}

DynamicObject::DynamicObject(float *speed, int row, int direction) : GameObject(){
	_speed[0] = speed[0]; _speed[1] = speed[1]; _speed[2] = speed[2];
	_row = row;
	_direction = direction;
}

DynamicObject::DynamicObject(float *speed) : GameObject(){
	_speed[0] = speed[0]; _speed[1] = speed[1]; _speed[2] = speed[2];
}

float *DynamicObject::getSpeed() {
	return _speed;
}

float DynamicObject::getSpeedX() {
	return _speed[X];
}

void DynamicObject::setSpeedX(float x) {
	_speed[X]=x;
}

/*int DynamicObject::getDirection(){
	return _direction;
}*/

void DynamicObject::setSpeed(float *s){
	_speed[0] = s[0];
	_speed[1] = s[1];
	_speed[2] = s[2];
}

void DynamicObject::setSpeed(float x, float y, float z){
	_speed[0] = x;
	_speed[1] = y;
	_speed[2] = z;
}

int DynamicObject::getDirection(){
	return _direction;
}

void DynamicObject::update(){
    return;
}

void DynamicObject::draw() {
    return;
}

