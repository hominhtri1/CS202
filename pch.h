
#ifndef PCH_H
#define PCH_H
#include <iostream>
#include <vector>
using namespace std;
class CVEHICLE {
	int mX, mY;
public:
	CVEHICLE();
	virtual void Move(int, int);
};

class CTRUCK : public CVEHICLE
{
// 5 trucks per line
public:
	void Move(int a);
};

class CCAR : public CVEHICLE
{
public:
	void Move(int a);
};

class CANIMAL {
	int mX, mY;
public:
	CANIMAL();
	virtual void Move(int, int);
	virtual void Fly(int, int); //Haven't declare
	virtual void Tell(); //Sound of animal
};

class CDINAUSOR : public CANIMAL {
public:
	void Move(int a);
	void Tell(); //Haven't declare
};

class CBIRD : public CANIMAL {
public:
	void Move(int a, int b);
	void Tell();
};

#endif
