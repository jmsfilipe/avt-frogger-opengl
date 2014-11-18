#pragma once

#include "Roadside.h"
#include "Lib.h"

Roadside::Roadside(float x, float y, float z) : StaticObject(x, y, z) {
    float colorComponents[3][4] = {
        {191.0/255.0, 191.0/255.0, 191.0/255.0, 1.0}, //ambient component
        {227.0/255.0, 227.0/255.0, 227.0/255.0, 1.0}, //dffuse component
        {250.0/255.0, 250.0/255.0, 250.0/255.0, 1.0} //specular component
    };
    float shininess = 19.0;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);

    setPosition(x, y, z);
    setSize(60.0, 1.0, 5.0);
}

void Roadside::draw() {
    StaticObject::draw();
}

void Roadside::update() {
    StaticObject::update();
}