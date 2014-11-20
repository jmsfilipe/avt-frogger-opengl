#pragma once

#include "GameObject.h"

class DynamicObject : public GameObject {
protected:
	float _speed[3];
	int _row, _direction;
public:
    enum ObjectDirection {LEFT, RIGHT};

    DynamicObject();
	DynamicObject(float *speed, int row, int direction);
	DynamicObject(float *speed);

	float *getSpeed();
    void setSpeed(float* s);
	void setSpeed(float x, float y, float z);

	float getSpeedX();
	void setSpeedX(float s);

	int getDirection();

    virtual void update();
    virtual void draw();
};

