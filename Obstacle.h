#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Header.h"

class Obstacle {

private:
	int mX, mY;
	int moveCounter;
	int lightCounter;
	int lowerLight, upperLight;

public:
	Obstacle(int x, int y, int lowerLight, int upperLight);

	int getMX();
	int getMY();
	int getLower();
	int getUpper();

	void inc();

	bool isTime();

	void Move();

};

#endif