/*
 * Camera.h
 *
 *  Created on: 14 wrz 2014
 *      Author: damian
 */

#ifndef CAMERA_H_
#define CAMERA_H_

class Camera {
public:
	Camera();
	virtual ~Camera();
	void action(unsigned char c, int x, int y);
	float X;
	float Y;
	float Z;
};

#endif /* CAMERA_H_ */
