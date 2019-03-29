#include "CharacterMain.h"
#include <Windows.h>
#pragma comment( lib, "winmm" )

string items[10][2];
int itemsInt[10][2];

int main()
{
	Opening();
	cout << "THANK YOU FOR PLAYING!\n";
	Sleep(1000);
	return 0;
}

CharacterMain::CharacterMain()
{
}


#pragma region Main formation

CharacterMain::CharacterMain(string nameOfPlayer, int experience, int argent, int place, int strength, int constitution, int dexterity, int intelligence, int wisdom, int charism, int alistair_situa, int alice_situa, int barimus_situa, int donovo_situa, int daniel_situa)
{
#pragma region Variables
	// initialize string items
	alistair_situation = alistair_situa; // 1 = alive, 2 = friends, 0 = dead
	alice_situation = alice_situa;
	donovo_situation = donovo_situa;
	barimus_situation = barimus_situa;
	daniel_situation = daniel_situa;
	const int TEN = 10;
	const int TWO = 2;
	const int THREE = 3;
	const int X_AXIS = 4;
	// for Alistairs room, to verify the first time it has been used
	r_Alistair_first_time = 0;
#pragma endregion


	int number = 1;
#pragma region items[i][1]
	// initialize items[i][1] to be equal to their number options
	items[0][1] = "  (1)";
	items[1][1] = "  (2)";
	items[2][1] = "  (3)";
	items[3][1] = "  (4)";
	items[4][1] = "  (5)";
	items[5][1] = "  (6)";
	items[6][1] = "  (7)";
	items[7][1] = "  (8)";
	items[8][1] = "  (9)";
	items[9][1] = " (10)";

#pragma endregion

	for (int i = 0; i < TEN; i++)
	{
		number = i + 1;
		items[i][0] = "[EMPTY]";
		items[i][1] = "QUANTATY";
		itemsInt[i][0] = number;
		itemsInt[i][1] = 0;
	}
	const int FIVE = 5;
	name = nameOfPlayer;
	hp = constitution * FIVE;
	totalHP = hp;
	xp = experience;
	money = argent;
	region = place;

	str = strength;
	con = constitution;
	dex = dexterity;
	intell = intelligence;
	wis = wisdom;
	charisma = charism;
}
#pragma endregion

/**
Purpose:  Change the name of the user
param: name
type: string
purpose: to change the name of the player
*/
int CharacterMain::ChangeName(string newName)
{
	//change the player name
	name = newName;
	// return 0;
	return 0;
}// end of function

#pragma region Set Name
/**
PURPOSE: THIS IS THE CODE THAT CHANGES THE NAME
*/
int CharacterMain::SetName()
{
	choice = "zero";
	do
	{
		cout << "WHAT IS YOUR NAME THAN?\n";
		getline(cin, name);
		cout << "IS " << name << " CORRECT?(Y/N)\n";
		getline(cin, choice);
		choice = toupper(choice[0]);
		if (choice != YES && choice != NO)
		{
			do
			{
				cout << "SORRY, I DIDN'T CATCH THAT, IS " << name << " CORRECT?(Y/N)\n";
				getline(cin, choice);
				choice = toupper(choice[0]);
			} while (choice != YES && choice != NO);
		}

		if (choice == YES)
		{
			cout << "THAT'S GREAT!\n";
		}
	} while (choice != YES);
	return 0;
}

#pragma endregion

