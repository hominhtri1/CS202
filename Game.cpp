#include "Game.h"

void backgroundThread(Game* gP, bool* IS_RUNNING_P)
{
	while (*IS_RUNNING_P)
	{
		gP->draw();

		Sleep(100);
	}
}



void Game::run()
{
	bool IS_RUNNING = true;

	thread bgThread(backgroundThread, this, &IS_RUNNING);

	while (true)
	{
		int input = toupper(_getch());

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