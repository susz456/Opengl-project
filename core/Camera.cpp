/*
 * Camera.cpp
 *
 *  Created on: 14 wrz 2014
 *      Author: damian
 */

#include "Camera.h"
#include <cstdio>


Camera::Camera() {
	X = 0;
	Y = 0;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::action(unsigned char c, int x, int y) {
	printf("key pressed:%c\n", c);
	switch (c) {
	case 'a':
		X ++;
		break;
	case 'd':
		X--;
		break;
	case 'w':
		Y++;
		break;
	case 's':
		Y--;
		break;
	case 'q':
		Z++;
		break;
	case 'e':
		Z--;
		break;
	}
}
