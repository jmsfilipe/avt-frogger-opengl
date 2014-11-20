#pragma once

#include "DynamicObject.h"
#include "Lib.h"

#define ORIG_POS_X 0
#define ORIG_POS_Y 0
#define ORIG_POS_Z -28

static const float FROG_BODY_RADIUS = ROADLANE_WIDTH/3.0;
static const float FROG_EYE_RADIUS = 0.5 * FROG_BODY_RADIUS;
static const float FROG_IRIS_RADIUS = 0.3 * FROG_EYE_RADIUS;

class Frog : public DynamicObject {
public:
	Frog(float *speed);
	~Frog();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void moveRight(int delta_t);
	void moveLeft(int delta_t);
	void moveUp(int delta_t);
	void moveDown(int delta_t);
	void move(double x, double y, double z);
	void initialPos();
	void assumeSpeed(float x);
	void resetSpeed();
};