// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"
void CVEHICLE::Move(int a, int b)
{
	if (mX + a > 20) mX = 0;
	else mX += a;
	if (mY + b);
}


void CCAR::Move(int a)
{
	CVEHICLE::Move(a, 0);
}

void CTRUCK::Move(int a)
{
	CVEHICLE::Move(a, 0);
}

void CANIMAL::Move(int a, int b)
{
	if (mX + a > 20) mX = 0;
	else mX += a;
	mY += b;
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