#pragma once
#include <iostream>
#include <conio.h>
#include <math.h>
#include <vector>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

class Hide
{
private:
	int length;
	int height;
	int mySpeed;
	int enemySpeed;
	int speedTemp;
	int totalDistance;

	int status;

	char holdMeImScared;
	char haveFriend;
	char haveAttack;

	char const WALL = '#';
	char const FLOOR = '.';
	char const FRIEND = 'F';
	char const ATTACK = 'A';
	char const ENEMY = 'X';
	char const ME = 'I';

	int const FORTY_TWO = 42;
	int const TWELVE = 12;

public:
	Hide();
	
	void playHide();
	void playHide(int i);
	void MakeMap(char map[42][12]) const;
	void MyMove(char(&map)[42][12], int(&goodLocation)[2], int& myMove, char& itemOne, char& itemTwo);
	char EnemyMover(char(&map)[42][12], int(&goodLocation)[2], int(&badLocation)[2], char &underIt);
	char EnemyMover(char(&map)[42][12], int(&badLocation)[2], int(&goodLocation)[2], vector<int>& moving, char underIt);
	int TheDistance(int(&loctOne)[2], int(&loctTwo)[2]);
	int checkDistance(int first, int second);

	int getStatus() const;

	bool WinOrLose(int(&badLocation)[2], int(&goodLocation)[2], char haveOne, char haveTwo) const;

	bool pathExists(char(&map)[42][12], int startX, int startY, int(&loct)[2], int distance, vector<int>& vect);


	~Hide();
};

