#pragma once

#include "DynamicObject.h"

#define BUS_LENGTH 6

static const float FIRST_BUSROW = ROAD_BOTTOM + ROAD_INBETWEEN_SPACE + ROADLANE_WIDTH;
static const float SCND_BUSROW = FIRST_BUSROW + 2*(ROADLANE_WIDTH);

static const float BUS_WIDTH = ROADSIDE_WIDTH - (2*ROAD_INBETWEEN_SPACE);
static const float BUS_MAINBODY_LENGTH = (2.0/3.0) * BUS_LENGTH;
static const float BUS_BUMPERS_HEIGHT = ((1.0/3.0)*BUS_LENGTH)/2.0;
static const float BUS_BUMPERS_LENGTH = BUS_BUMPERS_HEIGHT;

static const float BUS_WINDOWS_RADIUS = BUS_BUMPERS_HEIGHT - MARGINAL_SPACE;
static const float BUS_WINDOWS_WIDTH = BUS_WIDTH - (2*MARGINAL_SPACE);

static const float BUS_WHEELS_RADIUS = BUS_WINDOWS_RADIUS/2.0;
static const float BUS_WHEELS_WIDTH = BUS_WIDTH - (2*MARGINAL_SPACE);

static const float BUS_BODY_HEIGHT = BUS_BUMPERS_HEIGHT * 2.0;
static const float BUS_WHEELS_VISIBLE_HEIGHT = BUS_WHEELS_RADIUS;

class Bus : public DynamicObject {

public:
	Bus(float *speed, int row, int direction);
	~Bus();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};