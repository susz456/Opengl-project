/*
 * Engine.h
 *
 *  Created on: 14 wrz 2014
 *      Author: damian
 */

#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
public:
	Engine();
	virtual ~Engine();
	void action(int c, int x, int y);
	float X;
	float Y;
	float Z;
	float angle;
};

#endif /* ENGINE_H_ */
