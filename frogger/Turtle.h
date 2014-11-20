#pragma once

#include "DynamicObject.h"

static const float FIRST_TURTLEROW_Z = RIVER_BOTTOM + RIVER_INBETWEEN_SPACE;
static const float SCND_TURTLEROW_Z = FIRST_TURTLEROW_Z + (3*RIVER_ROW_WIDTH);

static const float SHELL_RADIUS = (RIVER_ROW_WIDTH - (RIVER_INBETWEEN_SPACE * 2))/2;
static const float SHELL_HEIGHT = 2.0;
static const float TURTLE_HEAD_RADIUS = SHELL_RADIUS/2.0;

static const float TURTLE_TOTAL_LENGTH = (SHELL_RADIUS + TURTLE_HEAD_RADIUS) * 2;

class Turtle : public DynamicObject {
public:
	Turtle(float *speed, int row, int direction);
	~Turtle();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};