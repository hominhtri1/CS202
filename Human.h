#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Obstacle.h"

class Human
{

private:
	int x, y;
	bool dead;

	bool checkFrame(int a, int b);

public:
	Human();

	int getX();
	int getY();

	void up();
	void down();
	void left();
	void right();

	bool atFinish();

	bool collide(CVEHICLE* ve);

	bool isDead();

};

#endif