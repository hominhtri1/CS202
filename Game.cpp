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
		cout << "y to continue, n to end" << endl;
}

void startGame()
{
	system("cls");
	Game g;
	g.run();
}



Game::Game()
{
	for (int i = 0; i <2; i ++)
	{
		Obstacle* x = new Obstacle(i,5); //fix
		ve.push_back(x);
	}

}

// Handles most of the control flow
void Game::run()
{
	// Is set to false when human is dead, ESC is pressed, or when human is at finish line
	bool IS_RUNNING = true;

	// Is set to true when "p" is pressed
	// Separate from IS_RUNNING because different flow control is needed
	bool IS_PAUSE = false;

	// To handle the unwanted effect where if the user hold a move button toward an obstacle then the game will jump out
	// It is better when the game stop at a screen, notifying the user that they have lost
	// When the user collides with an obstacle, IS_END is set to true to avoid the _getch loop joining the background
	// thread multiple times
	bool IS_END = false;

	showConsoleCursor(false);

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
			// exitGame is only called once
			if (!IS_END)
			{
				exitGame(&bgThread, &IS_RUNNING);
				IS_END = true;
			}

			// If input = "y", reset. If input = "n", end game. Otherwise, read input again
			if (input == 89)
				startGame();
			else if (input != 78)
				continue;

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
		moveHuman(input);

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
			else if (i == ve[0]->getMX()&& j == ve[0]->getMY())
				cout << "O";
			else if (i == ve[1]->getMX() && j == ve[1]->getMY())
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
	for (int i = 0; i <ve.size(); i++)
	{
		ve[i]->Move();
	}
}

bool Game::isHumanDead()
{
	for (int i = 0; i < ve.size(); i++)
	{
		if(hu.collide(ve[i])) return true;
	}
	return false;
}

void Game::moveHuman(int input)
{
	if (input == 87)
		hu.up();
	else if (input == 83)
		hu.down();
	else if (input == 65)
		hu.left();
	else if (input == 68)
		hu.right();
}

void Game::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

Game::~Game()
{
	for (int i = 0; i < ve.size(); i++)
	{
		delete ve[i];
	}
}