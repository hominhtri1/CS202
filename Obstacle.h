#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Header.h"

class Obstacle {

private:
	int mX, mY;
	int counter;
	int direction; //UPDATE

public:
	Obstacle(int x, int y, int z); //UPDATE
	Obstacle(ifstream& fin);

	int getMX();
	int getMY();

	void inc(); //counter

	bool isTime();

	void Move(bool move); //UPDATE

};

class Truck : public Obstacle {

};

class Car : public Obstacle {

};

class Dino : public Obstacle {

};

class Bird : public Obstacle {

};

#endif
