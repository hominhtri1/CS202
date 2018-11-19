#ifndef _HUMAN_H_
#define _HUMAN_H_

class Human
{

private:
	int x, y;

	bool checkFrame(int a, int b);

public:
	Human();

	int getX();
	int getY();

	void up();
	void down();
	void left();
	void right();

	bool atFinish();

};

#endif