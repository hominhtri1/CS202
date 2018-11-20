#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

class CVEHICLE {

private:
	int mX, mY;
	int counter;

public:
	CVEHICLE(int order, int x);

	int getMX();
	int getMY();

	void Move();

};

#endif