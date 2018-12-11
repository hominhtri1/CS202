#include "Game.h"

// Handles most background tasks
void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P)
{
	gP->drawFull();

	int lightCounter = 0;
	int fogCounter = 0;

	bool move = true;
	bool fog = true;

	// While no reason to stop, and while human is still alive
	while (*IS_RUNNING_P & !gP->isHumanDead())
	{
		// If pause is true, loops until pause is false
		while (*IS_PAUSE_P);

		if (lightCounter < 450)
			++lightCounter;
		else
			lightCounter = 0;

		if (lightCounter < 350)
			move = true;
		else
			move = false;

		if (fogCounter < 350)
			++fogCounter;
		else
			fogCounter = 0;

		if (fogCounter < 275)
			fog = true;
		else
			fog = false;

		gP->updateObstacle(move, fog);

		gP->eraseHuman();
		gP->drawUpdateHuman();

		// Need to constantly check for collision so collision checking is handled by
		// background thread
		gP->isHumanDead();

		Sleep(10);
	}

	// When there is collision, above loop will exit and the below line is printed
	// Depending on input, new game is started or program exits
	if (gP->isHumanDead())
	{
		gP->drawFull();
		cout << "y to continue, n to end" << endl;
	}
}

void startLevel(int level)
{
	system("cls");
	Game g(level);
	g.run();
}

void startGame()
{
	startLevel(0);
}



Game::Game(int level)
	: hu(9, 0)
{
	oldX = hu.getX();
	oldY = hu.getY();

	this->level = level;

	srand(time(NULL));

	for (int i = 0; i <= level; ++i)
	{
		int t = rand() % 4;
		if (t == 0) t = 4;
		vector<Obstacle*> line = dars.portion(i + 1, t);
		ve.push_back(line);
	}
}

Game::Game(int x, int y)
	: hu(x, y)
{
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
				cout << "y to continue, n to end" << endl;
				IS_END = true;
			}

			// If input = "y", reset. If input = "n", end game. Otherwise, read input again
			if (input == 89)
				startLevel(level);
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

		if (input == 76)
		{
			exitGame(&bgThread, &IS_RUNNING);

			saveGame();

			break;
		}

		if (input == 84)
		{
			exitGame(&bgThread, &IS_RUNNING);

			loadGame();

			break;
		}

		// Up, down, left, right
		moveHuman(input);

		// Human at finish line
		if (hu.atFinish())
		{
			Sleep(100);
			exitGame(&bgThread, &IS_RUNNING);

			if (level < 7)
				startLevel(level + 1);
			else
				startLevel(0);

			break;
		}

		Sleep(10);
	}
}

void Game::eraseHuman()
{
	gotoXY(oldY, oldX);
	cout << "_";
}

void Game::eraseObstacle()
{
	for (int i = 0; i < ve.size(); ++i)
	{
		for (int j = 0; j < ve[i].size(); ++j)
		{
			gotoXY(ve[i][j]->getMY(), ve[i][j]->getMX());
			cout << "_";
		}
	}
}

void Game::drawUpdateHuman()
{
	oldX = hu.getX();
	oldY = hu.getY();

	gotoXY(oldY, oldX);
	cout << "Y";
}

void Game::drawUpdateObstacle(bool fog)
{
	for (int i = 0; i < ve.size(); ++i)
	{
	for (int j = 0; j < ve[i].size(); ++j)
	{
		
		int tempX = ve[i][j]->getMX();
		int tempY = ve[i][j]->getMY();

		if (!fog || (abs(tempX - hu.getX()) + abs(tempY - hu.getY()) <= 5))
		{
			gotoXY(tempY, tempX);
			cout << "O";
		}
	}
}
}

void Game::drawFull()
{
	char map[10][10];

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			map[i][j] = '_';

	map[hu.getX()][hu.getY()] = 'Y';
	for (int i = 0; i < ve.size(); ++i)
	{
		for (int j = 0; j < ve[i].size(); ++j)
		{
			map[ve[i][j]->getMX()][ve[i][j]->getMY()] = 'O';
		}
	}
	system("cls");

	gotoXY(0, 0);

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cout << map[i][j];
		}
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

	Sleep(50);

	drawFull();

	// After the background thread is finished, merge it back into the main thread
	t->join();
}

void Game::moveObstacle(bool move)
{
	for (int i = 0; i < ve.size(); ++i)
	{
		for (int j = 0; j < ve[i].size(); ++j)
		{
			ve[i][j]->Move(move);
		}
	}
}

bool Game::isHumanDead()
{
	if (hu.isDead())
		return true;
	for (int i = 0; i < ve.size(); ++i)
	{
	for (int j = 0; j < ve[i].size(); ++j)
	{
		if (hu.collide(ve[i][j]))
			break;
	}
}
	return hu.isDead();
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

void Game::saveGame()
{
	drawFull();

	string path;
	cout << "Enter path:" << endl;
	getline(cin, path);

	ofstream fout;
	fout.open(path);

	fout << hu.getX() << " " << hu.getY() << endl;
	fout << level << endl;
	fout << ve.size() << endl;
	for (int i = 0; i < ve.size(); ++i)
	{

		for (int j = 0; j < ve[i].size(); ++j)
		{
			fout << ve[i][j]->getMX() << " " << ve[i][j]->getMY() << endl;
		}
	}

	fout.close();
}

void Game::loadGame()
{
	drawFull();

	string path;
	cout << "Enter path:" << endl;
	getline(cin, path);

	ifstream fin;
	fin.open(path);

	int tempX, tempY;
	fin >> tempX >> tempY;

	Game g(tempX, tempY);

	fin >> g.level;

	int size;
	fin >> size;

	for (int i = 0; i < size; ++i)
	{
		Obstacle* tempOb = new Obstacle(fin);
		g.ve[i].push_back(tempOb);
	}

	fin.close();

	g.run();
}

void Game::updateObstacle(bool move, bool fog)
{
	ve[0][0]->inc();

	if (!ve[0][0]->isTime())
		return;

	eraseObstacle();

	// Update obstacle positions
	moveObstacle(move);

	// Draw the map
	drawUpdateObstacle(fog);
}

Game::~Game()
{
	for (int i = 0; i < ve.size(); ++i)
	{
		for (int j = 0; j < ve[i].size(); ++j)
		{
			delete ve[i][j];
		}
	}
}
