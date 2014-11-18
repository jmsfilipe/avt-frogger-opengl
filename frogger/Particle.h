#pragma once

#include "DynamicObject.h"

class Particle : public DynamicObject {
public:
    VSResSurfRevLib *_particle;
    float	life;		// vida
	float	fade;		// fade
	float	r, g, b;    // color
	float x, y, z;    // posicao
	float vx, vy, vz; // velocidade 
    float ax, ay, az; // aceleraçcao
public:
	Particle();
	Particle(bool p);
	Particle(float x, float y, float z);
	~Particle();
	virtual void draw();
	virtual void update();
	VSResSurfRevLib *getParticle();
};