#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Header.h"

class Obstacle {

private:
	int mX, mY;
	int direction;
	int moveCounter;
	int lightCounter;
	int lowerLight, upperLight;

public:
	string texture[5];

	string empty;

	Obstacle(int x, int y, int direction, int lowerLight, int upperLight);

	int getMX();
	int getMY();
	int getDirection();
	int getLower();
	int getUpper();

	void inc();

	bool isTime();

	void Move();

	virtual int type() = 0;

};

class Car : public Obstacle
{

public:
	Car(int x, int y, int direction, int lowerLight, int upperLight);

	int type();

};

class Truck : public Obstacle
{

public:
	Truck(int x, int y, int direction, int lowerLight, int upperLight);

	int type();

};

class Dinosaur : public Obstacle
{

public:
	Dinosaur(int x, int y, int direction, int lowerLight, int upperLight);

	int type();

};

class Bird : public Obstacle
{

public:
	Bird(int x, int y, int direction, int lowerLight, int upperLight);

	int type();

};

#endif