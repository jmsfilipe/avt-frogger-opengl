#pragma once

#include "DynamicObject.h"

static const float LOG_RADIUS = (RIVER_ROW_WIDTH - (RIVER_INBETWEEN_SPACE * 2.0))/2.0;
static const float FIRST_LOGROW_Z = RIVER_BOTTOM + RIVER_ROW_WIDTH + RIVER_INBETWEEN_SPACE + LOG_RADIUS;
static const float SCND_LOGROW_Z = FIRST_LOGROW_Z + RIVER_ROW_WIDTH;
static const float THIRD_LOGROW_Z = SCND_LOGROW_Z + (2 * RIVER_ROW_WIDTH);

class TimberLog : public DynamicObject {
protected:
    static const int LOG = 0;
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