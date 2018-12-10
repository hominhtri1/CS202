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
vector<Obstacle*> Factory::portion(int x,int type)
{
	vector<Obstacle*> v;
	if (type == 1)
	{
		
		int po = rand() % 5; //random position
		int di = rand() % 2; //random direction, get 0,1 value
		if (di == 0) di = -1;
		int amount = rand() % 3; //return random amount of obstacle
		while (amount != 0)
		{
			Obstacle* t = new Car(x, po, di);
			v.push_back(t);
			po += 5;
			amount--;
		}
		
	}
	if (type == 2)
	{
		
		int po = rand() % 5;
		int di = rand() % 2; //random direction, get 0,1 value
		if (di == 0) di = -1;
		int amount = rand() % 3; //return random amount of obstacle
		while (amount != 0)
		{
			Obstacle* t = new Truck(x, po, di);
			v.push_back(t);
			po += 5;
			amount--;
		}

		
	}
	if (type == 3)
	{
	
		int po = rand() % 5;
		int di = rand() % 2; //random direction, get 0,1 value
		if (di == 0) di = -1;
		int amount = rand() % 3; //return random amount of obstacle
		while (amount != 0)
		{
			Obstacle* t = new Dino(x, po, di);
			v.push_back(t);
			po += 5;
			amount--;
		}

		
	}
	if (type == 1)
	{
		
		int po = rand() % 5;
		int di = rand() % 2; //random direction, get 0,1 value
		if (di == 0) di = -1;
		int amount = rand() % 3; //return random amount of obstacle
		while (amount != 0)
		{
			Obstacle* t = new Bird(x, po, di);
			v.push_back(t);
			po += 5;
			amount--;
		}

		
	}
	return v;
}
