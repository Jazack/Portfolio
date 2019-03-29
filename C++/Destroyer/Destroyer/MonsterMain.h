#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include <Windows.h>

using namespace std;

class MonsterMain
{
private:

	string name;
	int hp;
	int totalHP;
	double eighthHP;
	int xp;
	int money;

	int str;
	int con;
	int dex;
	int intell;
	int wis;
	int charisma;
	
	const double EIGHTH = 1 / 8;
	const int WEAK_MONSTER_HP_MOD = 4;

	const int FIVE = 5;
public:
	MonsterMain();
	MonsterMain(string monstersName, int experience, int argent, int strength, int constitution, int dexterity, int intelligence, int wisdom, int charism);
	MonsterMain(string monstersName, int constitution, int strength, int intelligence, int wisdom, int dexterity, int charism);
	int getHP();
	int getTotalHP();
	int getEighth();
	int getXP();
	int getMoney();
	string getName();
	int setHP(int pain);
	int changeHP(int pain);

	int getStr();
	int getCon();
	int getDex();
	int getIntell();
	int getWis();
	int getCharisma();

	void increaseXP(int increment);

	string returnName();
	int returnHP();
	int Wounded(int pain);
	~MonsterMain();

};
//(string monstersName, int experience, int argent, int strength, int constitution, int intelligence, int wisdom, int charism)