#pragma region Retrieve items out of combat
/**
A FUNCTION TO GET THE NON COMBAT ITEMS THAT ARE AVAILABLE TO BE USED

CURRENTLY JUST THE HP INCREASER
*/
string CharacterMain::Retrieve_Items_Not_Combat()
{
	cout << "\n";
	// repeat for every spot in items
	for (int i = 0; i < TEN; i++)
	{
		cout << itemsInt[i][0];
		cout << " ";
		cout << items[i][0];
		cout << " ";
		cout << items[i][1];
		cout << " ";
		cout << itemsInt[i][1];
		cout << "\n";
	}

	cout << "\n\n CHOOSE THE NUMBER FOR THE ITEM THAT YOU WANT TO USE\n";
	cout << "OR PRESS \"0\" TO RETURN\n";

	string item_choice = EMPTY;

	// set a loop to verify that the user's input works
	do
	{
		// insert user's input into number
		number = verify_number();

		// verify every input value for items
		for (int i = 0; i < TEN; i++)
		{
			// verify that the item in question has actual value
			if (number == itemsInt[i][0] && items[i][0] != EMPTY && items[i][0] != HEALTH_POTION && items[i][0] != ATTACK_POTION && items[i][0] != XP_MULTIPLIER && items[i][0] != ESCAPE && items[i][0] != SUPER_POTION)
			{
				itemsInt[i][1]--;
				item_choice = items[i][0];
				// if itemsInt section two is equal to 0, set items 0 to EMPTY
				if (itemsInt[i][1] == 0)
				{
					items[i][0] = EMPTY;
				}

				break;
			}// end for loop
			if (number == itemsInt[i][0])
			{
				break;
			}
		}

		// IF NUMBER = 0, BREAK
		if (number == 0 || item_choice != EMPTY)
			break;
		// tell the user that that they entered an incorrect value
		cout << "I DON'T THINK I CAN USE THAT, MAYBE I SHOULD TRY SOMETHING ELSE\n";
		

	} while (true);

	// return 0
	return item_choice;
}
#pragma endregion

#pragma region Retrieve Items

/// a method to retrieve the vector items within combat
string CharacterMain::Retrieve_Items()
{
	cout << "\n";
	// repeat for every spot in items
	for (int i = 0; i < TEN; i++)
	{
		cout << itemsInt[i][0];
		cout << " ";
		cout << items[i][0];
		cout << " ";
		cout << items[i][1];
		cout << " ";
		cout << itemsInt[i][1];
		cout << "\n";
	}

	cout << "\n\n CHOOSE THE NUMBER FOR THE ITEM THAT YOU WANT TO USE\n";
	cout << "OR PRESS \"0\" TO ESCAPE (WILL SKIP TURN)\n";

	string item_choice = EMPTY;
#pragma region Do while loop to verify the users input works
	// set a loop to verify that the user's input works
	do
	{
		// insert user's input into number
		number = verify_number();

		// verify every input value for items
		for (int i = 0; i < TEN; i++)
		{
			// verify that the item in question has actual value
			if (number == itemsInt[i][0] && items[i][0] != EMPTY && items[i][0] != EXTRA_HEALTH)
			{
				itemsInt[i][1]--;
				item_choice = items[i][0];
				// if itemsInt section two is equal to 0, set items 0 to EMPTY
				if (itemsInt[i][1] == 0)
				{
					items[i][0] = EMPTY;
				}
				
				break;
			}// end for loop

		}

		// IF NUMBER = 0, BREAK
		if (number == 0 || item_choice != EMPTY)
			break;
		// tell the user that that they entered an incorrect value
		cout << "I DON'T THINK I CAN USE THAT, MAYBE I SHOULD TRY SOMETHING ELSE\n";
		cin >> number;
		
	} while (true);
#pragma endregion
	// return 0
	return item_choice;
}
#pragma endregion

#pragma region Retrieve items by location

/**
a function to retrieve specific sections of the array
PARAM 1: a
TYPE: int
PURPOSE: TO IDENTIFY WHAT LOCATION IS DESIRED TO BE RETRIEVED
*/
int CharacterMain::Retrieve_Items(int a)
{
	cout << itemsInt[a][0];
	cout << " ";
	cout << items[a][0];//name
	cout << " ";
	cout << items[a][1];//"quantity"
	cout << " ";
	cout << itemsInt[a][1];//quantity
	cout << "\n";
	return 0;
}
#pragma endregion

#pragma region Purchasing
/**
A FUNCTION TO PURCHASE AN ITEM
PARAM 1: price
TYPE: int
PURPOSE: TO DETERMINE THE PRICE OF THE ITEM
PARAM 2: name_of_item
TYPE: string
PURPOSE: TO DEFINE THE ITEM BEING BOUGHT
*/
void CharacterMain::Purchase_Item(int price, string name_of_item)
{
	// declare constants
	const int TEN = 10;
	const int FIVE = 5;
	// run it through a for loop to find the section
	if (money - price > 0)
	{
		for (int i = 0; i < TEN; i++)
		{
			// see if this is the item desired, if so add one to the quantity
			if (items[i][0] == name_of_item && itemsInt[i][1] < FIVE)
			{
				itemsInt[i][1]++;
				setMoney(money - price);
				break;
			}
			// verify if this section is empty, if so, change the items to the item being bought,
			// and increase the quantity by 1
			if (items[i][0] == EMPTY)
			{
				items[i][0] = name_of_item;
				itemsInt[i][1]++;
				setMoney(money - price);
				break;
			}
			if (i == NINE)
			{
				cout << "SORRY, BUT YOU DO NOT HAVE ANY SPACE FOR " << name_of_item << " IN YOUR INVENTORY\n";
				break;
			}
		}

	}
	else
	{
		cout << "SORRY, BUT YOU DO NOT HAVE ENOUGH CURRENCY TO BUY THIS ITEM RIGHT NOW\n";
	}
	system("PAUSE");
}
#pragma endregion


