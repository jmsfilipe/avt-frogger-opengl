#pragma once

#include "vsResSurfRevLib.h"
#include "Lib.h"

class Entity {
protected:
	float _position[XYZ];
public:
	Entity();
	float *getPosition();
	void setPosition(float *pos);
	void setPosition(float x, float y, float z);
};