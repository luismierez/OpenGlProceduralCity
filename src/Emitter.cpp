#include "Emitter.h"

Emitter::Emitter()
{

}

void Emitter::setMaxParticles(int p)
{
	maxParticles = p;
}

void Emitter::DrawRain(double width, double height)
{
	for (int i=0; i <=MAXPARTICLES; i++)
	{
		if(particle[i].ypos<0.0) particle[i].lifetime=0;
		if((particle[i].active == true) && (particle[i].lifetime>0.0))
		{
			glBegin(GL_LINES);
				glVertex3f(particle[i].xpos, particle[i].ypos, particle[i].zpos);
				glVertex3f(particle[i].xpos, particle[i].ypos - 2, particle[i].zpos);
			glEnd();
		} else
		{
			particle[i].CreateParticles();
			particle[i].InitRain(width*height, width*height);
		}
		particle[i].RainEvolve();
	}
}

void Emitter::setgBest(double best)
{
	globalBest = best;
}

void Emitter::PSOInit(double x, double y, double z)
{
	for (int i=0; i <= MAXPARTICLES; i++)
	{
		particle[i].xpos = x + (rand()%10)/1.0;
		particle[i].ypos = y + (rand()%10)/1.0;
		particle[i].zpos = z + (rand()%10)/1.0;

		particle[i].xspeed = 0;
		particle[i].yspeed = 0;
		particle[i].zspeed = 0;

		Vector3 distance;
		distance.set(x - particle[i].xpos,
					 y - particle[i].ypos,
					 z - particle[i].zpos);

		particle[i].pBest = distance.magnitude();

		if (particle[i].pBest < globalBest)
		{
			globalBest = particle[i].pBest;
		}
	}
}

void Emitter::PSOAlgorithm()
{
	PSOInit(0,0,0);
	Vector3 particlePosition;
	Vector3 currentDistance;
	for (int i = 0; i <= MAXPARTICLES; i++)
	{
		particlePosition.set(particle[i].xpos, particle[i].ypos, particle[i].zpos);
		float particleBest = particlePosition.magnitude();

	}
}

