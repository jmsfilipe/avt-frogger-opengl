#pragma once

#include "StaticObject.h"

class River : public StaticObject {
public:
	River(float x, float y, float z);
	~River();
    void draw();
	void update();
	virtual void updateBoundingBox();
};