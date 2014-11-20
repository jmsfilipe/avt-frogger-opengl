#pragma once

#include "DynamicObject.h"

class Bus : public DynamicObject {
	VSResSurfRevLib *_body, 
		*_frontwindow, *_backwindow, 
		*_frontwheels, *_backwheels; 
public:
	Bus(float *speed, int row, int direction);
	~Bus();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};