/*
 * Camera.cpp
 *
 *  Created on: 14 wrz 2014
 *      Author: damian
 */

#include "Camera.h"

Camera::Camera() {
	X = 0;
	Y = 0;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::action(unsigned char c, int x, int y) {
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
	}
}
