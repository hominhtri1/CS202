#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int z)
{
	mX = x;
	mY = y;
	direction = 1;
	if (z==1||z==-1)
	direction = z;
	counter = 0;
}

Obstacle::Obstacle(ifstream& fin)
{
	fin >> mX >> mY;
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

void Obstacle::inc()
{
	if (counter < 15)
		++counter;
	else
		counter = 0;
}

bool Obstacle::isTime()
{
	return (counter == 0);
}

void Obstacle::Move(bool move)
{
	if (!move)
		return;
	if (direction == 1)
	{
		if (mY + 1 != 10)
			++mY;
		else
			mY = 0;
	}
	else
	{
		if (mY!= 0)
			--mY;
		else
			mY = 9;
	}
}
