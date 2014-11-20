#pragma once

#include "DynamicObject.h"

#define BUS_WIDTH 3.8
#define BUS_HEIGHT 3.0
#define BUS_LENGTH 7.0
#define BUS_BODYLENGTH 4.0

class Bus : public DynamicObject {
	VSResSurfRevLib *_body, 
		*_frontwindow, *_backwindow, 
		*_frontwheels, *_backwheels; 

	float _wheelsColor[NCOLOR_COMPONENTS][RGBA];
	float _windowColor[NCOLOR_COMPONENTS][RGBA];
public:
	Bus(float *speed, int row, int direction);
	~Bus();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};