#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int lowerLight, int upperLight)
{
	mX = x;
	mY = y;

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

	if (mY + 1 != 145)
		++mY;
	else
		mY = 0;
}