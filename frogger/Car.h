#pragma once

#include "DynamicObject.h"

#define FIRST_CARROW_Z -24.9 //row bottom z + eye candy space
#define SCND_CARROW_Z -20.9
#define THIRD_CARROW_Z -12.9

#define CAR_WIDTH 3.5
#define CAR_LENGTH 4

#define CAR_CHASSIS 0
#define CAR_WINDOW 1
#define CAR_FRONT_WHEELS 2
#define CAR_BACK_WHEELS 3

class Car : public DynamicObject {
private:
    VSResSurfRevLib *_carChassis, *_carWindow, *_wheels1, *_wheels2;
    float bodyPartColor[4], wheelsColor[4];
public:
	Car(float *speed, int row, int direction);
	~Car();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void move(int delta_t);
};