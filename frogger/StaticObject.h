#pragma once

#include "GameObject.h"
#define SCENARIO 0

class StaticObject : public GameObject {
    float _sizeCoeficient[3];
public:
    StaticObject();
    StaticObject(float x, float y, float z);
    ~StaticObject();
    float getSize(int pos);
    void setSize(float x, float y, float z);
    virtual void draw();
    virtual void update();
};