/// a method to hurt your HP
int CharacterMain::HurtHP(int pain)
{
	hp = hp - pain;
	return 0;
}

#pragma region GET functions

#pragma region Name, XP, HP, totHP
/**
a method to get the xp
*/
int CharacterMain::getXP()
{
	return xp;
}

/**
a method to get the total HP
*/
int CharacterMain::getTotalHP()
{
	return totalHP;
}

/**
Returns the players hp
*/
int CharacterMain::getHP()
{
	return hp;
}
/**
Returns the players name
*/
string CharacterMain::getName()
{
	return name;
}
/**
Returns the players money
*/
int CharacterMain::getMoney()
{
	return money;
}
/**
Returns the players region
*/
int CharacterMain::getRegion()
{
	return region;
}
#pragma endregion

#pragma region main stats

int CharacterMain::getSTR()
{
	return str;
}

int CharacterMain::getCon()
{
	return con;
}

int CharacterMain::getDEX()
{
	return dex;
}

int CharacterMain::getInt()
{
	return intell;
}

int CharacterMain::getWis()
{
	return wis;
}

int CharacterMain::getCharisma()
{
	return charisma;
}

#pragma endregion

#pragma region Room Getters

/**
A FUNCTION TO RETURN THE VALUE OF r_Alistair_first_time
*/
int CharacterMain::get_r_alistair()
{
	return r_Alistair_first_time;
}

#pragma endregion

#pragma region Array Getters
/**
A FUNCTION TO RETURN THE VALUE OF AN ITEM
PARAM 1: location
TYPE: int
PURPOSE: TO DETERMINE WHAT ITEM IS DESIRED
*/
int CharacterMain::getItemsInt(int location)
{
	return itemsInt[location][1];
}

/**
A FUNCTION TO RETURN THE NAME OF AN ITEM
PARAM 1: location
TYPE: int
PURPOSE: TO DETERMINE WHAT ITEM IS DESIRED
*/
string CharacterMain::getItems(int location)
{
	return items[location][0];
}
#pragma endregion

#pragma region State of others
int CharacterMain::get_alistair_situation()
{
	return alistair_situation;
}
int CharacterMain::get_alice_situation()
{
	return alice_situation;
}
int CharacterMain::get_donovo_situation()
{
	return donovo_situation;
}
int CharacterMain::get_barimus_situation()
{
	return barimus_situation;
}
int CharacterMain::get_daniel_situation()
{
	return daniel_situation;
}
#pragma endregion

#pragma endregion

#pragma region Set functions

#pragma region main stats
/**
sets the xp
*/
void CharacterMain::setXP(int changer)
{
	xp = changer;
}

/**
sets the name
*/
void CharacterMain::setName(string changer)
{
	name = changer;
}

/**
sets the hp
*/
void CharacterMain::setHP(int changer)
{
	hp = changer;
}
/**
sets the total hp
*/
void CharacterMain::setTotalHP()
{
	totalHP = con * FIVE;
}

/**
sets the money
*/
void CharacterMain::setMoney(int changer)
{
	money = changer;
}

/**
sets the region
*/
void CharacterMain::setRegion(int changer)
{
	region = changer;
}

/**
sets the str
*/
void CharacterMain::setSTR(int changer)
{
	str = changer;
}

/**
sets the con
*/
void CharacterMain::setCon(int changer)
{
	con = changer;
}

/**
sets the dex
*/
void CharacterMain::setDEX(int changer)
{
	dex = changer;
}

/**
sets the int
*/
void CharacterMain::setInt(int changer)
{
	intell = changer;
}

