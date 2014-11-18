#pragma once

#include "LightSource.h"

LightSource::LightSource(){
}

LightSource::LightSource(LightSource::_num type){
	_type = type;
	_state = false;
}

float * LightSource::getPosition(){
	return _position;
}

float * LightSource::getDirection(){
	return _direction;
}

void LightSource::setType(LightSource::_num type){
	_type = type;
}

int LightSource::getType(){
	return _type;
}
bool LightSource::getState(){
	return _state;
}

void LightSource::setState(bool state){
	_state = state;
}

void LightSource::setPosition(float *pos){
	_position[0] = pos[0];
	_position[1] = pos[1];
	_position[2] = pos[2];
}

void LightSource::setPosition(float x, float y, float z){
	_position[0] = x;
	_position[1] = y;
	_position[2] = z;
}

void LightSource::setDirection(float *dir){
	_direction[0] = dir[0];
	_direction[1] = dir[1];
	_direction[2] = dir[2];
}

void LightSource::setDirection(float x, float y, float z){
	_direction[0] = x;
	_direction[1] = y;
	_direction[2] = z;
}

void LightSource::setCutOff(double cutoff){
	_cutOff = cutoff;
}

void LightSource::setExponent(double exponent){
	_exponent = exponent;
}

void LightSource::setAmbient(float *amb){
	_ambient[0] = amb[0];
	_ambient[1] = amb[1];
	_ambient[2] = amb[2];
}

void LightSource::setAmbient(float x, float y, float z){
	_ambient[0] = x;
	_ambient[1] = y;
	_ambient[2] = z;
}

void LightSource::setDiffuse(float *dif){
	_diffuse[0] = dif[0];
	_diffuse[1] = dif[1];
	_diffuse[2] = dif[2];
}

void LightSource::setDiffuse(float x, float y, float z){
	_diffuse[0] = x;
	_diffuse[1] = y;
	_diffuse[2] = z;
}

void LightSource::setSpecular(float *spec){
	_specular[0] = spec[0];
	_specular[1] = spec[1];
	_specular[2] = spec[2];
}

void LightSource::setSpecular(float x, float y, float z){
	_specular[0] = x;
	_specular[1] = y;
	_specular[2] = z;
}
