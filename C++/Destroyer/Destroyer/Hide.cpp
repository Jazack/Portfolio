#include "Hide.h"
#include <iostream>
#include <Windows.h>
#pragma comment( lib, "winmm" )
Hide::Hide()
{
	
}

void Hide::playHide()
{
	PlaySound(TEXT("music\\danielFight.wav"), NULL, SND_LOOP | SND_ASYNC);
	const int FORTY_TWO = 42;
	const int TWELVE = 12;

	char const WALL = '#';
	char const FLOOR = '.';
	char const ATTACK = 'A';
	char const FRIEND = 'F';
	char const ENEMY = 'X';
	char const ME = 'I';

	int totalDistance;
	int yourLocation[2];
	yourLocation[0] = 6;
	yourLocation[1] = 1;
	int mySpeed = 1;

	char holdMeImScared = '.';
	char haveFriend = ',';
	char haveAttack = ',';

	int enemyLocation[2];
	enemyLocation[0] = 35;
	enemyLocation[1] = 6;
	int enemySpeed = 2;
	int time = 0;

	vector<int> movement;

	char myMap[FORTY_TWO][TWELVE];
	// make the walls
	for (int i = 0; i < FORTY_TWO; i++)
	{
		myMap[i][0] = WALL;
		myMap[i][11] = WALL;
	}
	for (int i = 0; i < TWELVE; i++)
	{
		myMap[0][i] = WALL;
		myMap[FORTY_TWO - 1][i] = WALL;
	}

	for (int j = 1; j < (TWELVE - 1); j++)
	{
		for (int i = 1; i < (FORTY_TWO - 1); i++)
		{
			myMap[i][j] = FLOOR;
		}
	}

	for (int i = 1; i < 4; i++)
	{
		myMap[i][3] = WALL;
		myMap[i + 1][2] = WALL;
		myMap[i][8] = WALL;
		myMap[13 + i][9] = WALL;
		myMap[13 + i][2] = WALL;
		myMap[24 + i][6] = WALL;
	}
	myMap[4][1] = WALL;
	myMap[18][6] = WALL;
	myMap[28][2] = WALL;
	myMap[27][5] = WALL;
	myMap[25][5] = WALL;
	myMap[25][9] = WALL;
	myMap[24][10] = WALL;
	myMap[23][9] = WALL;
	myMap[6][1] = ME;
	myMap[15][6] = ATTACK;
	myMap[1][10] = FRIEND;
	myMap[35][6] = ENEMY;

	for (int i = 8; i < 11; i++)
	{
		myMap[7][i] = WALL;
	}
	for (int i = 0; i < 4; i++)
	{
		myMap[11 + i][5 - i] = WALL;
		myMap[16 + i][9 - i] = WALL;
	}

	for (int i = 0; i < 3; i++)
	{
		myMap[11 + i][7 + i] = WALL;
		myMap[12 + i][5 + i] = WALL;
		myMap[15 + i][4 + i] = WALL;
		myMap[16 + i][2 + i] = WALL;
	}
	for (int i = 0; i < 5; i++)
	{
		myMap[24 + i][1] = WALL;
		myMap[24 + i][3] = WALL;
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			myMap[36 + i][5 + j] = WALL;
		}
	}
	MakeMap(myMap);
	do
	{

		movement.clear();
		totalDistance = TheDistance(yourLocation, enemyLocation);
		MyMove(myMap, yourLocation, mySpeed, haveFriend, haveAttack);
		system("CLS");
		MakeMap(myMap);
		if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
		{
			break;
		}
#pragma region Villian move

		if (time == 0)
		{
			time++;
			enemySpeed++;
		}
		else
		{
			time--;
			enemySpeed--;
		}
		if (totalDistance < 10)
		{
			int yesOrNo;
			for (int a = 9; a > 0; a--)
			{
				if (pathExists(myMap, enemyLocation[0], enemyLocation[1], yourLocation, 0 + a, movement))
				{
					yesOrNo = 0;
					break;
				}
				yesOrNo = 1;
			}
			if (yesOrNo == 0)
			{

				for (int i = 0; i < enemySpeed; i++)
				{
					holdMeImScared = EnemyMover(myMap, enemyLocation, yourLocation, movement, holdMeImScared);
					Sleep(100);
					system("CLS");
					MakeMap(myMap);
					if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
					{
						break;
					}
				}
				if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
				{
					break;
				}

			}
			else
			{
				for (int i = 0; i < enemySpeed; i++)
				{
					holdMeImScared = EnemyMover(myMap, yourLocation, enemyLocation, holdMeImScared);
					Sleep(100);
					system("CLS");
					MakeMap(myMap);
					if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
					{
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < enemySpeed; i++)
			{
				holdMeImScared = EnemyMover(myMap, yourLocation, enemyLocation, holdMeImScared);
				Sleep(100);
				system("CLS");
				MakeMap(myMap);
				if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
				{
					break;
				}
			}
		}
#pragma endregion

	} while (TRUE);
	if (haveFriend == 'F' && haveAttack == 'A')
	{
		cout << "CONGRATS! YOU MADE A NEW FRIEND!\n";
		status = 2;
	}
	else if (haveAttack == 'A')
	{
		cout << "CONGRATS! YOU WON THE BATTLE!\n";
		status = 0;
	}
	else
	{
		cout << "You lost!\n";
		status = 3;
	}
}

void Hide::playHide(int i)
{
	PlaySound(TEXT("music\\danielFight.wav"), NULL, SND_LOOP | SND_ASYNC);

	const int FORTY_TWO = 42;
	const int TWELVE = 12;

	char const WALL = '#';
	char const FLOOR = '.';
	char const ATTACK = 'A';
	char const ENEMY = 'X';
	char const ME = 'I';

	int totalDistance;
	int yourLocation[2];
	yourLocation[0] = 6;
	yourLocation[1] = 1;
	int mySpeed = 1;

	char holdMeImScared = '.';
	char haveFriend = ',';
	char haveAttack = ',';

	int enemyLocation[2];
	enemyLocation[0] = 35;
	enemyLocation[1] = 6;
	int enemySpeed = 2;
	int time = 0;

	vector<int> movement;

	char myMap[FORTY_TWO][TWELVE];
	// make the walls
	for (int i = 0; i < FORTY_TWO; i++)
	{
		myMap[i][0] = WALL;
		myMap[i][11] = WALL;
	}
	for (int i = 0; i < TWELVE; i++)
	{
		myMap[0][i] = WALL;
		myMap[FORTY_TWO - 1][i] = WALL;
	}

	for (int j = 1; j < (TWELVE - 1); j++)
	{
		for (int i = 1; i < (FORTY_TWO - 1); i++)
		{
			myMap[i][j] = FLOOR;
		}
	}

	for (int i = 1; i < 4; i++)
	{
		myMap[i][3] = WALL;
		myMap[i + 1][2] = WALL;
		myMap[i][8] = WALL;
		myMap[13 + i][9] = WALL;
		myMap[13 + i][2] = WALL;
		myMap[24 + i][6] = WALL;
	}
	myMap[4][1] = WALL;
	myMap[18][6] = WALL;
	myMap[28][2] = WALL;
	myMap[27][5] = WALL;
	myMap[25][5] = WALL;
	myMap[25][9] = WALL;
	myMap[24][10] = WALL;
	myMap[23][9] = WALL;
	myMap[6][1] = ME;
	myMap[15][6] = ATTACK;
	myMap[1][10] = FLOOR;
	myMap[35][6] = ENEMY;

	for (int i = 8; i < 11; i++)
	{
		myMap[7][i] = WALL;
	}
	for (int i = 0; i < 4; i++)
	{
		myMap[11 + i][5 - i] = WALL;
		myMap[16 + i][9 - i] = WALL;
	}

	for (int i = 0; i < 3; i++)
	{
		myMap[11 + i][7 + i] = WALL;
		myMap[12 + i][5 + i] = WALL;
		myMap[15 + i][4 + i] = WALL;
		myMap[16 + i][2 + i] = WALL;
	}
	for (int i = 0; i < 5; i++)
	{
		myMap[24 + i][1] = WALL;
		myMap[24 + i][3] = WALL;
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			myMap[36 + i][5 + j] = WALL;
		}
	}
	MakeMap(myMap);
	do
	{

		movement.clear();
		totalDistance = TheDistance(yourLocation, enemyLocation);
		MyMove(myMap, yourLocation, mySpeed, haveFriend, haveAttack);
		system("CLS");
		MakeMap(myMap);
		if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
		{
			break;
		}
#pragma region Villian move
		if (time == 0)
		{
			enemySpeed++;
			time++;
		}
		else
		{
			enemySpeed--;
			time--;
		}
		if (totalDistance < 10)
		{
			if (pathExists(myMap, enemyLocation[0], enemyLocation[1], yourLocation, 0, movement))
			{

				for (int i = 0; i < enemySpeed; i++)
				{
					holdMeImScared = EnemyMover(myMap, enemyLocation, yourLocation, movement, holdMeImScared);
					Sleep(100);
					system("CLS");
					MakeMap(myMap);
					if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
					{
						break;
					}
				}
				if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
				{
					break;
				}

			}
			else
			{
				for (int i = 0; i < enemySpeed; i++)
				{
					holdMeImScared = EnemyMover(myMap, yourLocation, enemyLocation, holdMeImScared);
					Sleep(100);
					system("CLS");
					MakeMap(myMap);
					if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
					{
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < enemySpeed; i++)
			{
				holdMeImScared = EnemyMover(myMap, yourLocation, enemyLocation, holdMeImScared);
				Sleep(100);
				system("CLS");
				MakeMap(myMap);
				if (WinOrLose(enemyLocation, yourLocation, haveFriend, haveAttack))
				{
					break;
				}
			}
		}
#pragma endregion

	} while (TRUE);
	if (haveFriend == 'F' && haveAttack == 'A')
	{
		cout << "CONGRATS! YOU MADE A NEW FRIEND!\n";
		status = 2;
	}
	else if (haveAttack == 'A')
	{
		cout << "CONGRATS! YOU WON THE BATTLE!\n";
		status = 0;
	}
	else
	{
		cout << "You lost!\n";
		status = 3;
	}
}



void Hide::MakeMap(char map[42][12]) const
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char const WALL = '#';
	char const FLOOR = '.';
	char const FRIEND = 'F';
	char const ATTACK = 'A';
	char const ENEMY = 'X';
	char const ME = 'I';

	for (int j = 0; j < (TWELVE); j++)
	{
		for (int i = 0; i < (FORTY_TWO); i++)
		{
			if (map[i][j] == WALL || i == 41)
			{
				SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
			}
			else if (map[i][j] == FLOOR)
			{
				SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (map[i][j] == ME)
			{
				SetConsoleTextAttribute(hconsole, FOREGROUND_GREEN);
			}
			else if (map[i][j] == ENEMY)
			{
				SetConsoleTextAttribute(hconsole, FOREGROUND_RED);
			}
			else if (map[i][j] == ATTACK)
			{
				SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_GREEN);
			}
			else if (map[i][j] == FRIEND)
			{
				SetConsoleTextAttribute(hconsole, FOREGROUND_BLUE);
			}

			cout << map[i][j];
		}
		cout << endl;
	}
}

void Hide::MyMove(char(&map)[42][12], int(&goodLocation)[2], int & myMove, char& itemOne, char& itemTwo)
{
	int c;
	c = 0;
	int currentMove = myMove;
	do
	{


		switch ((c = _getch())) {
		case KEY_UP:
			if (map[goodLocation[0]][goodLocation[1] - 1] == '#')
			{
				break;
			}
			else
			{
				if (map[goodLocation[0]][goodLocation[1] - 1] == 'F')
				{
					itemOne = map[goodLocation[0]][goodLocation[1] - 1];
				}
				if (map[goodLocation[0]][goodLocation[1] - 1] == 'A')
				{
					itemTwo = map[goodLocation[0]][goodLocation[1] - 1];
				}
				map[goodLocation[0]][goodLocation[1]] = '.';
				map[goodLocation[0]][goodLocation[1] - 1] = 'I';
				goodLocation[1] = goodLocation[1] - 1;
				currentMove--;
			}
			break;
		case KEY_DOWN:
			if (map[goodLocation[0]][goodLocation[1] + 1] == '#')
			{
				break;
			}
			else
			{
				if (map[goodLocation[0]][goodLocation[1] + 1] == 'F')
				{
					itemOne = map[goodLocation[0]][goodLocation[1] + 1];
				}
				if (map[goodLocation[0]][goodLocation[1] + 1] == 'A')
				{
					itemTwo = map[goodLocation[0]][goodLocation[1] + 1];
				}
				map[goodLocation[0]][goodLocation[1]] = '.';
				map[goodLocation[0]][goodLocation[1] + 1] = 'I';
				goodLocation[1] = goodLocation[1] + 1;
				currentMove--;
			}
			break;
		case KEY_LEFT:
			if (map[goodLocation[0] - 1][goodLocation[1]] == '#')
			{
				break;
			}
			else
			{
				if (map[goodLocation[0] - 1][goodLocation[1]] == 'F')
				{
					itemOne = map[goodLocation[0] - 1][goodLocation[1]];
				}
				if (map[goodLocation[0] - 1][goodLocation[1]] == 'A')
				{
					itemTwo = map[goodLocation[0] - 1][goodLocation[1]];
				}
				map[goodLocation[0]][goodLocation[1]] = '.';
				map[goodLocation[0] - 1][goodLocation[1]] = 'I';
				goodLocation[0] = goodLocation[0] - 1;
				currentMove--;
			}
			break;
		case KEY_RIGHT:
			if (map[goodLocation[0] + 1][goodLocation[1]] == '#')
			{
				break;
			}
			else
			{
				if (map[goodLocation[0] + 1][goodLocation[1]] == 'F')
				{
					itemOne = map[goodLocation[0] + 1][goodLocation[1]];
				}
				if (map[goodLocation[0] + 1][goodLocation[1]] == 'A')
				{
					itemTwo = map[goodLocation[0] + 1][goodLocation[1]];
				}
				map[goodLocation[0]][goodLocation[1]] = '.';
				map[goodLocation[0] + 1][goodLocation[1]] = 'I';
				goodLocation[0] = goodLocation[0] + 1;
				currentMove--;
			}
			break;
		default:
			break;
		}

	} while (currentMove != 0);
}

char Hide::EnemyMover(char(&map)[42][12], int(&goodLocation)[2], int(&badLocation)[2], char &underIt)
{
	char placeHolder;
	map[badLocation[0]][badLocation[1]] = underIt;
	if (goodLocation[0] == badLocation[0])
	{
		if (goodLocation[1] < badLocation[1])
		{
			if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
		}
		else
		{
			if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
		}
	}
	if (goodLocation[1] == badLocation[1])
	{
		if (goodLocation[0] < badLocation[0])
		{
			if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
		}
		else
		{
			if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}

		}
	}
	if (goodLocation[0] < badLocation[0] && goodLocation[1] < badLocation[1])
	{
		if ((goodLocation[0] - badLocation[0]) < (goodLocation[1] - badLocation[1]))
		{
			if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
		}
		else
		{
			if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}

			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
		}
	}
	if (goodLocation[0] < badLocation[0] && goodLocation[1] > badLocation[1])
	{
		if ((goodLocation[0] - badLocation[0]) < (goodLocation[1] - badLocation[1]))
		{
			if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
		}
		else
		{

			if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
		}
	}
	if (goodLocation[0] > badLocation[0] && goodLocation[1] < badLocation[1])
	{
		if ((goodLocation[0] - badLocation[0]) < (goodLocation[1] - badLocation[1]))
		{
			if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}

		}
		else
		{
			if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
		}
	}
	if (goodLocation[0] > badLocation[0] && goodLocation[1] > badLocation[1])
	{
		if ((goodLocation[0] - badLocation[0]) < (goodLocation[1] - badLocation[1]))
		{
			if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}

		}
		else
		{
			if (map[badLocation[0] + 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] + 1] != '#')
			{
				badLocation[1] = badLocation[1] + 1;
			}
			else if (map[badLocation[0]][badLocation[1] - 1] != '#')
			{
				badLocation[1] = badLocation[1] - 1;
			}
			else if (map[badLocation[0] - 1][badLocation[1]] != '#')
			{
				badLocation[0] = badLocation[0] - 1;
			}
		}
	}
	placeHolder = map[badLocation[0]][badLocation[1]];
	map[badLocation[0]][badLocation[1]] = 'X';
	return placeHolder;
}

