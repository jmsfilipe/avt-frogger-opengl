#pragma once

#include "GameObject.h"

class DynamicObject : public GameObject {
protected:
	float _speed[3];
	int _row, _direction;
public:
	DynamicObject();
	DynamicObject(int nParts);
	DynamicObject(float *speed, int row, int direction, int nParts);
	DynamicObject(float *speed, int nParts);

	float *getSpeed();
	float getSpeedX();
	void setSpeedX(float s);
	int getDirection();
	void setSpeed(float* s);
	void setSpeed(float x, float y, float z);

    virtual	void update();
    virtual void draw();
};