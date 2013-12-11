#include "Particles.h"
#include <iostream>

Particles::Particles()
{

}

void Particles::CreateParticles()	
{ 
	lifetime = (rand()%500000)/50.0;
	decay = 0.01;
	r = 0.7;
	g = 0.7;
	b = 1.0;
	xpos = 0.0;
	ypos = 0.0;
	zpos = 0.0;
	xspeed = 0.05 - (rand()%100)/1000.0;
	yspeed = 0.1 - (rand()%100)/1000.0;
	zspeed = 0.05 - (rand()%100)/1000.0;
	active = true;
}

void Particles::FountainEvolve()
{
	lifetime-=decay;
	xpos+=xspeed;
	ypos+=yspeed;
	zpos+=zspeed;
	yspeed-=0.00007;
}

void Particles::SphereEvolve()
{

}

void Particles::RainEvolve()
{
	ypos-= (rand() % 100)/100.0 * 0.3;
}

void Particles::InitRain(int width, int height)
{
	xpos = -width + (rand() % (2*width))/1.0;
	ypos = rand()%80;
	zpos = -height + (rand() % (2*height))/1.0;
}