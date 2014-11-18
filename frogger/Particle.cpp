#pragma once

#include "Particle.h"
#include "Lib.h"

Particle::Particle(){}

Particle::Particle(bool t) : DynamicObject(){
	_particle =  new VSResSurfRevLib(); 
	setTexture(0, "textures/particle.png");
		if(_texPath != "")
		 _texID = _particle->addTexture(_iTex, _texPath);
}

Particle::Particle(float xx, float yy, float zz) : DynamicObject() {
/* float colorComponents[3][4] = {
        {0,0,0, 0}, //ambient component
        {0,0,0, 0}, //dffuse component
        {0,0,0, 0} //specular component
    };
    float shininess = 0;

    setBaseColor(AMBIENT_COMP, colorComponents[AMBIENT_COMP]);
    setBaseColor(DIFFUSE_COMP, colorComponents[DIFFUSE_COMP]);
    setBaseColor(SPECULAR_COMP, colorComponents[SPECULAR_COMP]);
    setShininess(shininess);*/
	//setTexture(0, "textures/particula.bmp");
	x = xx; y = yy; z = zz;
    setPosition(x, y, z);

	_particle =  new VSResSurfRevLib(); 
}

Particle::~Particle(){
}

VSResSurfRevLib *Particle::getParticle(){
	return _particle;}

void Particle::draw() {
	_particle->createBillboard();
	float color[4] = {r,g,b,life};
	float white[4] = {0,0,0,1};
	_particle->setMaterialBlockName("Materials");
    _particle->setColor(VSResourceLib::DIFFUSE, color);
	_particle->setColor(VSResourceLib::AMBIENT, color);
    _particle->setColor(VSResourceLib::SPECULAR, white);
    _particle->setColor(VSResourceLib::SHININESS, white);
	//_particle->setTexture(_iTex, _texID);
}


void Particle::update(){
	
    Lib::vsml->pushMatrix(VSMathLib::MODEL);
    
    //transformations
	//std::cout << "x: " << x  << "y: " << y  << "z: " << z << "\n";
    Lib::vsml->translate(x, y, z);
	//Lib::vsml->translate(0, 0, 0);
	_particle->render();
    Lib::vsml->popMatrix(VSMathLib::MODEL);
}