// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

CVEHICLE::CVEHICLE()
{
	mX = 0;
	mY = 0;
}
void CVEHICLE::Move(int, int)
{
	int a = 1;
	while (a % 100 != 0) a++;
	
		if (mX + 1 > 20) mX = 0;
		else mX += 1;
		mY = 0;
	
}


void CCAR::Move(int a)
{
	while (a > 0)
	{
		CVEHICLE::Move(0, 0);
		a--;
	}
}

void CTRUCK::Move(int a)
{
	while (a > 0)
	{
		CVEHICLE::Move(0, 0);
		a--;
	}
}

CANIMAL::CANIMAL()
{
	mX = 0;
	mY = 0;
}

void CANIMAL::Move(int, int)
{
	int a = 1;
	while (a % 100 != 0) a++;

	if (mX + 1 > 20) mX = 0;
	else mX += 1;
}


void CDINAUSOR::Move(int a)
{
	CANIMAL::Move(a, 0);
}

void CBIRD::Move(int a, int b)
{
	if (b == 0)
	{
		CANIMAL::Move(a, 2);
		b == 1;
	}
	if (b == 1)
	{
		CANIMAL::Move(a, 0);
		b == 0;
	}
}
