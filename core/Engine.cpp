#include "Engine.h"


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
			if (speed == 0) break;
			if (direction == DIRECTION_FORWARD){
				angle -= ANGLE_CHANGE;
			} else {
				angle += ANGLE_CHANGE;
			}
			deaccelerate(TURNING_FACTOR);
			break;
		case KEYBOARD_RIGHT:
			if (speed == 0) break;
			if (direction == DIRECTION_FORWARD){
				angle += ANGLE_CHANGE;
			} else {
				angle -= ANGLE_CHANGE;
			}
			deaccelerate(TURNING_FACTOR);
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
		case KEYBOARD_CTRL:
			Z = 0;
			X = 0;
			speed = 0;
			angle = 0;
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
	//printf ("speed:%f\n",speed);
	//printf ("angle:%f\n",angle);
	
	cosinus = cos (angle * PI / 180.0);
	sinus = sin (angle * PI / 180.0);
	
	if (carIsOutOfTrack()) {
		//printf ("out of track\n");
		deaccelerate(OUT_OF_TRACK_FACTOR);
		//speed = 0;
		//return;
	}
	
	if (direction == DIRECTION_FORWARD) {
		Z += speed * cosinus;
		X += speed * sinus;
	} else {
		Z -= speed * cosinus;
		X -= speed * sinus;
	}
}

bool Engine::carIsOutOfTrack() {
	left = X + (CAR_WIDTH / 2);
	right = X - (CAR_WIDTH / 2);
	top = Z + (CAR_LENGTH / 2);
	bottom = Z - (CAR_LENGTH / 2);
	
	topLeft = calculateRotatedDimen(top, left);
	topRight = calculateRotatedDimen(top, right);
	bottomLeft = calculateRotatedDimen(bottom, left);
	bottomRight = calculateRotatedDimen(bottom, right);
	
	//printf ("left:%f, right:%f, top:%f, bot:%f\n",left,right,top,bottom);
	//printf ("topleft.x:%f topleft.z:%f\n",topLeft.X, topLeft.Z);
	if (pointIsOutOfTrack(topLeft.X, topLeft.Z)) return true;
	if (pointIsOutOfTrack(topRight.X, topRight.Z)) return true;
	if (pointIsOutOfTrack(bottomLeft.X, bottomLeft.Z)) return true;
	if (pointIsOutOfTrack(bottomRight.X, bottomRight.Z)) return true;
	return false;
}

Point Engine::calculateRotatedDimen(float x, float z) {
	Point p;
	//printf("X:%f  Z:%f\n",X,Z);
	//printf("angle:%f sinus:%f, cosinus:%f\n",angle,sinus,cosinus);
	p.X = ((x - Z)*cosinus) - ((z - X)*sinus) + Z;
	p.Z = ((x - Z)*sinus) + ((z - X)*cosinus) + X;
	return p;
}

bool Engine::pointIsOutOfTrack(float z, float x) {
	if (x >= TRACK_LEFT_BORDER) return true;
	if (x <= TRACK_RIGHT_BORDER) return true;
	if (z >= TRACK_END_BORDER) return true;
	if (z <= TRACK_START_BORDER) return true;
	return false;
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
	speed = speed - ((MAX_SPEED - speed)/10 * factor) - 5*(speed * factor);
}