char Hide::EnemyMover(char(&map)[42][12], int(&badLocation)[2], int(&goodLocation)[2], vector<int>& moving, char underIt)
{
	char placeHolder;
	if (goodLocation[0] == badLocation[0] && goodLocation[1] == badLocation[1] + 1)
	{
		badLocation[1] = badLocation[1] + 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0]][badLocation[1] - 1] = underIt;

	}
	else if (goodLocation[0] == badLocation[0] && goodLocation[1] == badLocation[1] - 1)
	{
		badLocation[1] = badLocation[1] - 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0]][badLocation[1] + 1] = underIt;

	}
	else if (goodLocation[0] == badLocation[0] + 1 && goodLocation[1] == badLocation[1])
	{
		badLocation[0] = badLocation[0] + 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0] - 1][badLocation[1]] = underIt;

	}
	else if (goodLocation[0] == badLocation[0] - 1 && goodLocation[1] == badLocation[1])
	{
		badLocation[0] = badLocation[0] - 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0] + 1][badLocation[1]] = underIt;

	}
	else if (moving.back() == 0)
	{
		badLocation[1] = badLocation[1] - 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0]][badLocation[1] + 1] = underIt;
		moving.pop_back();
	}
	else if (moving.back() == 1)
	{
		badLocation[1] = badLocation[1] + 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0]][badLocation[1] - 1] = underIt;
		moving.pop_back();
	}
	else if (moving.back() == 2)
	{
		badLocation[0] = badLocation[0] - 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0] + 1][badLocation[1]] = underIt;
		moving.pop_back();
	}
	else if (moving.back() == 3)
	{
		badLocation[0] = badLocation[0] + 1;
		placeHolder = map[badLocation[0]][badLocation[1]];
		map[badLocation[0]][badLocation[1]] = 'X';
		map[badLocation[0] - 1][badLocation[1]] = underIt;
		moving.pop_back();
	}
	return placeHolder;
}

