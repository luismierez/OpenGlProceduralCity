#ifndef _PARTICLES_H_
#define _PARTICLES_H_
//#include "SmartGLUT.h"
#include <stdlib.h>
#include <stdio.h>

class Particles
{
public:

	float lifetime;					// total lifetime of the particle
	float decay;					// decay speed of the particle
	float r,g,b;					// color values of the particle
	float xpos, ypos, zpos;			// position of the particle
	float xspeed, yspeed, zspeed;	// speed of the particle
	float pBest;
	bool active;					// is particle active or not?

	Particles();
	void CreateParticles();
	void FountainEvolve();
	void SphereEvolve();
	void RainEvolve();
	void InitRain(int width, int height);
};

#endif