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
	--x;
}

void Human::down()
{
	++x;
}

void Human::left()
{
	--y;
}

void Human::right()
{
	++y;
}