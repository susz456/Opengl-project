#include "Engine.h"
#include <cstdio>

Engine::Engine() {
	X = 0;
	Y = 0;
	Z = 0;
	angle = 0;
	speed = 0;
	direction = DIRECTION_FORWARD;
	bool keyboard[256];
}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

void Engine::action(const int c, int x, int y) {
	//printf ("engine action, c:%d\n",c);
	
	switch (c) {
	case 100:
		angle -= 0.1;
		break;
	case 102:
		angle += 0.1;
		break;
	case KEYBOARD_UP:
		if (speed <= 0) {
			direction = DIRECTION_FORWARD;
			accelerate();
		} else if (direction == DIRECTION_FORWARD){
			accelerate();
		} else if (direction == DIRECTION_BACKWARD) {
			deaccelerate(BRAKING_FACTOR);
		}
		break;
	case KEYBOARD_DOWN:
		if (speed <= 0) {
			direction = DIRECTION_BACKWARD;
			accelerate();
		} else if (direction == DIRECTION_BACKWARD){
			accelerate();
		} else if (direction == DIRECTION_FORWARD) {
			deaccelerate(BRAKING_FACTOR);
		}
		break;
	}
	
}

void Engine::move() {
	printf ("speed:%f\n",speed);
	if (speed > 0) {
		deaccelerate(AIR_RESISTANCE);
	} else {
		speed = 0;
	}
	if (direction == DIRECTION_FORWARD) {
		Z += speed;
	} else {
		Z -= speed;
	}
}

void Engine::accelerate() {
	if (speed >= MAX_SPEED) {
		speed == MAX_SPEED;
		return;
	}
	speed = speed + ((MAX_SPEED - speed) * 0.01);
}

void Engine::deaccelerate(float factor) {
	if (speed <= 0) {
		speed = 0;
		return;
	}
	speed = speed + ((speed - MAX_SPEED) * factor);
}
