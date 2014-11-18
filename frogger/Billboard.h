#pragma once

#include "DynamicObject.h"

class Billboard : public DynamicObject {
private:
    VSResSurfRevLib *_billboard;
    float bodyPartColor[4];
public:
	Billboard(float x, float y, float z);
	~Billboard();
	virtual void draw();
	virtual void update(float angle1, float angle2, float up0, float up1, float up2, float up20, float up21, float up22);
};