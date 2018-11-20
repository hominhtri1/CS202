#include "Game.h"

void backgroundThread(Game* gP, bool* IS_RUNNING_P)
{
	while (*IS_RUNNING_P & !gP->isHumanDead())
	{
		gP->draw();

		gP->updateVehicle();

		gP->isHumanDead();

		Sleep(10);
	}

	if (gP->isHumanDead())
		cout << "You are dead" << endl;
}



Game::Game()
{
	ve = new CVEHICLE(0, 5);
}

void Game::run()
{
	bool IS_RUNNING = true;

	thread bgThread(backgroundThread, this, &IS_RUNNING);

	while (true)
	{
		int input = toupper(_getch());

		if (hu.isDead())
		{
			exitGame(&bgThread, &IS_RUNNING);
			break;
		}

		if (input == 27)
		{
			exitGame(&bgThread, &IS_RUNNING);
			break;
		}

		if (input == 87)
			hu.up();
		else if (input == 83)
			hu.down();
		else if (input == 65)
			hu.left();
		else if (input == 68)
			hu.right();

		if (hu.atFinish())
		{
			Sleep(100);
			exitGame(&bgThread, &IS_RUNNING);
			break;
		}
	}
}

void Game::draw()
{
	gotoXY(0, 0);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			if (i == hu.getX() && j == hu.getY())
				cout << "H";
			else if (i == ve->getMX() && j == ve->getMY())
				cout << "O";
			else
				cout << "_";

		cout << endl;
	}
}

void Game::gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Game::exitGame(thread* t, bool* IS_RUNNING_P)
{
	*IS_RUNNING_P = false;

	t->join();
}

void Game::updateVehicle()
{
	ve->Move();
}

Game::~Game()
{
	delete ve;
}

bool Game::isHumanDead()
{
	return hu.collide(ve);
}