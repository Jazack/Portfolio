#pragma once
#include "MonsterMain.h"
#include <string>
#include <string.h>
#include <iostream>
#include <Windows.h>

using namespace std;

MonsterMain::MonsterMain()
{
}

/// initializer for the boss monsters
MonsterMain::MonsterMain(string monstersName, int experience, int argent, int strength, int constitution, int dexterity, int intelligence, int wisdom, int charism)
{
	//argent is the money that is given, it's called that because I like French, and argent is money in French
	const int EIGHTH = 8;
	const int WEAK_MONSTER_HP_MOD = 4;
	xp = experience;
	money = argent;
	name = monstersName;
	con = constitution;
	str = strength;
	intell = intelligence;
	wis = wisdom;
	dex = dexterity;
	hp = constitution * WEAK_MONSTER_HP_MOD;
	charisma = charism;
	totalHP = hp;
	eighthHP = hp / EIGHTH;
}

/// Standard initializer for the average monster
MonsterMain::MonsterMain(string monstersName, int constitution, int strength, int intelligence, int wisdom, int dexterity, int charism)
{
	const int EIGHTH = 8;
	const int WEAK_MONSTER_HP_MOD = 4;
	name = monstersName;
	con = constitution;
	str = strength;
	intell = intelligence;
	wis = wisdom;
	dex = dexterity;
	hp = constitution * WEAK_MONSTER_HP_MOD;
	charisma = charism;
	totalHP = hp;
	eighthHP = hp / EIGHTH;
}

#pragma region Return Values

string MonsterMain::returnName()
{
	cout << name;
	return name;
}

int MonsterMain::returnHP()
{
	cout << hp;
	return hp;
}

#pragma endregion

#pragma region GetValues 

// get an eighth of the hp
int MonsterMain::getEighth()
{
	return eighthHP;
}

int MonsterMain::getXP()
{
	return xp;
}

int MonsterMain::getMoney()
{
	return money;
}

string MonsterMain::getName()
{
	//cout << name;
	return name;
}

int MonsterMain::setHP(int pain)
{
	hp = hp - pain;
	return 0;
}

int MonsterMain::changeHP(int pain)
{
	hp = pain;
	return hp;
}

int MonsterMain::getHP()
{
	return hp;
}

int MonsterMain::getTotalHP()
{
	return totalHP;
}

int MonsterMain::getCon()
{
	return con;
}

int MonsterMain::getStr()
{
	return str;
}

int MonsterMain::getDex()
{
	return dex;
}

int MonsterMain::getIntell()
{
	return intell;
}

int MonsterMain::getWis()
{
	return wis;
}

int MonsterMain::getCharisma()
{
	return charisma;
}

int MonsterMain::Wounded(int pain)
{
	hp = hp - pain;
	return 0;
}

#pragma endregion

/**
A FUNCTION TO INCREASE THE TOTAL XP GIVEN BY THE MONSTER
PARAM 1: increment
TYPE: int
PURPOSE: TO INCREASE THE XP GIVEN BY THE MONSTER
*/
void MonsterMain::increaseXP(int increment)
{
	xp = xp + increment;
}
MonsterMain::~MonsterMain()
{
}
