#include "Game.h"

// Handles most background tasks
void backgroundThread(Game* gP, bool* IS_RUNNING_P, bool* IS_PAUSE_P, bool* soundOnP)
{
	gP->drawFull();

	bool SOUND = true;

	thread sThread(soundThread, &SOUND, soundOnP);

	int fogCounter = 0;

	bool move = true;
	bool fog = true;

	// While no reason to stop, and while human is still alive
	while (*IS_RUNNING_P & !gP->isHumanDead())
	{
		// If pause is true, loops until pause is false
		while (*IS_PAUSE_P);

		if (fogCounter < 350)
			++fogCounter;
		else
			fogCounter = 0;

		if (fogCounter < 275)
			fog = true;
		else
			fog = false;

		gP->updateObstacle(fog);

		gP->updateHuman();

		// Need to constantly check for collision so collision checking is handled by
		// background thread
		gP->isHumanDead();

		Sleep(10);
	}

	SOUND = false;

	sThread.join();

	// When there is collision, above loop will exit and the below line is printed
	// Depending on input, new game is started or program exits
	if (gP->isHumanDead())
	{
		gP->drawFull();

		gP->drawBomb();
		gotoXY(0, 36);

		if (*soundOnP)
			PlaySound(TEXT("sound/Bomb.wav"), NULL, SND_FILENAME);

		cout << "y to continue, n to end" << endl;
	}
}

void soundThread(bool* SOUND_P, bool* soundOnP)
{
	while (true)
	{
		if (!*SOUND_P)
			break;

		if (!*soundOnP)
			continue;

		PlaySound(TEXT("sound/car.wav"), NULL, SND_FILENAME);

		if (!*SOUND_P)
			break;
		PlaySound(TEXT("sound/dinosaur.wav"), NULL, SND_FILENAME);

		if (!*SOUND_P)
			break;
		PlaySound(TEXT("sound/truck.wav"), NULL, SND_FILENAME);

		if (!*SOUND_P)
			break;
		PlaySound(TEXT("sound/bird.wav"), NULL, SND_FILENAME);
	}
}

void startLevel(int* levelP, bool* soundOnP)
{
	system("cls");
	Game g(levelP, soundOnP);
	g.run();
}

void startGame()
{
	showConsoleCursor(false);

	int choose = 11;
	int normal = 10;
	int contColor = 8;

	string menu[] = { "1. New game", "2. Continue game", "3. Load game", "4. Settings", "5. Exit" };
	int len = 5;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
	for (int i = 0; i < len; ++i)
		cout << menu[i] << endl;

	bool soundOn = true;
	int level = 0;

	bool cont = false;

	int line = 0;

	bool stop = false;

	while (!stop)
	{
		if (!cont)
		{
			gotoXY(0, 1);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), contColor);
			cout << menu[1];
		}

		gotoXY(0, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), choose);
		cout << menu[line];

		int input = toupper(_getch());

		if (input == 69)
		{
			switch (line)
			{
			case 0:
			{
				level = 0;
				startLevel(&level, &soundOn);

				cont = true;

				break;
			}
			case 1:
			{
				if (!cont)
				{
					system("cls");
					cout << "You haven't played the game yet" << endl;
					_getch();
				}
				else
					startLevel(&level, &soundOn);

				break;
			}
			case 2:
			{
				system("cls");

				string path;
				cout << "Enter path:" << endl;
				getline(cin, path);

				Game g(&level, &soundOn, 0);
				g.loadGameFile(path);

				cont = true;

				break;
			}
			case 3:
			{
				settingsMenu(&soundOn, &level);

				break;
			}
			case 4:
				stop = true;
			}

			system("cls");

			gotoXY(0, 0);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
			for (int i = 0; i < len; ++i)
				cout << menu[i] << endl;
		}

		gotoXY(0, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
		cout << menu[line];

		if (input == 87)
		{
			if (line - 1 != -1)
				--line;
			else
				line = len - 1;
		}
		else if (input == 83)
		{
			if (line + 1 != len)
				++line;
			else
				line = 0;
		}
	}
}

