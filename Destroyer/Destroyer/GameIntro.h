#pragma once
#include <string>
#include "Opening.h"
#include "Fight.h"
#include "Hide.h"
#include "CharacterMain.h"
#include "Opening.h"
#include "ConsoleControls.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "conio.h" // if this doesn't help with changing colors, get rid of it
#include <Windows.h>
#include <time.h>
#include <sys/types.h>



class GameIntro
{
private:
	// character settings
	std::string userName;
	std::string trueUserName;


	int xp = 0;
	int money = 10;
	int str = 3;
	int con = 4;
	int dex = 4;
	int intell = 3;
	int wis = 4;
	int charism = 2;

	// character choices
	std::string choice;
	int choice_int;
	int location;
	int subLocation;
	int firstTime;

	// Constant for choices
	const std::string YES = "Y";
	const std::string NO = "N";
	const std::string SAVED = "S";
	const std::string CHOICE_ONE = "O";
	const std::string CHOICE_TWO = "T";
	const std::string EXIT = "E";
	const std::string FIRST = "F";
	const std::string NEXT = "N";
	const std::string LAST = "L";
	const std::string ITEMS = "I";
	const std::string CANCEL = "C";

	// room strings
	std::string r_one;
	std::string r_two;
	std::string r_three;
	std::string r_title;
	int r_options;

	// ROOM OPTIONS
	double percentage;
#pragma region Constants for room settings

	// const ints for room setings
	const int ONE = 1; // starting value for people when alive, 0 is dead
	const int TWO = 2; // value for saved
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;
	const int SIX = 6;
	const int SEVEN = 7;
	const int EIGHT = 8;
	const int NINE = 9;
	const int TEN = 10;
	const int ELEVEN = 11;
	const int TWELVE = 12;
	const int THIRTEEN = 13;
	const int FOURTEEN = 14;
	const int FIFTEEN = 15;
	const int SIXTEEN = 16;
	const int SEVENTEEN = 17;
	const int EIGHTEEN = 18;
	const int NINETEEN = 19;
	const int TWENTY = 20;
	const int HUNDRED = 100;
	const double THREE_FOURTHS = 0.75;
	const double FIVE_HALVES = 2.5;

	const int BLACK = 0;
	const int DARKBLUE = 1;
	const int DARKCYAN = 2;
	const int DARKRED = 3;
	const int DARKMAGENTA = 4;
	const int DARKYELLOW = 5;
	const int DARKGRAY = 6;
	const int GRAY = 7;
	const int BLUE = 8;
	const int GREEN = 9;
	const int CYAN = 10;
	const int RED = 11;
	const int MAGENTA = 12;
	const int YELLOW = 13;
	const int WHITE = 14;
	const int DARKGREEN = 15;

	const std::string BACKGROUND = "BACKGROUND";
	const std::string FOREGROUND = "FOREGROUND";

#pragma endregion

	// areas
	const int EXIT_AREA = 12;
	const int DEAD = 11;
	const int BEGINING = 0;
	const int FRONT_ROOM = 1;
	const int R_ALISTAIR = 2;
	const int B_HALL = 3;
	const int R_DONOVO = 4;
	const int R_DANIEL = 5;
	const int TOP_LIVING_ROOM = 6;
	const int STORE = 7;
	const int T_HALL = 8;
	const int R_BARIMUS = 9;
	const int R_ALICE = 10;

	// save variables
	int iosNumber;
	int fileNumber;
	std::string fileName;

	// people constants
	const int ALIVE = 2;

	// loading variables
	int intHolder;
	std::string nameHolder;
	std::string textColor;

	// items
	const std::string HEALTH_POTION = "HEALTH_POTION";
	const std::string ATTACK_POTION = "ATTACK_POTION";
	const std::string XP_MULTIPLIER = "XP_MULTIPLIER";
	const std::string ESCAPE = "ESCAPE";
	const std::string EXTRA_HEALTH = "EXTRA_HEALTH";
	const std::string SUPER_POTION = "SUPER_POTION";
	const std::string EMPTY = "[EMPTY]";
	
	// music player
	std::string music;

public:
	GameIntro();
	int Start(CharacterMain & player);
	int LivingFormation(std::string title, std::string roomOne, std::string roomTwo, std::string roomThree, std::string colors);
	int SimpleFormation(std::string title, std::string roomOne, std::string optionTwo, std::string colors);
	
	// SELECTORS
	std::string YesOrNo();
	int ChooseANumber(int upperLimit);
	void SaveOrLoad(CharacterMain & player);
	void SimpleChooser();
	void NormalChooser();

	// Save and loads
	std::string SaveLoadChooser();
	void SaveGame(CharacterMain &player, std::string fileLocation);
	void LoadGame(CharacterMain &player, std::string fileLocation);

#pragma region ROOMS
	int Begining(CharacterMain &player);
	int Alistair(CharacterMain &player, int &time);
	void Cavernous_Room(CharacterMain &player);
	void Botom_Hall(CharacterMain &player);
	void Donovo(CharacterMain &player);
	void Daniel(CharacterMain &player);
	void T_L_Room(CharacterMain &player);
	void Bath_Room(CharacterMain &player);
	void Top_Hall(CharacterMain &player);
	void Barimus(CharacterMain &player);
	void Alice(CharacterMain &player);
#pragma endregion

	void Store(CharacterMain & player);
	void IncreaseStats(CharacterMain & player);

	void Talking_With_Donovo(CharacterMain & player);
	void Talking_With_Daniel(CharacterMain & player);
	std::string FirstOrSecond();

	// CONSOLE CONTROLLS
#pragma region COLOR CONTROL
	
#pragma endregion

	~GameIntro();
};

