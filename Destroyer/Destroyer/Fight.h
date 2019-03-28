#pragma once
#include "CharacterMain.h"
#include "MonsterMain.h"
#include "MonsterMain.h"
#include "GameIntro.h"
#include "Opening.h"
#include "GameIntro.h"
#include "CharacterMain.h"
#include <string>
#include <iostream>
// allows random numbers
#include <cstdlib>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
// allows pauses
#include <Windows.h>
#include <vector>
#include <time.h>


class Fight
{
private:
	CharacterMain mainPlayer;
	MonsterMain mainMonster;

	string choice;
	string item_choice;
#pragma region Constants
	const string YES = "Y";
	const string NO = "N";

	const string ATTACK = "A";
	const string RUN = "R";
	const string ITEM = "I";
	const string TALK = "T";

	// items that are allowed to be used
	const string HEALTH_POTION = "HEALTH_POTION";
	const string ATTACK_POTION = "ATTACK_POTION";
	const string XP_MULTIPLIER = "XP_MULTIPLIER";
	const string ESCAPE = "ESCAPE";
	const string SUPER_POTION = "SUPER_POTION";

	// constants for talking
	const string INTIMIDATE = "I";
	const string DIPLOMACY = "D";
	const string BLUFF = "B";
	const string CHARM = "C";
	const string STOP = "S";

	const int INTIMIDATE_WORK = 2;
	const int INTIMIDATE_NOT_WORK = 3;
	const int DIPLOMACY_WORK = 4;
	const int DIPLOMACY_NOT_WORK = 5;
	const int BLUFF_WORK = 6;
	const int BLUFF_NOT_WORK = 7;
	const int CHARM_WORK = 8;
	const int CHARM_NOT_WORK = 9;
	const int RUN_WORK = 10;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int SIX = 6;
	const int TEN = 10;

	const int CRIT = 10;
	const int MONSTER_CONSTITUTION_START = 3;
	// How low talking needs to go before the monster automatically hurts the player
	const int FAILURE = -6;

	// if the player dies
	const int DEAD = 11;
#pragma endregion

	int comparePlayer;
	int compareMonster;
	int damage;
	int playerLife;
	int monsterLife;
    int zero = 0;
	const int MULTIPLIER = 2;
	int randomOne;
	int randomTwo;
	
	int talking_place;
	int defense;

#pragma region Monster Variables
	// monster variables
	string firstChoice;
	// variable to check if talking worked with the monster
	string workedString;

	int worked;
	// part tells you which ai track to follow
	int part;

	int monsterChoice;
	int monsterVariable;

	// alice
	int strength_modifier;
	// Barimus
	int diplomacy_modifier;
	// donovo
	int constitution_modifier;
	// danial
	int dexterity_modifier;
	// constants for fighting
	const int RUNM = 1;
	const int FIGHTM = 2;
	const int DOUBLEDMGM = 3;
	const int DMGDISM = 4;
	const int ADVM = 5;
	const int NOTURNM = 6;
	const int TWOATTACKSM = 7;
	const int TALKM = 8;
	const int SIXDMG = 9;
	const int CHARMM = 10;
	const int DIPLOMACYM = 11;
	const int BLUFFM = 12;
	const int HEALM = 13;
	const int CRYM = 14;

	const double FOURTH = 0.25;
	// variables for the user's name and info
	string playerName;
	int playerInfo;

#pragma region Donovo stats
	int health_potions;
	int fealings;
#pragma endregion
#pragma endregion


public:

	Fight();
	Fight(int location, CharacterMain &player);
	Fight(CharacterMain &player, MonsterMain & monster);
	int formation(CharacterMain &character, MonsterMain &monster);
	int FirstFight(CharacterMain &character);

#pragma region User Choices

	int KillEmAll(CharacterMain &character, MonsterMain &monster);
	int RunAway(CharacterMain &character, MonsterMain &monster);
	int Item(CharacterMain &character, MonsterMain &monster);
	int Talk(CharacterMain &character, MonsterMain &monster);
	int YesOrNo();
	int UserChoice(CharacterMain &character, MonsterMain &monster);

#pragma endregion
	int MonsterFight(MonsterMain &monster, CharacterMain &character, int &part);
	int MonsterAction(CharacterMain &character, MonsterMain &monster);
	void FightSetup(CharacterMain &character, MonsterMain &monster);
	void Attack(CharacterMain &character, MonsterMain &monster);

	void DisplayConquests(CharacterMain &character, MonsterMain &monster);

#pragma region DONOVO FIGHTING AREA
	void DonovoFight(CharacterMain & character, int strenth_mod, int charisma_mod, int diplomacy_mod);
	int DonovoAI(MonsterMain & donovo, CharacterMain & player, int strenth_mod, int charisma_mod, int diplomacy_mod);
	int donovo_fell_good(MonsterMain & donovo);
	int donovo_Action(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod, int donovoChoice);
	int UserChoice(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod);
	int KillEmAll(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod);
	int RunAway(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod);
	int Item(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod);
	int Talk(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod);
#pragma endregion

	void AliceFight(CharacterMain & character, int strenth_mod, int charisma_mod, int diplomacy_mod);
	void AliceAI(MonsterMain & alice, CharacterMain & player);

	~Fight();
};

