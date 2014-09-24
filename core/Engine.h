#ifndef ENGINE_H_
#define ENGINE_H_
#define PI 3.14159265
#include <cstdio>
#include <cmath>

	struct Point{
		float X;
		float Z;
	};
class Engine {
private:

	enum KEY_STATE {NOTPUSHED, PUSHED} keys[16];
	int static const DIRECTION_FORWARD = 1;
	int static const DIRECTION_BACKWARD = 2;
	int static const KEYBOARD_UP = 1;
	int static const KEYBOARD_DOWN = 3;
	int static const KEYBOARD_LEFT = 2;
	int static const KEYBOARD_RIGHT = 0;
	int static const KEYBOARD_SHIFT = 13;
	int static const KEYBOARD_CTRL = 15;
	
	float static const MAX_SPEED = 0.15;
	float static const BRAKING_FACTOR = 0.01;
	float static const ACCELERATE_FACTOR = 0.0015;
	float static const AIR_RESISTANCE = 0.001;
	float static const HAND_BRAKE_FACTOR = 0.3;
	float static const TURNING_FACTOR = 0.002;
	float static const ANGLE_CHANGE = 0.7;
	float static const OUT_OF_TRACK_FACTOR = 0.01;
	
	float static const CAR_WIDTH = 0.170;
	float static const CAR_LENGTH = 0.370;
	float static const TRACK_LEFT_BORDER = 0.340;
	float static const TRACK_RIGHT_BORDER = -0.340;
	float static const TRACK_END_BORDER = 22;
	float static const TRACK_START_BORDER = -22;
	
	void accelerate(float factor);
	void deaccelerate(float factor);
	bool carIsOutOfTrack();
	bool pointIsOutOfTrack(float X, float Y);
	Point calculateRotatedDimen(float X, float Y);
	
	float left;
	float right;
	float top;
	float bottom;
	
	Point topLeft;
	Point topRight;
	Point bottomLeft;
	Point bottomRight;
	
	double cosinus;
	double sinus;



public:
	Engine();
	virtual ~Engine();
	void actionDown(int c, int x, int y);
	void actionUp(int c, int x, int y);
	void move();
	void update();
	float speed;
	int direction;
	float X;
	float Y;
	float Z;
	float angle;
};

#endif /* ENGINE_H_ */
