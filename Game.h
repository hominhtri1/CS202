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
	Game();
	Game(int level);
	Game(int x, int y);

	void run();

	void updateHuman();

	void drawFull();

	void exitGame(thread* t, bool* IS_RUNNING_P);

	bool isHumanDead();

	void moveHuman(int input);

	string saveGame();

	void loadGame();

	void loadGameFile(string path);

	void updateObstacle(bool fog);

	void drawBomb();

	~Game();

};

void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P);

void startLevel(int level);

void startGame();

struct ObstacleS
{
	int mX, mY;
	int lowerLight, upperLight;
};

#endif