int Hide::TheDistance(int(&loctOne)[2], int(&loctTwo)[2])
{

	return sqrt(pow((loctOne[0] - loctTwo[0]), 2) + pow((loctOne[1] - loctTwo[1]), 2));
}

int Hide::checkDistance(int first, int second)
{
	return first - second;
}

int Hide::getStatus() const
{
	return status;
}

bool Hide::WinOrLose(int(&badLocation)[2], int(&goodLocation)[2], char haveOne, char haveTwo) const
{
	if (goodLocation[0] == badLocation[0] && goodLocation[1] == badLocation[1])
	{
		return true;
	}
	return false;
}

bool Hide::pathExists(char(&map)[42][12], int startX, int startY, int(&loct)[2], int distance, vector<int> &vect)
{


	if (map[startX][startY] == '#')
	{
		return false;
	}

	if (startX == loct[0] && startY == loct[1])
	{
		return true;
	}
	if (distance == 10)
	{
		return false;
	}
#pragma region the X-coordinates ==

	if (loct[0] == startX)
	{
		if (checkDistance(loct[1], startY) < 0) // checks to see if you are above it
		{
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}

		}
		else
		{
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
		}
	}
#pragma endregion

#pragma region The y-coordinates ==

	else if (loct[1] == startY)
	{
		if (checkDistance(loct[0], startX) < 0) // checks if you are to the right of it
		{
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}

		}
		else
		{
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
		}
	}
