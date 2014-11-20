#pragma once

#include "Roadside.h"
#include "Lib.h"

Roadside::Roadside(float x, float y, float z) : StaticObject() {
    //(float* color, float shininess, float *pos, float *size)
    float auxAbsPos[XYZ] = {x, y, z};
    float auxSize[XYZ] = {BOARD_LENGTH, 1.0, ROADSIDE_WIDTH};
    float auxColor[RGBA] = {191.0/255.0, 191.0/255.0, 191.0/255.0, 1.0};

    setPosition(auxAbsPos);
    _shininess = 10;
    setSize(auxSize);
    setColor(auxColor);


    getBody()->addCubicPart(getColor(), _shininess, _sizeCoeficient,
        scenarioDefaultRelativePos, scenarioDefaultRotAngle, 
        scenarioDefaultRotAxis);
}

void Roadside::draw() {
    StaticObject::draw();
}

void Roadside::update() {
    StaticObject::update();
}