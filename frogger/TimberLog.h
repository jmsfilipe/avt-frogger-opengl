#pragma once

#include "DynamicObject.h"

#define FIRST_LOGROW_Z 7.5 //row bottom z + eye candy space + log radius
#define SCND_LOGROW_Z 12.5
#define THIRD_LOGROW_Z 22.5

class TimberLog : public DynamicObject {
protected:
	int _height;
public:
	TimberLog(float *speed, int row, int direction);
	~TimberLog();
	virtual void draw();
	virtual void update();
	virtual void updateBoundingBox();
	void setHeight(int h);
	void move(int delta_t);
};