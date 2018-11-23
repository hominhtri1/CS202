#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

class Obstacle {

private:
	int mX, mY;
	int counter;

public:
	Obstacle(int order, int x);

	int getMX();
	int getMY();

	void Move();

};

#endif