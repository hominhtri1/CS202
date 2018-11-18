#ifndef _GAME_H_
#define _GAME_H_

#include "Header.h"
#include "Human.h"

class Game
{

private:
	Human hu;

public:
	void run();

	void draw();

	void gotoXY(int x, int y);

	void exitGame(thread* t, bool* IS_RUNNING_P);

};

void backgroundThread(Game* gP, bool* IS_RUNNING_P);

#endif