#pragma endregion
#pragma region upper left

	else if (loct[0] < startX && loct[1] < startY) // checks if you are to the upper left
	{
		if ((startX - loct[0]) < (startY - loct[1]))
		{
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
		}
		else
		{
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
		}
	}
#pragma endregion
#pragma region lower left
	else if (loct[0] < startX && loct[1] > startY) // checks if you are to the lower left
	{
		if ((startX - loct[0]) < (loct[1] - startY))
		{
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
		}
		else
		{
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
		}
	}
#pragma endregion
#pragma region upper right

	else if (loct[0] > startX && loct[1] < startY) // checks if you are to the upper right
	{
		if ((loct[0] - startX) < (startY - loct[1]))
		{
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
		}
		else
		{
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
		}
	}
#pragma endregion
#pragma region lower right
	else if (loct[0] > startX && loct[1] > startY) // checks if you are to the lower right
	{
		if ((loct[0] - startX) < (loct[1] - startY))
		{
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}

		}
		else
		{
			if (pathExists(map, startX, startY + 1, loct, distance + 1, vect))
			{
				vect.push_back(1);
				return true;
			}
			if (pathExists(map, startX + 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(3);
				return true;
			}
			if (pathExists(map, startX - 1, startY, loct, distance + 1, vect))
			{
				vect.push_back(2);
				return true;
			}
			if (pathExists(map, startX, startY - 1, loct, distance + 1, vect))
			{
				vect.push_back(0);
				return true;
			}
		}
	}
#pragma endregion
	return false;
}

Hide::~Hide()
{
}
