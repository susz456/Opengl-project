#include "Engine.h"
#include <cstdio>

Engine::Engine() {
	X = 0;
	Y = 0;
	Z = 0;
	angle = 0;
	speed = 0;
	direction = DIRECTION_FORWARD;
	for (int i=0 ; i<16 ; i++) keys[i] = NOTPUSHED;
}

Engine::~Engine() {
}

void Engine::actionUp(const int c, int x, int y) {
	//printf ("engine key up, c:%d\n",c);
	int key = c - 100;
	keys[key] = NOTPUSHED;
}

void Engine::actionDown(const int c, int x, int y) {
	//printf ("engine key down, c:%d\n",c);
	if (c < 100) return;
	int pressedKey = c - 100;
	keys[pressedKey] = PUSHED;
	if (speed == 0) {
		keys[KEYBOARD_LEFT] = NOTPUSHED;
		keys[KEYBOARD_RIGHT] = NOTPUSHED;
	}
	
	switch (pressedKey) {
	case KEYBOARD_UP:
		keys[KEYBOARD_DOWN] = NOTPUSHED;
		break;
	case KEYBOARD_DOWN:
		keys[KEYBOARD_UP] = NOTPUSHED;
		break;
	case KEYBOARD_SHIFT:
		keys[KEYBOARD_UP] = NOTPUSHED;
		keys[KEYBOARD_DOWN] = NOTPUSHED;
		break;
	case KEYBOARD_LEFT:
		keys[KEYBOARD_RIGHT] = NOTPUSHED;
		break;
	case KEYBOARD_RIGHT:
		keys[KEYBOARD_LEFT] = NOTPUSHED;
		break;
	}
}

void Engine::update() {
	for (int i=0 ; i<16 ; i++){
		if (keys[i] == NOTPUSHED) continue;

		switch (i) {
		case KEYBOARD_LEFT:
			angle -= 1.0;
			break;
		case KEYBOARD_RIGHT:
			angle += 1.0;
			break;
		case KEYBOARD_SHIFT:
			deaccelerate(HAND_BRAKE_FACTOR);
			break;
		case KEYBOARD_UP:
			if (speed <= 0) {
				direction = DIRECTION_FORWARD;
				accelerate(ACCELERATE_FACTOR);
			} else if (direction == DIRECTION_FORWARD){
				accelerate(ACCELERATE_FACTOR);
			} else if (direction == DIRECTION_BACKWARD) {
				deaccelerate(BRAKING_FACTOR);
			}
			break;
		case KEYBOARD_DOWN:
			if (speed <= 0) {
				direction = DIRECTION_BACKWARD;
				accelerate(ACCELERATE_FACTOR);
			} else if (direction == DIRECTION_BACKWARD){
				accelerate(ACCELERATE_FACTOR);
			} else if (direction == DIRECTION_FORWARD) {
				deaccelerate(BRAKING_FACTOR);
			}
			break;
		}
	}
	if (speed > 0) {
		deaccelerate(AIR_RESISTANCE);
	} else {
		speed = 0;
	}
}

void Engine::move() {
	update();
	printf ("speed:%f\n",speed);
	if (direction == DIRECTION_FORWARD) {
		Z += speed;
	} else {
		Z -= speed;
	}
}

void Engine::accelerate(float factor) {
	if (speed >= MAX_SPEED) {
		speed == MAX_SPEED;
		return;
	}
	speed = speed + ((MAX_SPEED - speed) * factor);
}

void Engine::deaccelerate(float factor) {
	if (speed <= 0) {
		speed = 0;
		return;
	}
<<<<<<< HEAD
	speed = speed - ((MAX_SPEED - speed)/10 * factor) - 5*(speed * factor);
=======
	speed = speed - ((MAX_SPEED - speed)/10 * factor) - (speed * factor);
>>>>>>> 81998adc462a35c543589d7907c849313be7ca42
}

float Engine::getAngle() {
  return angle;
}
