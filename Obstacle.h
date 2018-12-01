#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

class Obstacle {

private:
	int mX, mY;  //rotate Oxy coordinate by 90 degrees, O is at top-left
	int counter;

public:
	Obstacle(int y, int x);

	int getMX();
	int getMY();

	void Move();

};

#endif