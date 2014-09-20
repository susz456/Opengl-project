#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
private:
	int static const DIRECTION_FORWARD = 1;
	int static const DIRECTION_BACKWARD = 2;
	int static const KEYBOARD_UP = 101;
	int static const KEYBOARD_DOWN = 103;
	float static const MAX_SPEED = 0.5;
	float static const BRAKING_FACTOR = 0.03;
	float static const AIR_RESISTANCE = 0.0005;
	
	void accelerate();
	void deaccelerate(float factor);

public:
	Engine();
	virtual ~Engine();
	void action(int c, int x, int y);
	void move();
	float speed;
	int direction;
	float X;
	float Y;
	float Z;
	float angle;
};

#endif /* ENGINE_H_ */
