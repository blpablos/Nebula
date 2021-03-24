#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"


class Swarm
{
public:
	const static int NPARTICLES = 5000;
private:
	Particle* m_pParticles;
	int lastTime;
public:
	Swarm();
	virtual ~Swarm();

	Particle* const getParticles() { return m_pParticles; };
	void update(int elapsed);

};

#endif