#include "Human.h"

Human::Human()
{
	x = 9;
	y = 0;
}

int Human::getX()
{
	return x;
}

int Human::getY()
{
	return y;
}

void Human::up()
{
	if (checkFrame(x - 1, y))
		--x;
}

void Human::down()
{
	if (checkFrame(x + 1, y))
		++x;
}

void Human::left()
{
	if (checkFrame(x, y - 1))
		--y;
}

void Human::right()
{
	if (checkFrame(x, y + 1))
		++y;
}

bool Human::checkFrame(int a, int b)
{
	return ((0 <= a && a < 10) && (0 <= b && b < 10));
}

bool Human::atFinish()
{
	return (x == 0);
}