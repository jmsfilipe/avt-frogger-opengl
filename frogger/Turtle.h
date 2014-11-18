#pragma once

#include "DynamicObject.h"

#define FIRST_TURTLEROW_Z 15.1
#define SCND_TURTLEROW_Z 0.1

class Turtle : public DynamicObject {
public:
	Turtle(float *speed, int row, int direction);
	~Turtle();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};