#include "Road.h"

#include "Lib.h"

Road::Road(float x, float y, float z) : StaticObject(x, y, z) {
    float colorComponents[3][4] = {
        {45.0/255.0, 48.0/255.0, 46.0/255.0, 1.0}, //ambient component
        {71.0/255.0, 71.0/255.0, 71.0/255.0, 1.0}, //dffuse component
        {0, 0, 0.0, 1.0} //specular component
    };
    float shininess = 128;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);
	setTexture(0, "textures/street.jpg");

    setPosition(x, y, z);
    setSize(60.0, 1.0, 20.0);
}

void Road::draw() {
    StaticObject::draw();
}

void Road::update() {
    StaticObject::update();
}