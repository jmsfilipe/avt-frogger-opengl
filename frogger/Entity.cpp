#pragma once

#include "Entity.h"

Entity::Entity(){
		_position[0] = 0.0f; _position[1] = 0.0f; _position[2] = 0.0f;
}

float* Entity::getPosition(){
	return _position;
}

void Entity::setPosition(float *pos){
	_position[0] = pos[0];
	_position[1] = pos[1];
	_position[2] = pos[2];
}

void Entity::setPosition(float x, float y, float z){
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
}