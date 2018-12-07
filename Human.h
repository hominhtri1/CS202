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
	Human(int x, int y);

	int getX();
	int getY();

	void up();
	void down();
	void left();
	void right();

	bool atFinish();

	bool collide(Obstacle* ve);

	bool isDead();

};

#endif