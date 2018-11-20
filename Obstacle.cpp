#include "Obstacle.h"

CVEHICLE::CVEHICLE(int order, int x)
{
	mY = order * 4;
	mX = x;

	counter = 0;
}

int CVEHICLE::getMX()
{
	return mX;
}

int CVEHICLE::getMY()
{
	return mY;
}

void CVEHICLE::Move()
{
	++counter;

	if (counter == 100)
	{
		if (mY + 1 != 10)
			++mY;
		else
			mY = 0;

		counter = 0;
	}
}