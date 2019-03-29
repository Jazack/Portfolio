#pragma once
#include "Opening.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <string.h>
#include "Credits.h"
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class CharacterMain
{
private:

	// CONSTANTS FOR ITEMS
	const string HEALTH_POTION = "HEALTH_POTION";
	const string ATTACK_POTION = "ATTACK_POTION";
	const string XP_MULTIPLIER = "XP_MULTIPLIER";
	const string ESCAPE = "ESCAPE";
	const string EXTRA_HEALTH = "EXTRA_HEALTH";
	const string SUPER_POTION = "SUPER_POTION";
	const string EMPTY = "[EMPTY]";

	const int TEN = 10;
	const int TWO = 2;
	const int FIVE = 5;
	const int NINE = 9;
	const int THREE = 3;
	const int X_AXIS = 4;

	string choice;
	string item_choice;
	const string YES =  "Y";
	const string NO = "N";

	string name;
	string arrayValue;
	
	int hp;
	int totalHP;
	int xp;
	int money;
	int region;

	int str;
	int con;
	int dex;
	int intell;
	int wis;
	int charisma;

	int value;

	int number;

	// veryfying the state of people
	int alistair_situation;
	int alice_situation;
	int donovo_situation;
	int barimus_situation;
	int daniel_situation;

	// variables for various rooms
	int r_Alistair_first_time = 0;

public:
	CharacterMain();
	CharacterMain(string nameOfPlayer, int experience, int argent, int place, int strength, int constitution, int dexterity, int intelligence, int wisdom, int charism, int alistair_situa, int alice_situa, int barimus_situa, int donovo_situa, int daniel_situa);
	
	int DisplayAll();
	
	int SetName();

#pragma region Changers

	int ChangeName(string newName);

#pragma endregion
	int HurtHP(int pain);

	string Retrieve_Items();
	string Retrieve_Items_Not_Combat();
	int Retrieve_Items(int a);
	int Retrieve_Items(string a);
	void Purchase_Item(int price, string name_of_item);

	// all the get files
	int getXP();
	string getName();
	int getHP();
	int getTotalHP();
	int getMoney();
	int getRegion();

	int getSTR();
	int getCon();
	int getDEX();
	int getInt();
	int getWis();
	int getCharisma();
	// getters for the arrays
	int getItemsInt(int location);
	string getItems(int location);

	// room getters
	int get_r_alistair();

	// all the setter files
	void setXP(int changer);
	void setName(string changer);
	void setHP(int changer);
	void setTotalHP();
	void setMoney(int changer);
	void setRegion(int changer);

	void setSTR(int changer);
	void setCon(int changer);
	void setDEX(int changer);
	void setInt(int changer);
	void setWis(int changer);
	void setCharisma(int changer);

	// array setters
	void setItemsInt(int location, int changer);
	void setItems(int location, string changer);

	// room setters
	void set_r_alistair(int changer);

	// increasers
	void increaseXP(int newXP);
	void increaseMoney(int newMoney);

	// veryfying the state of people
	// getters
	int get_alistair_situation();
	int get_alice_situation();
	int get_donovo_situation();
	int get_barimus_situation();
	int get_daniel_situation();
	// setters
	void set_alistair_situation(int changer);
	void set_alice_situation(int changer);
	void set_donovo_situation(int changer);
	void set_barimus_situation(int changer);
	void set_daniel_situation(int changer);

	int verify_number();
	~CharacterMain();
};

