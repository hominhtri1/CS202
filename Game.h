#ifndef _GAME_H_
#define _GAME_H_

#include "Header.h"
#include "Human.h"
#include "Obstacle.h"

class Game
{

private:
	Human hu;
	vector<vector<Obstacle*>> ve; //change to vector

public:
	Game();

	void run();

	void draw();

	void gotoXY(int x, int y);

	void exitGame(thread* t, bool* IS_RUNNING_P);

	void updateVehicle();

	bool isHumanDead();

	void moveHuman(int input);

	void showConsoleCursor(bool showFlag);

	~Game();

};

void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P);

void startGame();

#endif