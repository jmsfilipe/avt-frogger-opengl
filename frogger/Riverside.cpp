#include "Riverside.h"
#include "Lib.h"

Riverside::Riverside(float x, float y, float z) : StaticObject(x, y, z) {
    float colorComponents[3][4] = {
        {36.0/255.0, 181.0/255.0, 89.0/255.0, 1.0}, //ambient component
        {65.0/255.0, 204.0/255.0, 116.0/255.0, 1.0}, //dffuse component
        {35.0/255.0, 222.0/255.0, 104.0/255.0, 1.0} //specular component
    };
    float shininess = 5.0;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);

    setPosition(x, y, z);
    setSize(60.0, 1.0, 5.0);

	updateBoundingBox();
}

void Riverside::draw() {
    StaticObject::draw();
}

void Riverside::update() {
    StaticObject::update();
}

void Riverside::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-2, _position[2]);
	_box.setMax(_position[0]+60, _position[1]+2, _position[2]+5);
}