void settingsMenu(bool* soundOnP, int* levelP)
{
	int choose = 11;
	int normal = 10;
	int soundColor = 7;

	string menu[] = { "1. Sound: ", "2. Level: ", "3. Return" };
	int len = 3;

	system("cls");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
	for (int i = 0; i < len; ++i)
		cout << menu[i] << endl;

	int line = 0;

	bool stop = false;

	while (!stop)
	{
		gotoXY(0, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), choose);
		cout << menu[line];

		gotoXY(10, 0);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), soundColor);
		cout << char((*soundOnP) ? 'Y' : 'N');

		gotoXY(10, 1);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), soundColor);
		cout << *levelP;

		int input = toupper(_getch());

		if (input == 69)
		{
			switch (line)
			{
			case 0:
			{
				*soundOnP = !*soundOnP;

				break;
			}
			case 1:
			{
				if (*levelP < 4)
					++*levelP;
				else
					*levelP = 0;

				break;
			}
			case 2:
				stop = true;
			}
		}

		gotoXY(0, line);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normal);
		cout << menu[line];

		if (input == 87)
		{
			if (line - 1 != -1)
				--line;
			else
				line = len - 1;
		}
		else if (input == 83)
		{
			if (line + 1 != len)
				++line;
			else
				line = 0;
		}
	}
}



Game::Game(int* levelP, bool* soundOnP, int dummy)
	: hu(0, 0)
{
	this->levelP = levelP;
	this->soundOnP = soundOnP;
}

Game::Game(int* levelP, bool* soundOnP)
	: hu(36, 75)
{
	this->soundOnP = soundOnP;

	oldX = hu.getX();
	oldY = hu.getY();

	this->levelP = levelP;

	srand(time(NULL));

	for (int i = 0; i <= *levelP; i += 1)
	{
		random_device rd;
		mt19937 g(rd());

		vector<int> arr = { 0, 1, 2, 3, 4 };
		shuffle(arr.begin(), arr.end(), g);

		int shift = rand() % 15;

		int lower = 20 + 5 * i;
		int upper = lower + 30 - 6 * i;

		int type = rand() % 4;

		for (int j = 0; j < 2; ++j)
		{
			Obstacle* tempOb = factory(type, (i + 1) * 6, arr[j] * 27 + shift, i % 2, lower, upper);
			ve.push_back(tempOb);
		}
	}
}

Game::Game(int x, int y, int* levelP, bool* soundOnP)
	: hu(x, y)
{
	this->levelP = levelP;
	this->soundOnP = soundOnP;
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
	thread bgThread(backgroundThread, this, &IS_RUNNING, &IS_PAUSE, soundOnP);

	// Input loop, stop when human is dead, ESC is pressed, or when human is at finish line
	while (true)
	{
		int input = toupper(_getch());

		// If dead, end game. Except when input = "y", then game is reset
		if (hu.isDead())
		{
			exitGame(&bgThread, &IS_RUNNING);

			drawBomb();
			gotoXY(0, 36);

			// To handle the unwanted effect where if the user hold a move button toward an
			// obstacle then the game will jump out
			// It is better when the game stop at a screen, notifying the user that they have lost
			// When the user collides with an obstacle, IS_END is set to true to avoid the _getch
			// loop joining the background thread multiple times
			cout << "y to continue, n to end" << endl;

			int input2 = input;

			// If input = "y", reset. If input = "n", end game. Otherwise, read input again
			while (true)
			{
				if (input2 == 89)
					startLevel(levelP, soundOnP);
				else if (input2 != 78)
				{
					input2 = toupper(_getch());
					continue;
				}

				break;
			}

			break;
		}

		// Input = "p"
		if (input == 80)
		{
			IS_PAUSE = true;

			while (true)
			{
				int input2 = toupper(_getch());

				if (input2 == 80)
				{
					IS_PAUSE = false;
					break;
				}
			}
		}

		// Input = ESC
		if (input == 27)
		{
			exitGame(&bgThread, &IS_RUNNING);
			break;
		}

		if (input == 76)
		{
			exitGame(&bgThread, &IS_RUNNING);

			string path = saveGame();

			cout << "y to continue, n to end" << endl;

			while (true)
			{
				int input2 = toupper(_getch());

				if (input2 == 89)
					loadGameFile(path);
				else if (input2 != 78)
					continue;

				break;
			}

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

			if (*levelP < 4)
			{
				++(*levelP);
				cout << "On to level " << (*levelP) << endl;
			}
			else
			{
				*levelP = 0;
				cout << "You have won. Back to level 0" << endl;
			}

			_getch();
			startLevel(levelP, soundOnP);

			break;
		}

		Sleep(10);
	}
}

void Game::updateHuman()
{
	int newX = hu.getX();
	int newY = hu.getY();

	string textureH[] = { "   ",
		"   ",
		" o ",
		"/|\\",
		"/ \\" };

	for (int i = 0; i < 5; ++i)
	{
		gotoXY(oldY, oldX + i);
		cout << "   ";
		gotoXY(newY, newX + i);
		cout << textureH[i];
	}

	oldX = newX;
	oldY = newY;
}

