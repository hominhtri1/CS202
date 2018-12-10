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
public:
	Truck(int x, int y, int z) : Obstacle(x, y, z)
	{
	};
};

class Car : public Obstacle {
public:
	Car(int x, int y, int z) : Obstacle(x, y, z)
	{
	};
};

class Dino : public Obstacle {
public:
	Dino(int x, int y, int z) : Obstacle(x, y, z)
{
};
};

class Bird : public Obstacle {
public:
	Bird(int x, int y, int z) : Obstacle(x, y, z)
{
};
};

class Factory
{
public:	vector<Obstacle*> portion(int x, int type); //create line of obstacle
};
#endif
