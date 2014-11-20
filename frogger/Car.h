#pragma once

#include "DynamicObject.h"

#define CAR_LENGTH 4.0

static const float FIRST_CARROW_Z = ROAD_BOTTOM + ROAD_INBETWEEN_SPACE; //row's bottom z + eye candy space
static const float SCND_CARROW_Z = FIRST_CARROW_Z + (2 * ROADLANE_WIDTH);
static const float THIRD_CARROW_Z = SCND_CARROW_Z + ROADLANE_WIDTH;

static const float CAR_WIDTH = ROADLANE_WIDTH - (ROAD_INBETWEEN_SPACE * 2.0);
static const float CAR_CHASSIS_WIDTH = (2.0/3.0) * CAR_WIDTH;
static const float CAR_SIDE_WIDTH = ((1.0/3.0) * CAR_WIDTH)/2.0;
static const float CAR_CHASSIS_HEIGHT = CAR_WIDTH/3.0;
static const float CAR_WHEELS_HEIGHT = (4.0/5.0) * CAR_CHASSIS_HEIGHT; //empirical value
static const float CAR_WHEELS_VISIBLE_HEIGHT = (2.0/3.0) * CAR_WHEELS_HEIGHT;
static const float CAR_WINDOWS_HEIGHT = (3.0/4.0) * CAR_CHASSIS_HEIGHT; //empirical value
static const float CAR_WINDOWS_WIDTH = (2.6/4.0) * CAR_WIDTH;
static const float CAR_SIDE_HEIGTH = 1.0;

class Car : public DynamicObject {
private:
    float bodyPartColor[4], wheelsColor[4];

public:
	Car(float *speed, int row, int direction);
	~Car();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};