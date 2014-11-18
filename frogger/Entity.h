#pragma once

#include "vsResSurfRevLib.h"
#include "Lib.h"

class Entity {
protected:
	float _position[3]; //TODO:VEC3
public:
	Entity();
	float *getPosition();
	void setPosition(float *pos); //TODO:VEC3
	void setPosition(float x, float y, float z);
};