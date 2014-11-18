#pragma once

#include "DynamicObject.h"

class Bus : public DynamicObject {
public:
	Bus(float *speed, int row, int direction);
	~Bus();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};