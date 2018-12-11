#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Header.h"

class Obstacle {

private:
	int mX, mY;
	int counter;

public:
	Obstacle(int x, int y);
	Obstacle(ifstream& fin);

	int getMX();
	int getMY();

	void inc();

	bool isTime();

	void Move(bool move);

};

#endif
