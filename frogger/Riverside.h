#pragma once

#include "StaticObject.h"

class Riverside : public StaticObject {
public:
	Riverside(float x, float y, float z);
	~Riverside();
    void draw();
	void update();
	virtual void updateBoundingBox();
};