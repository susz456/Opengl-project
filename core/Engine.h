#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
private:
	enum KEY_STATE {NOTPUSHED, PUSHED} keys[16];
	int static const DIRECTION_FORWARD = 1;
	int static const DIRECTION_BACKWARD = 2;
	int static const KEYBOARD_UP = 1;
	int static const KEYBOARD_DOWN = 3;
	int static const KEYBOARD_LEFT = 0;
	int static const KEYBOARD_RIGHT = 2;
	int static const KEYBOARD_SHIFT = 13;
	int static const KEYBOARD_CTRL = 15;
	
	float static const MAX_SPEED = 0.15;
	float static const BRAKING_FACTOR = 0.01;
	float static const ACCELERATE_FACTOR = 0.003;
	float static const AIR_RESISTANCE = 0.001;
	float static const HAND_BRAKE_FACTOR = 0.3;
	
	void accelerate(float factor);
	void deaccelerate(float factor);
	

public:
	Engine();
	virtual ~Engine();
	void actionDown(int c, int x, int y);
	void actionUp(int c, int x, int y);
	void move();
	void update();
  float getAngle();
	float speed;
	int direction;
	float X;
	float Y;
	float Z;
	float angle;
};

#endif /* ENGINE_H_ */
