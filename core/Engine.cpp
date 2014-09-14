/*
 * Engine.cpp
 *
 *  Created on: 14 wrz 2014
 *      Author: damian
 */

#include "Engine.h"
#include <cstdio>

Engine::Engine() {
	X = 0;
	Y = 0;
	Z = 0;
	angle = 0;
	bool keyboard[256];
}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

void Engine::action(int c, int x, int y) {
	printf ("engine action, c:%d\n",c);
	keyboard[c] = true;
	switch (c) {
	case 100:
		angle -= 0.1;
		break;
	case 102:
		angle += 0.1;
		break;
	case 101:
		Z += 0.1;
		break;
	case 103:
		Z -= 0.1;
		break;
	}
}
