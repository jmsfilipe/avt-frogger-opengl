#pragma once

#include "StaticObject.h"

class Roadside : StaticObject {
public:
	Roadside(float x, float y, float z);
	~Roadside();
    void draw();
	void update();
};