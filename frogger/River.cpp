#include "River.h"
#include "Lib.h"

River::River(float x, float y, float z) : StaticObject(x, y, z) {
    float colorComponents[3][4] = {
        {59.0/255.0, 153.0/255.0, 219.0/255.0, 1.0}, //ambient component
        {100.0/255.0, 175.0/255.0, 227.0/255.0, 1.0}, //dffuse component
        {140.0/255.0, 197.0/255.0, 237.0/255.0, 1.0} //specular component
    };
    float shininess = 50.0;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);
	setTexture(0, "textures/water.jpg");

    setPosition(x, y, z);
    setSize(60.0, 1.0, 25.0);
	
	updateBoundingBox();
}

void River::draw() {
    StaticObject::draw();
}

void River::updateBoundingBox(){
	_box.setMin(_position[0], _position[1]-2, _position[2]);
	_box.setMax(_position[0]+60, _position[1]+2, _position[2]+25);
}


void River::update() {

    StaticObject::update();
}

