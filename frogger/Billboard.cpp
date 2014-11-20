#pragma once

#include "Billboard.h"
#include "Lib.h"

Billboard::Billboard(float x, float y, float z) : DynamicObject() {
 float colorComponents[3][4] = {
        {0,0,0, 0}, //ambient component
        {0,0,0, 0}, //dffuse component
        {0,0,0, 0} //specular component
    };
    float shininess = 0;

    /*setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);*/
	setTexture(0, "textures/tree.png");

    setPosition(x, y, z);

	_billboard =  new VSResSurfRevLib(); 
}

Billboard::~Billboard(){
}

void Billboard::draw() {
	_billboard->createBillboard();
	if(_texPath != "")
		_billboard->addTexture(_iTex, _texPath);
	/*_billboard->setMaterialBlockName("Materials");
    _billboard->setColor(VSResourceLib::DIFFUSE, _diffColor);
	_billboard->setColor(VSResourceLib::AMBIENT, _ambColor);
    _billboard->setColor(VSResourceLib::SPECULAR, _specColor);
    _billboard->setColor(VSResourceLib::SHININESS, _shininess);*/
}


void Billboard::update(float angle1, float angle2, float up0, float up1, float up2, float up20, float up21, float up22){
	
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    
    //transformations

    Lib::vsml->translate(_position[X], _position[Y], _position[Z]);
    
	//std::cout << "angle: " << angle1 << " " << up1 << "\n";
	Lib::vsml->translate(0.5,0,0);
	Lib::vsml->rotate(angle1,0,up1,0);
	//Lib::vsml->rotate((angle2),up20,up21,up22);
	Lib::vsml->scale(8, 10, 0);
	Lib::vsml->translate(-0.5,0,0);
	//Lib::vsml->translate(0, 0, 0);
	_billboard->render();
    Lib::vsml->popMatrix(VSMathLib::MODEL);
}