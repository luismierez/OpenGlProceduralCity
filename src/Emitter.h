#ifndef _EMITTER_H_
#define _EMITTER_H_

#include "SmartGLUT.h"
#include "Particles.h"
#include "Vector3.h"

#define MAXPARTICLES 500

class Emitter
{
public:
	int maxParticles;
	double globalBest;


	Emitter();
	Particles particle[MAXPARTICLES];
	void setMaxParticles(int p);
	void DrawRain(double width, double heigth);
	void setgBest(double best);
	void PSOInit(double x, double y, double z);
	void PSOAlgorithm();

};
#endif _EMITTER_H_