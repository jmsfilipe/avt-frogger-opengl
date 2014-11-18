#pragma once

#include "Lib.h"

class LightSource {
protected:
	float _ambient[4];
	float _diffuse[4];
	float _specular[4];
	float _position[4];
	float _direction[4];
	double _cutOff;
	double _exponent;
	bool _state;
	int _type;

public:
	enum _num {POINT, SPOTLIGHT, DIRECTIONAL};
	LightSource();
	LightSource(_num type);
	bool getState();
	void setState(bool state);
	void setType(_num type);
	int getType();
	void setPosition(float *pos);
	void setPosition(float x, float y, float z);
	float *getPosition();
	float *getDirection();
	void setDirection(float *pos);
	void setDirection(float x, float y, float z);
	void setCutOff(double cutoff);
	void setExponent(double exponent);
	void setAmbient(float *pos);
	void setAmbient(float x, float y, float z);
	void setDiffuse(float *pos);
	void setDiffuse(float x, float y, float z);
	void setSpecular(float *pos);
	void setSpecular(float x, float y, float z);
};