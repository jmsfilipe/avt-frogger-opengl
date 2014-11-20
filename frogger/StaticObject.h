#pragma once

#include "GameObject.h"
#define SCENARIO 0

class StaticObject : public GameObject {
protected:
    float _sizeCoeficient[XYZ], _color[RGBA], _shininess;
	int _iTex;
	std::string _texPath;

    float scenarioDefaultRelativePos[XYZ], scenarioDefaultRotAngle, 
        scenarioDefaultRotAxis[XYZ];

public:
    //float* color, float shininess, float *pos, float *size
    StaticObject();
    ~StaticObject();

    float getSize(int dimension);
    void setSize(float *dimensions);

    float *getColor();
    void setColor(float *color);

	void setTexture(int i, std::string path);

    virtual void draw();
    virtual void update();
};