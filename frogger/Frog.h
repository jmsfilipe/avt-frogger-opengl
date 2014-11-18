#pragma once

#include "DynamicObject.h"
#include "Lib.h"

#define ORIG_POS_X 0
#define ORIG_POS_Y 0
#define ORIG_POS_Z -28

class Frog : public DynamicObject {
private:
    VSResSurfRevLib *_frogHead, *_frogBody;
    float bodyPartColor[4];
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