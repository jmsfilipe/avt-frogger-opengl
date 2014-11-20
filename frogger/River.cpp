#include "River.h"
#include "Lib.h"

River::River(float x, float y, float z) : StaticObject() {
    //(float* color, float shininess, float *pos, float *size)
    float auxAbsPos[XYZ] = {x, y, z};
    float auxSize[XYZ] = {BOARD_LENGTH, 1.0, RIVER_WIDTH};
    float auxColor[RGBA] = {59.0/255.0, 153.0/255.0, 219.0/255.0, 1.0};

    setPosition(auxAbsPos);
    _shininess = 50.0;
    setSize(auxSize);
    setColor(auxColor);
    setTexture(0, "textures/water.jpg");

    getBody()->addCubicPart(getColor(), _shininess, _sizeCoeficient,
        scenarioDefaultRelativePos, scenarioDefaultRotAngle, 
        scenarioDefaultRotAxis);
}

void River::draw() {
    getBody()->getBodyPart(SCENARIO)->getSurfRev()->addTexture(_iTex, _texPath);
    StaticObject::draw();
}

void River::update() {
    updateBoundingBox();
    StaticObject::update();
}

void River::updateBoundingBox(){
	_box.setMin(_position[X], _position[Y]-2, _position[Z]);
	_box.setMax(_position[X]+60, _position[Y]+2, _position[Z]+25);
}
