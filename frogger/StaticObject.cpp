#include "StaticObject.h"

StaticObject::StaticObject() : GameObject(1) {}

StaticObject::~StaticObject() {}

StaticObject::StaticObject(float x, float y, float z) : GameObject(1) {
    _position[0] = x;
    _position[1] = y;
    _position[2] = z;
}

void StaticObject::setSize(float x, float y, float z) {
    _sizeCoeficient[0] = x;
    _sizeCoeficient[1] = y;
    _sizeCoeficient[2] = z;
}


float StaticObject::getSize(int pos) {
    return _sizeCoeficient[pos];
}

void StaticObject::draw() {
    Part *body = getPart(SCENARIO);
    body->createCube();
	if(_texPath != "")
	body->addTexture(_iTex, _texPath);
	body->setMaterialBlockName("Materials");
    body->setColor(VSResourceLib::DIFFUSE, _diffColor);
	body->setColor(VSResourceLib::AMBIENT, _ambColor);
    body->setColor(VSResourceLib::SPECULAR, _specColor);
    body->setColor(VSResourceLib::SHININESS, _shininess);
}

void StaticObject::update() {
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    
    //transformations
    Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    Lib::vsml->scale(getSize(X), getSize(Y), getSize(Z));
    Lib::vsml->translate(0, 0, 0);

    getPart(SCENARIO)->render();
    Lib::vsml->popMatrix(VSMathLib::MODEL);
}