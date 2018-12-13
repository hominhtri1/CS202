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
	int* levelP;
	vector<Obstacle*> ve;
	bool* soundOnP;

public:
	Game(int* levelP, bool* soundOnP, int dummy);
	Game(int* levelP, bool* soundOnP);
	Game(int x, int y, int* levelP, bool* soundOnP);

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

	Obstacle* factory(int type, int x, int y, int direction, int lowerLight, int upperLight);

	~Game();

};

void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P, bool* soundOnP);

void soundThread(bool* SOUND_P, bool* soundOnP);

void startLevel(int* levelP, bool* soundOnP);

void startGame();

void settingsMenu(bool* soundOnP, int* levelP);

struct ObstacleS
{
	int type;
	int mX, mY;
	int direction;
	int lowerLight, upperLight;
};

#endif