#ifndef _GAME_H_
#define _GAME_H_

#include "Header.h"
#include "Human.h"
#include "Obstacle.h"

class Game
{

private:
	Human hu;
	int oldX, oldY;
	int level;
	vector<Obstacle*> ve;

public:
	Game(int level);
	Game(int x, int y);

	void run();

	void eraseHuman();

	void eraseObstacle();

	void drawUpdateHuman();

	void drawUpdateObstacle(bool fog);

	void drawFull();

	void gotoXY(int x, int y);

	void exitGame(thread* t, bool* IS_RUNNING_P);

	void moveObstacle(bool move);

	bool isHumanDead();

	void moveHuman(int input);

	void showConsoleCursor(bool showFlag);

	void saveGame();

	void loadGame();

	void updateObstacle(bool move, bool fog);

	~Game();

};

void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P);

void startLevel(int level);

void startGame();

#endif