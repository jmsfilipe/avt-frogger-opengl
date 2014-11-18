#pragma once

#include "StaticObject.h"

class Road : StaticObject {
public:
	Road(float x, float y, float z);
	~Road();
    void draw();
	void update();
};