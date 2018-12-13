#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int direction, int lowerLight, int upperLight)
{
	mX = x;
	mY = y;

	this->direction = (direction == 1) ? 1 : -1;

	moveCounter = 0;
	lightCounter = 0;

	this->lowerLight = lowerLight;
	this->upperLight = upperLight;
}

int Obstacle::getMX()
{
	return mX;
}

int Obstacle::getMY()
{
	return mY;
}

int Obstacle::getLower()
{
	return lowerLight;
}

int Obstacle::getUpper()
{
	return upperLight;
}

int Obstacle::getDirection()
{
	return direction;
}

void Obstacle::inc()
{
	if (moveCounter < 5)
		++moveCounter;
	else
		moveCounter = 0;
}

bool Obstacle::isTime()
{
	return (moveCounter == 0);
}

void Obstacle::Move()
{
	++lightCounter;

	if (lightCounter == 1)
	{
		gotoXY(159, mX);
		cout << "G";
	}
	else if (lightCounter == lowerLight)
	{
		gotoXY(159, mX);
		cout << "R";
	}

	if (lightCounter == upperLight)
		lightCounter = 0;
	else if (lightCounter > lowerLight)
		return;

	mY += direction;

	if (mY == 135)
		mY = 0;
	else if (mY == -1)
		mY = 134;
}



Car::Car(int x, int y, int direction, int lowerLight, int upperLight)
	: Obstacle(x, y, direction, lowerLight, upperLight)
{
	string tmp[5] = { "             ",
					  "  ______     ",
					  " /|_||_\\`.__ ",
					  "(   _    _ _\\",
					  "=`-(_)--(_)-'" };
	for (int i = 0; i < 5; ++i)
		texture[i] = tmp[i];

	empty = "             ";
}

int Car::type()
{
	return 0;
}



Truck::Truck(int x, int y, int direction, int lowerLight, int upperLight)
	: Obstacle(x, y, direction, lowerLight, upperLight)
{
	string tmp[5] = { "                  ",
					  "      ____        ",
					  " ____//_]|________",
					  "(o _ |  -|   _  o|",
					  " `(_)-------(_)--'" };

	for (int i = 0; i < 5; ++i)
		texture[i] = tmp[i];

	empty = "                  ";
}

int Truck::type()
{
	return 1;
}



Dinosaur::Dinosaur(int x, int y, int direction, int lowerLight, int upperLight)
	: Obstacle(x, y, direction, lowerLight, upperLight)
{
	string tmp[5] = { "              / _)",
					  "     _.----._/ /  ",
					  "    /         /   ",
					  " __/ (  | (  |    ",
					  "/__.-'|_|--|_|    " };

	for (int i = 0; i < 5; ++i)
		texture[i] = tmp[i];

	empty = "                  ";
}

int Dinosaur::type()
{
	return 2;
}



Bird::Bird(int x, int y, int direction, int lowerLight, int upperLight)
	: Obstacle(x, y, direction, lowerLight, upperLight)
{
	string tmp[5] = { "       ",
					  "<6)_ ,/",
					  " (_==/ ",
					  "  ='-  ",
					  "       " };

	for (int i = 0; i < 5; ++i)
		texture[i] = tmp[i];

	empty = "       ";
}

int Bird::type()
{
	return 3;
}