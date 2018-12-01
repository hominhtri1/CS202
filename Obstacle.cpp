#include "Obstacle.h"

Obstacle::Obstacle(int y, int x)
{
	int distance; //distance between obstacle
	distance = 5;
	mY = y *distance;
	mX = x;

	counter = 0;
}

int Obstacle::getMX()
{
	return mX;
}

int Obstacle::getMY()
{
	return mY;
}

void Obstacle::Move()
{
	++counter;

	if (counter == 1+8*mX)
	{
		if (mY + 1 != 10)
			++mY;
		else
			mY = 0;

		counter = 0;
	}
}