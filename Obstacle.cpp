#include "Obstacle.h"

Obstacle::Obstacle(int order, int x)
{
	mY = order * 4;
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

	if (counter == 10)
	{
		if (mY + 1 != 10)
			++mY;
		else
			mY = 0;

		counter = 0;
	}
}