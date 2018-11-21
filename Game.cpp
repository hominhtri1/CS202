#include "Game.h"

// Handles most background tasks
void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P)
{
	// While no reason to stop, and while human is still alive
	while (*IS_RUNNING_P & !gP->isHumanDead())
	{
		// If pause is true, loops until pause is false
		while (*IS_PAUSE_P);

		// Draw the map
		gP->draw();

		// Update obstacle positions
		gP->updateVehicle();

		// Need to constantly check for collision so collision checking is handled by
		// background thread
		gP->isHumanDead();

		Sleep(10);
	}

	// When there is collision, above loop will exit and the below line is printed
	// Depending on input, new game is started or program exits
	if (gP->isHumanDead())
		cout << "y to continue" << endl;
}



Game::Game()
{
	ve = new CVEHICLE(0, 5);
}

// Handles most of the control flow
void Game::run()
{
	// Is set to false when human is dead, ESC is pressed, or when human is at finish line
	bool IS_RUNNING = true;

	// Is set to true when "p" is pressed
	// Separate from IS_RUNNING because different flow control is needed
	bool IS_PAUSE = false;

	// Background thread handling pausing, drawing, updating obstacle positions,
	// and checking for collisions
	thread bgThread(backgroundThread, this, &IS_RUNNING, &IS_PAUSE);

	// Input loop, stop when human is dead, ESC is pressed, or when human is at finish line
	while (true)
	{
		int input = toupper(_getch());

		// If already paused, unpause when input = "p"
		if (IS_PAUSE)
		{
			if (input == 80)
				IS_PAUSE = false;

			continue;
		}

		// If dead, end game. Except when input = "y", then game is reset
		if (hu.isDead())
		{
			exitGame(&bgThread, &IS_RUNNING);

			if (input == 89)
			{
				system("cls");
				Game g;
				g.run();
			}

			break;
		}

		// Input = "p"
		if (input == 80)
			IS_PAUSE = true;

		// Input = ESC
		if (input == 27)
		{
			exitGame(&bgThread, &IS_RUNNING);
			break;
		}

		// Up, down, left, right
		if (input == 87)
			hu.up();
		else if (input == 83)
			hu.down();
		else if (input == 65)
			hu.left();
		else if (input == 68)
			hu.right();

		// Human at finish line
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
				cout << "Y";
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

// Signals the background thread to stop
void Game::exitGame(thread* t, bool* IS_RUNNING_P)
{
	// Set bool to false, the loop in the background thread will exit
	*IS_RUNNING_P = false;

	// After the background thread is finished, merge it back into the main thread
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