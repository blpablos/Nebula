#include "Swarm.h"

Swarm::Swarm() {
	m_pParticles = new Particle[NPARTICLES];
	lastTime = 0;

}

void Swarm::update(int elapsed) {

	int interval = elapsed - lastTime;

	for (int i = 0; i < NPARTICLES; i++) {
		m_pParticles[i].update(interval);
	}

	lastTime = elapsed;
}

Swarm::~Swarm() {
	delete[] m_pParticles;

}