/**
sets the wis
*/
void CharacterMain::setWis(int changer)
{
	wis = changer;
}

/**
sets the charisma
*/
void CharacterMain::setCharisma(int changer)
{
	charisma = changer;
}
#pragma endregion

#pragma region Room setters

/**
A FUNCTION TO CHANGE THE FIRST TIME VARIABLE FOR ALISTAIR'S ROOM
*/
void CharacterMain::set_r_alistair(int changer)
{
	r_Alistair_first_time = changer;
}

#pragma endregion

#pragma region Array Setters

/**
A FUNCTION TO SET THE VALUE OF ITEMSINT
PARAM 1: location
TYPE: int
PURPOSE: TO DETERMINE THE ADDRESS DESIRED

PARAM 2: changer
TYPE: int
PURPOSE: TO CHANGE THE ARRAY LOCATIONS VALUE
*/
void CharacterMain::setItemsInt(int location, int changer)
{
	itemsInt[location][1] = changer;
}
/**
A FUNCTION TO SET THE VALUE OF ITEMSINT
PARAM 1: location
TYPE: int
PURPOSE: TO DETERMINE THE ADDRESS DESIRED

PARAM 2: changer
TYPE: string
PURPOSE: TO CHANGE THE ARRAY LOCATIONS VALUE
*/
void CharacterMain::setItems(int location, string changer)
{
	items[location][0] = changer;
}
#pragma endregion

#pragma region state of others
void CharacterMain::set_alistair_situation(int changer)
{
	alistair_situation = changer;
}
void CharacterMain::set_alice_situation(int changer)
{
	alice_situation = changer;
}
void CharacterMain::set_donovo_situation(int changer)
{
	donovo_situation = changer;
}
void CharacterMain::set_barimus_situation(int changer)
{
	barimus_situation = changer;
}
void CharacterMain::set_daniel_situation(int changer)
{
	daniel_situation = changer;
}

#pragma endregion


#pragma endregion


/// A function to display all of the stats
int CharacterMain::DisplayAll()
{
	cout << name << "\nHEALTH: " << hp << "      XP: " << xp << "\nMONEY: " << money << "\nSTRENGTH: " << str << "\nCONSTITUTION: " << con << "\nDEXTERITY: " << dex << "\nINTELLIGENCE: " << intell << "\nWISDOM: " << wis << "\nCHARISMA: " << charisma << "\n\n";
	return 0;
}


/**
A FUNCTION TO INCREASE THE XP THAT THE PLAYER HAS
PARAM 1: newXP
TYPE: int
PURPOSE: TO BE USED IN INCREASING THE XP OF THE PLAYER
*/
void CharacterMain::increaseXP(int newXP)
{
	xp = xp + newXP;
}

/**
A FUNCTION TO INCREASE THE TOTAL MONEY THAT THE PLAYER HAS
PARAM 1: newMoney
TYPE: int
PURPOSE: TO INCREASE THE TOTAL MONEY THAT THE PLAYER HAS
*/
void CharacterMain::increaseMoney(int newMoney)
{
	money = money + newMoney;
}

#pragma region Verify the Number
/**
A FUNCTION TO DETERMINE A NUMBER BETWEEN 0 AND TEN
*/
int CharacterMain::verify_number()
{
	do
	{
		cin >> choice;
		number = -1;
		try
		{
			choice = toupper(choice[0]);
			// EXTREME ANNOYANCE AND JUST TRYING TO MAKE THIS WORK
			if (choice == "A" || choice == "B" || choice == "C" || choice == "D" || choice == "E" || choice == "F" || choice == "G" || choice == "H" || choice == "I" || choice == "J" || choice == "K" || choice == "L" || choice == "M" || choice == "N" || choice == "P" || choice == "O" || choice == "Q" || choice == "R" || choice == "S" || choice == "T" || choice == "U" || choice == "W" || choice == "X" || choice == "Y" || choice == "Z")
			{
				throw choice;
			}
			else
			{
				number = stoi(choice);
			}
		}
		catch (string e)
		{
			cout << "AN INCORRECT ITEM WAS PLACED HERE\n";
		}
		if (number >= 0 && number <= TEN)
			break;
		cout << "SORRY, I DIDN'T CATCH THAT, WHAT DID YOU WANT?\n";
	} while (true);
	return number;
}
#pragma endregion

CharacterMain::~CharacterMain()
{
}