void Game::drawFull()
{
	system("cls");

	string textureH[] = { "   ",
		"   ",
		" o ",
		"/|\\",
		"/ \\" };

	for (int i = 0; i < 5; ++i)
	{
		gotoXY(hu.getY(), hu.getX() + i);
		cout << textureH[i];
	}

	for (int i = 0; i < ve.size(); ++i)
		for (int j = 0; j < 5; ++j)
		{
			gotoXY(ve[i]->getMY(), ve[i]->getMX() + j);
			cout << ve[i]->texture[j];
		}

	gotoXY(140, 36);
	cout << "Level " << *levelP;

	gotoXY(0, 36);
}

// Signals the background thread to stop
void Game::exitGame(thread* t, bool* IS_RUNNING_P)
{
	// Set bool to false, the loop in the background thread will exit
	*IS_RUNNING_P = false;

	// After the background thread is finished, merge it back into the main thread
	t->join();

	drawFull();
}

bool Game::isHumanDead()
{
	if (hu.isDead())
		return true;

	for (int i = 0; i < ve.size(); ++i)
	{
		if (hu.collide(ve[i]))
			break;
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

string Game::saveGame()
{
	drawFull();

	cout << "Saving" << endl;

	string path;
	cout << "Enter path:" << endl;
	getline(cin, path);

	ofstream fout;
	fout.open(path, ios::binary);

	int memblock[] = { hu.getX(), hu.getY() };
	fout.write((char*)memblock, sizeof(int) * 2);

	fout.write((char*)levelP, sizeof(int));

	int size = ve.size();
	fout.write((char*)&size, sizeof(int));

	ObstacleS* arr = new ObstacleS[size];

	for (int i = 0; i < ve.size(); ++i)
	{
		arr[i].type = ve[i]->type();
		arr[i].mX = ve[i]->getMX();
		arr[i].mY = ve[i]->getMY();
		arr[i].direction = ve[i]->getDirection();
		arr[i].lowerLight = ve[i]->getLower();
		arr[i].upperLight = ve[i]->getUpper();
	}

	fout.write((char*)arr, sizeof(ObstacleS) * size);

	delete[] arr;

	fout.close();

	return path;
}

void Game::loadGame()
{
	drawFull();

	cout << "Loading" << endl;

	string path;
	cout << "Enter path:" << endl;
	getline(cin, path);

	loadGameFile(path);
}

void Game::loadGameFile(string path)
{
	ifstream fin;
	fin.open(path, ios::binary);

	if (!fin.is_open())
		return;

	int memblock[2];
	fin.read((char*)memblock, sizeof(int) * 2);

	Game g(memblock[0], memblock[1], levelP, soundOnP);

	fin.read((char*)g.levelP, sizeof(int));

	int size;
	fin.read((char*)&size, sizeof(int));

	ObstacleS* arr = new ObstacleS[size];
	fin.read((char*)arr, sizeof(ObstacleS) * size);

	for (int i = 0; i < size; ++i)
	{
		Obstacle* tempOb = factory(arr[i].type, arr[i].mX, arr[i].mY, arr[i].direction,
			arr[i].lowerLight, arr[i].upperLight);
		g.ve.push_back(tempOb);
	}

	delete[] arr;

	fin.close();

	g.run();
}

void Game::updateObstacle(bool fog)
{
	ve[0]->inc();

	if (!ve[0]->isTime())
		return;

	// eraseObstacle();

	for (int i = 0; i < ve.size(); ++i)
	{
		int oldX = ve[i]->getMX();
		int oldY = ve[i]->getMY();

		ve[i]->Move();

		int newX = ve[i]->getMX();
		int newY = ve[i]->getMY();

		for (int j = 0; j < 5; ++j)
		{
			gotoXY(oldY, oldX + j);
			cout << ve[i]->empty;
			gotoXY(newY, newX + j);
			cout << ve[i]->texture[j];
		}
	}
}

void Game::drawBomb()
{
	string bomb[] = { "     ",
		".---.",
		"(\\|/)",
		"--0--",
		"(/|\\)" };

	for (int i = 0; i < 5; ++i)
	{
		gotoXY(hu.getY(), hu.getX() + i);
		cout << bomb[i];
	}
}

Obstacle* Game::factory(int type, int x, int y, int direction, int lowerLight, int upperLight)
{
	switch (type)
	{
	case 0:
		return new Car(x, y, direction, lowerLight, upperLight);
		break;
	case 1:
		return new Truck(x, y, direction, lowerLight, upperLight);
		break;
	case 2:
		return new Dinosaur(x, y, direction, lowerLight, upperLight);
		break;
	case 3:
		return new Bird(x, y, direction, lowerLight, upperLight);
		break;
	}
}

Game::~Game()
{
	for (int i = 0; i < ve.size(); ++i)
		delete ve[i];
}