#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

using namespace std;

void RGB(int ticks, unsigned char& R, unsigned char& G, unsigned char& B);

int main(int argc, char* argv[])
{
	srand(time(NULL));

	Screen screen;

	if (screen.init() == false) {
		cout << "Error initializing SDL." << endl;
	}
	
	Swarm swarm;
	bool quit = false;
	unsigned char red, green, blue;

	while (!quit) {
		// Update particles

		int elapsed = SDL_GetTicks();
		swarm.update(elapsed);

		// Draw particles
		//RGB(elapsed, red, green, blue);
		green = (unsigned char) ((1 + cos(elapsed * 0.0001)) * 128);
		red = (unsigned char) ((1 + sin(elapsed * 0.0002)) * 128);
		blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);

		const Particle* const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		// Draw screen
		screen.update();


		// Check events going on in the screen

		if (screen.processEvents() == false) {
			break;
		}
		
	}


	return 0;
}


void RGB(int ticks, unsigned char& R, unsigned char& G, unsigned char& B) {

	double dR, dG, dB;
	double value = (double)(ticks % 20000) / 20000;

	if (0 <= value && value <= 1.0 / 8.0) {
		dR = 0;
		dG = 0;
		dB = 4 * value + .5; // .5 - 1 // b = 1/2
	}
	else if (1.0 / 8.0 < value && value <= 3.0 / 8.0) {
		dR = 0;
		dG = 4 * value - .5; // 0 - 1 // b = - 1/2
		dB = 1; // small fix
	}
	else if (3.0 / 8.0 < value && value <= 5.0 / 8.0) {
		dR = 4 * value - 1.5; // 0 - 1 // b = - 3/2
		dG = 1;
		dB = -4 * value + 2.5; // 1 - 0 // b = 5/2
	}
	else if (5.0 / 8.0 < value && value <= 7.0 / 8.0) {
		dR = 1;
		dG = -4 * value + 3.5; // 1 - 0 // b = 7/2
		dB = 0;
	}
	else if (7.0 / 8.0 < value && value <= 1.0) {
		dR = -4 * value + 4.5; // 1 - .5 // b = 9/2
		dG = 0;
		dB = 0;
	}
	else {    // should never happen - value > 1
		dR = .5;
		dG = 0;
		dB = 0;
	}

	// scale for hex conversion

	R = (unsigned char)(128 * dR);
	G = (unsigned char)(128 * dG);
	B = (unsigned char)(128 * dB);


	return;

}
