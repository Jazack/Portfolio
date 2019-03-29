#include "Fight.h"
#pragma comment( lib, "winmm" )
#pragma once

using namespace std;

#pragma region INITIALIZERS
Fight::Fight()
{
}

Fight::Fight(int area, CharacterMain &player)
{
	srand(time(NULL));
	CharacterMain mainPlayer = player;
	switch (area)
	{
	case 0:
		FirstFight(mainPlayer);
	default:
		break;
	}
}

Fight::Fight(CharacterMain & player, MonsterMain & monster)
{
	srand(time(NULL));
	formation(player, monster);
	player.increaseXP(monster.getXP());
	player.increaseMoney(monster.getMoney());
}
#pragma endregion

#pragma region EXPLAINING HOW TO FIGHT
int Fight::FirstFight(CharacterMain &player)
{
	// set the monster variable to 0
	monsterVariable = 0;
	// create a monster item
	MonsterMain Doll("PRACTICE ILLUSION", 0, 0, 1, 4, 1, 1, 1, 1);
	FightSetup(player, Doll);
	cout << "\n\nNOW, NOTICE YOUR OPTIONS, YOU CAN ATTACK, ATTEMPT TO RUN, USE AN ITEM, OR TALK TO THE MONSTER";
	cout << "\nIF YOU ATTACK, YOU WILL RAISE ITS ANGER, MAKING IT LESS LIKELY TO TALK TO YOU, AND IF YOU RUN, IT";
	cout << "\nCAN CHASE AFTER YOU.  YOU CAN USE AN ITEM.  AND IF YOU TRY TO TALK TO IT, IT MAY OR MAY NOT TALK BACK.";
	cout << "DO YOU UNDERSTAND?(Y/N)\n";
	YesOrNo();
	Sleep(500);
	if (choice == NO)
	{
		cout << "WELL, THE BEST WAY FOR YOU TO LEARN IS BY PRACTICING!  FIRST JUST CHOOSE AN OPTION TO DO\nTRY TO ATTACK HIM. ";
	}
	cout << "GO AND CHOOSE WHAT YOU'LL DO\n";

	// call the function UserChoice
	UserChoice(player, Doll);
	
	// call the MonsterFight function
	MonsterFight(Doll, player, monsterVariable);

	MonsterAction(player, Doll);
	system("PAUSE");

	// call the function formation
	formation(player, Doll);

	return 0;
}
#pragma endregion

#pragma region Basic fight Formation

int Fight::formation(CharacterMain &character, MonsterMain &monster)
{
	const int FOUR = 4;
	// start monsterVariable at a random point
	monsterVariable = rand() % 2;
	// set talking_place to zero
	talking_place = zero;
	// set playerLife and monsterLife to their respective healths
	playerLife = character.getHP();
	monsterLife = monster.getHP();
	// start a do while loop for the battle
	do
	{	
		FightSetup(character, monster);
		
		// the the user input
		UserChoice(character, monster);

		// if the monster is now at zero life, kill it
		if (monster.getHP() <= zero)
		{
			// congratulate the player for winning
			cout << "CONGRATULATIONS! YOU WON!\n";
			// pause so that they can read it
			system("PAUSE");
			DisplayConquests(character, monster);
			// break
			break;
		}// end if

#pragma region Ifs for talking
		if (comparePlayer == INTIMIDATE_WORK || comparePlayer == DIPLOMACY_WORK || comparePlayer == BLUFF_WORK || comparePlayer == CHARM_WORK)
		{
			talking_place++;
			comparePlayer = zero;
		}
		else
		{
			talking_place--;
			comparePlayer = zero;
		}

		if (talking_place >= FOUR)
		{
			cout << "\nCONGRATULATIONS! YOU ENDED THE CONFLICT PEACEFULLY!  YOU HAVE A NEW FRIEND!\n";
			system("PAUSE");
			DisplayConquests(character, monster);
			break;
		}

		if (talking_place <= FAILURE)
		{
			talking_place = zero;
			compareMonster = monster.getStr();
			compareMonster = compareMonster * rand() % 5 + 1;
			character.HurtHP(compareMonster);
			cout << "THE MONSTER HATES YOU! IT DEALT " << compareMonster << " DAMAGE TO YOU!\n";
			system("PAUSE");
		}

#pragma endregion

		zero = 0;
		// break if comparePlayer equals 1
		if (comparePlayer == RUN_WORK)
		{
			// set comparePlayer to 0
			comparePlayer = zero;
			// break
			break;
		}// end if

		// call the monster fight function
		MonsterFight(monster, character, monsterVariable);
		// call the MonsterAction function
		MonsterAction(character, monster);

		//  break if either playerLife equals zero or monsterLife equals zero;
		if (character.getHP() <= zero)
		{
			cout << "SORRY BUT YOU LOST\n";
			character.setRegion(DEAD);
			system("PAUSE");
			break;
		}

		// IF THE MONSTER HAS ESCAPED, BREAK
		if (monsterChoice == RUNM)
		{
			cout << monster.getName() << " HAS ESCAPED\n";
			system("PAUSE");
			break;
		}

		// pause before restarting
		system("PAUSE");
		
	} while (true); // end while loop
	character.setHP(character.getTotalHP());

	// return 0
	getline(cin, choice);
	choice = toupper(choice[0]);
	return 0;
}// end function formation

void Fight::FightSetup(CharacterMain &character, MonsterMain &monster) {
	// clear the screen
	system("CLS");
	cout << "HP: ";
	playerInfo = character.getHP();
	cout << playerInfo;
	cout << "/";
	playerInfo = character.getTotalHP();
	cout << playerInfo;
	cout << "----XP: ";
	playerInfo = character.getXP();
	cout << playerInfo;
	cout << "------------------------------------ MONSTER NAME: ";
	monster.returnName();
	cout << "\nName: ";
	playerName = character.getName();
	cout << playerName;
	cout << "  ATTACK(A)   RUN(R)   ITEM(I)    TALK(T) ---------- HP: ";
	monster.returnHP();
	cout << "\n\n";
}
void Fight::Attack(CharacterMain & character, MonsterMain & monster)
{
	randomOne = rand() % TEN + 1;
	randomTwo = rand() % TEN + 1;
	if (randomOne == TEN)
		damage = monster.getStr() + randomOne * MULTIPLIER;
	else
		damage = monster.getStr() + randomOne;
	if (randomTwo == TEN)
		defense = character.getDEX() + randomTwo * MULTIPLIER;
	else
		defense = character.getDEX() + randomTwo;
}
#pragma endregion

#pragma region Choices for the player

int Fight::UserChoice(CharacterMain &character, MonsterMain &monster)
{
	// set comparePlayer to 0
	comparePlayer = 0;
	cin >> choice;
	choice = toupper(choice[0]);
	// set firstChoice to choice for the monsters fight function
	firstChoice = choice;

	if (choice != ATTACK && choice != RUN && choice != ITEM && choice != TALK)
	{
		do
		{
			cout << "WAIT, WHAT SHOULD I DO AGAIN?\n";
			cin >> choice;
			choice = toupper(choice[0]);
			// set firstChoice to choice for the monsters fight function
			firstChoice = choice;
		} while (choice != ATTACK && choice != RUN && choice != ITEM && choice != TALK);

	}
	if (choice == ATTACK)
	{
		KillEmAll(character, monster);
	}
	if (choice == RUN)
	{
		RunAway(character, monster);
	}
	if (choice == ITEM)
	{
		Item(character, monster);
	}
	if (choice == TALK)
	{
		Talk(character, monster);
	}
	return 0;
}

#pragma endregion

#pragma region Options

#pragma region Fight Sequence

int Fight::KillEmAll(CharacterMain &character, MonsterMain &monster)
{
	damage = character.getSTR();
	int randomOne = rand() % CRIT;
	int randomTwo = rand() % 4 + 1;
	// if randomOne = 4, set damage to be equal to damage * multiplier * randomOne
	if (randomOne == CRIT)
	{
		damage = damage + (MULTIPLIER * randomOne);
	}
	// else just multiply damage by randomOne
	else
	{
		damage = damage + randomOne;
	}
	// set the defense of the monster to the con and randomTwo
	int defense = monster.getCon() + randomTwo;

	// if damage is greater than or equal to defense
	if (damage >= defense)
	{
		// take the damage and take out the defense
		damage = damage - defense;
		// change the hp of the monster
		monster.setHP(damage);
		// comment how much they hurt the monster
		cout << "\nYOU HURT THE MONSTER " << damage << "\n";
	}
	else
	{
		// tell the player that ______ defended against them
		cout << "\nTHE " << monster.getName() << " DEFENDED AGAINST YOUR ATTACK!\n";
	}

	// return 0
	return 0;
}
#pragma endregion

#pragma region Run
/// a method to see if the player can run away from the monster
int Fight::RunAway(CharacterMain &character, MonsterMain &monster)
{
	// get the players dex and monsters str
	randomOne = rand() % CRIT;
	randomTwo = rand() % 5;
	comparePlayer = character.getDEX() + randomOne;
	compareMonster = monster.getStr() + randomTwo;
	// compare them
	if (comparePlayer >= compareMonster)
	{
		// if the player is higher, set comparePlayer to 1
		comparePlayer = RUN_WORK;
		// say congratulations
		cout << "CONGRATULATIONS! YOU ESCAPE!\n";
	}
	// else set comparePlayer to 0
	else
	{
		comparePlayer = 0;
		// let them know that they failed
		cout << "IN ATTEMPTING TO ESCAPE, THE MONSTER HAS CORNERED YOU!  YOU ARE NOW GOING TO BE ATTACKED!";
	}

	// return 0
	return 0;
}// end method
#pragma endregion

#pragma region Items
/// a function to get items
int Fight::Item(CharacterMain &character, MonsterMain &monster)
{
	// clear the screen
	system("CLS");
	// goto the Retrieve_Items function
	item_choice = character.Retrieve_Items();
#pragma region ITEM EFFECTS

#pragma region super potion
	if (item_choice == SUPER_POTION)
	{
		if (character.getHP() < character.getTotalHP())
		{
			character.setHP(character.getHP() + TEN + TEN);
			if (character.getHP() > character.getTotalHP())
				character.setHP(character.getTotalHP());
			cout << "YOU DRINK THE SUPER POTION, IT RESTORES SOME HP\n";
		}
		else
		{
			cout << "YOU DRINK THE SUPER POTION, YET YOU ALREADY HAVE FULL LIFE\n";
		}
		// ATTACK PART
#pragma region ATTACK PART OF THE POTION
		damage = character.getSTR() + TWO;
		int randomOne = rand() % CRIT + SIX;
		int randomTwo = rand() % FOUR + 1;
		// if randomOne = 4, set damage to be equal to damage * multiplier * randomOne
		if (randomOne >= CRIT + FOUR)
		{
			damage = damage + (MULTIPLIER * randomOne);
		}
		// else just multiply damage by randomOne
		else
		{
			damage = damage + randomOne;
		}
		// set the defense of the monster to the con and randomTwo
		int defense = monster.getCon() + randomTwo;

		// if damage is greater than or equal to defense
		if (damage > defense)
		{
			// take the damage and take out the defense
			damage = damage - defense;
			// change the hp of the monster
			monster.setHP(damage);
			// comment how much they hurt the monster
			cout << "\nYOU ARE EVEN STRONGER FROM THE SUPER POTION, YOU HURT THE MONSTER " << damage << "\n";
		}
		else
		{
			// tell the player that ______ defended against them
			cout << monster.getName() << " DEFENDED AGAINST YOUR ATTACK!\n";
		}
#pragma endregion
	}
#pragma endregion

#pragma region HEALTH POTION

	if (item_choice == HEALTH_POTION)
	{
		if (character.getHP() < character.getTotalHP())
		{
			character.setHP(character.getHP() + TEN + TEN);
			if (character.getHP() > character.getTotalHP())
				character.setHP(character.getTotalHP());
			cout << "YOU DRINK A HEALTH POTION, IT RESTORES SOME HP\n";
		}
		else
		{
			cout << "YOU DRINK A HEALTH POTION, YET YOU ALREADY HAVE FULL LIFE\n";
		}
	}
#pragma endregion

#pragma region ATTACK POTION
	if (item_choice == ATTACK_POTION)
	{
		damage = character.getSTR();
		int randomOne = rand() % CRIT + TEN;
		int randomTwo = rand() % FOUR + 1;
		// if randomOne = 4, set damage to be equal to damage * multiplier * randomOne
		if (randomOne >= CRIT + SIX)
		{
			damage = damage + (MULTIPLIER * randomOne);
		}
		// else just multiply damage by randomOne
		else
		{
			damage = damage + randomOne;
		}
		// set the defense of the monster to the con and randomTwo
		int defense = monster.getCon() + randomTwo;

		// if damage is greater than or equal to defense
		if (damage >= defense)
		{
			// take the damage and take out the defense
			damage = damage - defense;
			// change the hp of the monster
			monster.setHP(damage);
			// comment how much they hurt the monster
			cout << "\nYOU HURT THE MONSTER " << damage << "\n";
		}
		else
		{
			// tell the player that ______ defended against them
			cout << "\nTHE " << monster.getName() << " DEFENDED AGAINST YOUR ATTACK!\n";
		}
	}
#pragma endregion

#pragma region XP MULTIPLIER (INCREASER)
	if (item_choice == XP_MULTIPLIER)
	{
		monster.increaseXP(TEN);
	}
#pragma endregion

#pragma region ESCAPE
	if (item_choice == ESCAPE)
	{
		comparePlayer = RUN_WORK;
	}
#pragma endregion

#pragma endregion

	// pause
	system("PAUSE");
	// return 0
	return 0;
}

#pragma endregion

#pragma region Talk
int Fight::Talk(CharacterMain &character, MonsterMain &monster)
{
	// clear the screen
	system("CLS");
	// present the options
	cout << "INTIMIDATE (I) DIPLOMACY (D)   BLUFF (B)   CHARM (C) STOP (S) (WILL SKIP TURN)\n";
	// ALLOW USER INPUT
	cin >> choice;
	// RAISE IT TO UPPERCASE AND THE FIRST LETTER
	choice = toupper(choice[0]);
	// verify that it works
	if (choice != INTIMIDATE && choice != DIPLOMACY && choice != BLUFF && choice != CHARM && choice != STOP)
	{
		// GO INTO A LOOP UNTIL A PROPER ENTRY IS PUT IN
		do
		{
			cout << "WHAT WAS THAT?\n";
			cin >> choice;
			choice = toupper(choice[0]);
		} while (choice != INTIMIDATE && choice != DIPLOMACY && choice != BLUFF && choice != CHARM && choice != STOP);
	}
	// IF DIPLOMACY IS USED, COMPARE int to wis
	if (choice == DIPLOMACY)
	{
		comparePlayer = character.getInt();
		compareMonster = monster.getWis();
		randomOne = rand() % CRIT + 1;
		randomTwo = rand() % CRIT + 1;
		if (randomOne == CRIT)
		{
			comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
		}
		else
		{
			comparePlayer = comparePlayer + randomOne;
		}

		// multiply compareMonster by it's multiplier
		if (randomTwo == CRIT)
		{
			compareMonster = compareMonster + (randomTwo * MULTIPLIER);
		}
		else
		{
			compareMonster = compareMonster + randomTwo;
		}

		// verify which is greater
		if (comparePlayer >= compareMonster)
		{
			cout << "\nCONGRATULATIONS! YOU HAD A NICE DISCUSSION WITH THE ";
			cout << monster.getName();
			comparePlayer = DIPLOMACY_WORK;
			worked = 1;
			cout << "\n";
		}
		else
		{
			cout << "\nALAS, YOUR ATTEMPTS TO CONVERSE WITH HIM FAILED, ";
			cout << monster.getName();
			cout << " WILL STRIKE BACK";
			comparePlayer = DIPLOMACY_NOT_WORK;
			worked = 0;
			cout << "\n";
		}
	}
	
	// IF INTIMIDATE IS USED, COMPARTE STR TO STR
	if (choice == INTIMIDATE)
	{
		comparePlayer = character.getSTR();
		compareMonster = monster.getStr();
		randomOne = rand() % CRIT;
		randomTwo = rand() % CRIT;
		if (randomOne == CRIT)
		{
			comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
		}
		else
		{
			comparePlayer = comparePlayer + randomOne;
		}

		// multiply compareMonster by it's multiplier
		if (randomTwo == CRIT)
		{
			compareMonster = compareMonster + (randomTwo * MULTIPLIER);
		}
		else
		{
			compareMonster = compareMonster + randomTwo;
		}

		// verify which is greater
		if (comparePlayer >= compareMonster)
		{
			cout << "\nYOU HAVE PROVEN YOURSELF TO BE GREATER THAN YOUR ENEMY";
			comparePlayer = INTIMIDATE_WORK;
			worked = 1;
			cout << "\n";
		}
		else
		{
			cout << "YOU COULD NOT MAKE YOUR OPPONENT COWER IN FEAR";
			comparePlayer = INTIMIDATE_NOT_WORK;
			worked = 0;
			cout << "\n";
		}
	}
	
	// IF BLUFF IS USED
	if (choice == BLUFF)
	{
		comparePlayer = character.getWis();
		compareMonster = monster.getIntell();
		randomOne = rand() % CRIT;
		randomTwo = rand() % CRIT;
		if (randomOne == CRIT)
		{
			comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
		}
		else
		{
			comparePlayer = comparePlayer + randomOne;
		}

		// multiply compareMonster by it's multiplier
		if (randomTwo == CRIT)
		{
			compareMonster = compareMonster + (randomTwo * MULTIPLIER);
		}
		else
		{
			compareMonster = compareMonster + randomTwo;
		}

		// verify which is greater
		if (comparePlayer >= compareMonster)
		{
			cout << "\nYOU HAVE LIED TO THE ENEMY, HE BELIEVES\n";
			comparePlayer = BLUFF_WORK;
			worked = 1;
			cout << "\n";
		}
		else
		{
			cout << "\nWHY WOULD YOU LIE TO THE ENEMY!?!?!\n";
			comparePlayer = BLUFF_NOT_WORK;
			worked = 0;
			cout << "\n";
		}
	}

	// IF CHARM IS USED
	if (choice == CHARM)
	{
		comparePlayer = character.getCharisma();
		compareMonster = monster.getCon();
		randomOne = rand() % CRIT;
		randomTwo = rand() % CRIT;
		if (randomOne == CRIT)
		{
			comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
		}
		else
		{
			comparePlayer = comparePlayer + randomOne;
		}

		// multiply compareMonster by it's multiplier
		if (randomTwo == CRIT)
		{
			compareMonster = compareMonster + (randomTwo * MULTIPLIER);
		}
		else
		{
			compareMonster = compareMonster + randomTwo;
		}

		// verify which is greater
		if (comparePlayer >= compareMonster)
		{
			cout << "\nYOU HAVE MADE YOUR ENEMY LIKE YOU\n";
			comparePlayer = CHARM_WORK;
			worked = 1;
			cout << "\n";
		}
		else
		{
			cout << "\nTHE ENEMY IS DISGUSTED AT YOUR ADVANCES\n";
			comparePlayer = CHARM_NOT_WORK;
			worked = 0;
			cout << "\n";
		}
	}
	// if stop is used

	return 0;
}
#pragma endregion

#pragma endregion

int Fight::YesOrNo()
{
	cin >> choice;
	choice = toupper(choice[0]);
	if (choice != YES && choice != NO)
	{
		do
		{
			cout << "SORRY, I DIDN'T HEAR YOU, WHAT WAS THAT?\n";
			cin >> choice;
			choice = toupper(choice[0]);
		} while (choice != YES && choice != NO);
	}
	return 0;
}

#pragma region Monster controlls

#pragma region Fight Basic AI

int Fight::MonsterFight(MonsterMain &monster, CharacterMain &character, int &part)
{
	// Constants for the monster to fight
	const int RUNM = 1;
	const int FIGHTM = 2;
	const int DOUBLEDMGM = 3;
	const int DMGDISM = 4;
	const int ADVM = 5;
	const int NOTURNM = 6;
	const int TWOATTACKSM = 7;
	const int TALKM = 8;
	const int SIXDMG = 9;

#pragma region Variable 0

	// if following pattern 0
	if (part == 0)
	{
		
		do
		{
			// CHECK IF THE PLAYER ATTACKED
			if (firstChoice == ATTACK)
			{
				// CHECK THE MONSTERS HP
				if (monster.getHP() <= monster.getEighth())
				{
					// have the monster run
					monsterChoice = RUNM;
					break;
				}
				else
				{
					// else have him fight
					monsterChoice = FIGHTM;
					break;
				}
				
			}

			// IF THE PLAYER TALKED
			if (firstChoice == TALK)
			{
				if (choice == INTIMIDATE)
				{
					if (worked == 1)
					{
						// have the monster run
						monsterChoice = RUNM;
					}
					else
					{
						// have the monster fight
						monsterChoice = FIGHTM;
					}

					// break
					break;

				}
				if (choice == BLUFF)
				{
					if (worked == 1)
					{
						// have the monster do damage at disadvantage
						monsterChoice = DMGDISM;
					}
					else
					{
						// have the monster do double damage
						monsterChoice = DOUBLEDMGM;
					}

					// break
					break;
				}
				if (choice == CHARM)
				{
					if (worked == 1)
					{
						// SKIP THE TURN
						monsterChoice = NOTURNM;
					}
					else
					{
						// ATTACK TWICE
						monsterChoice = TWOATTACKSM;
					}

					// break
					break;
				}
				if (choice == DIPLOMACY)
				{
					if (worked == 1)
					{
						// TALK TO THE PLAYER
						monsterChoice = TALKM;
					}
					else
					{
						// DO SIX EXTRA DAMAGE
						monsterChoice = SIXDMG;
					}

					// break
					break;
				}
			}

			// IF THE PLAYER RUNS
			if (firstChoice == RUN)
			{
				// fight the player
				monsterChoice = FIGHTM;
				// break
				break;
			}

			// IF THE PLAYER USES AN ITEM
			if (firstChoice == ITEM)
			{
				// FIGHT THE PLAYER
				monsterChoice = FIGHTM;
				// BREAK
				break;
			}
		} while (true);
		
	}
#pragma endregion

#pragma region Variable 1

	// if monster is following pattern 1
	if (part == 1)
	{
		do
		{
			// CHECK IF THE PLAYER ATTACKED
			if (firstChoice == ATTACK)
			{
				randomOne = rand() % 3;
				// CHECK THE MONSTERS HP
				if (monster.getHP() <= monster.getEighth() && randomOne == 0)
				{
					// have the monster run
					monsterChoice = RUNM;
					break;
				}

				if (randomOne == 0)
				{
					monsterChoice = FIGHTM;
					break;
				}

				if (randomOne == 1)
				{
					monsterChoice = DOUBLEDMGM;
					break;
				}

				if (randomOne == TWO)
				{
					monsterChoice = SIXDMG;
					break;
				}

				if (randomOne == THREE)
				{
					monsterChoice = DMGDISM;
					break;
				}
				// if somehow they can get through all of this without breaking out, have the monster just fight and break
				monsterChoice = FIGHTM;
				break;
			}
#pragma region Talk

			// IF THE PLAYER TALKED
			if (firstChoice == TALK)
			{
				if (choice == INTIMIDATE)
				{
					if (worked == 1)
					{
						randomOne = rand() % 2;
						
						if (randomOne == 0)
						{
							// have the monster run
							monsterChoice = RUNM;
							break;
						}

						if (randomOne == 1)
						{
							// have the monster fight
							monsterChoice = FIGHTM;
							break;
						}

						if (randomOne == TWO)
						{
							// have the monster fight at disadvantage
							monsterChoice = DMGDISM;
							break;
						}
						// have the monster run
						monsterChoice = RUNM;
						break;
					}
					else
					{
						// have the monster fight
						monsterChoice = FIGHTM;
					}

					// break
					break;

				}
				if (choice == BLUFF)
				{
					if (worked == 1)
					{
						// No turn
						monsterChoice = NOTURNM;
					}
					else
					{
						// have the monster do double damage
						monsterChoice = DOUBLEDMGM;
					}

					// break
					break;
				}
				if (choice == CHARM)
				{
					if (worked == 1)
					{
						// Dis adavantage
						monsterChoice = DMGDISM;
					}
					else
					{
						// ATTACK TWICE
						monsterChoice = TWOATTACKSM;
					}

					// break
					break;
				}
				if (choice == DIPLOMACY)
				{
					if (worked == 1)
					{
						// TALK TO THE PLAYER
						monsterChoice = TALKM;
					}
					else
					{
						randomOne = rand() % TWO;
						if (randomOne == 0)
						{
							// do six extra damage
							monsterChoice = SIXDMG;
							break;
						}
						if (randomOne == 1)
						{
							// have monster do two attacks
							monsterChoice = TWOATTACKSM;
							break;
						}
						if (randomOne == TWO)
						{
							// have the monster do a normal attack
							monsterChoice = FIGHTM;
							break;
						}
						// DO SIX EXTRA DAMAGE if the monster hasn't gotten it's choice
						monsterChoice = SIXDMG;
						break;
					}

					// break
					break;
				}
			}

#pragma endregion
			// IF THE PLAYER RUNS
			if (firstChoice == RUN)
			{
				// fight the player
				monsterChoice = ADVM;
				// break
				break;
			}

			// IF THE PLAYER USES AN ITEM
			if (firstChoice == ITEM)
			{
				randomOne = rand() % TWO;
				if (randomOne == 0)
				{
					// have the monster talk
					monsterChoice = TALKM;
					// break
					break;
				}

				if (randomOne == 1)
				{
					// have the monster fight
					monsterChoice = FIGHTM;
					// break
					break;
				}

				if (randomOne == TWO)
				{
					// do disadavantage damage
					monsterChoice = DMGDISM;
					// break
					break;
				}
				// FIGHT THE PLAYER if somehow none of those worked
				monsterChoice = FIGHTM;
				// BREAK
				break;
			}// end of if firstChoice == items
		} while (true);
		// make monsterVariable one less so that the other style is played next
		
	}

	if (part == 1)
	{
		part--;
	}
	else
	{
		part++;
	}

#pragma endregion
	// return 0
	return 0;
}
#pragma endregion

#pragma region ACTIONS

int Fight::MonsterAction(CharacterMain &character, MonsterMain &monster)
{
	// initialize constants
	const int RUNM = 1;
	const int FIGHTM = 2;
	const int DOUBLEDMGM = 3;
	const int DMGDISM = 4;
	const int ADVM = 5;
	const int NOTURNM = 6;
	const int TWOATTACKSM = 7;
	const int TALKM = 8;
	const int SIXDMG = 9;

	switch (monsterChoice)
	{
	case RUNM:
#pragma region RUN
		randomOne = rand() % CRIT;
		randomTwo = rand() % 8;
		compareMonster = monster.getDex() + randomTwo;
		comparePlayer = character.getDEX() + randomOne;
		if (compareMonster >= comparePlayer)
		{
			monsterChoice = RUNM;
		}
		else
		{
			monsterChoice = 0;
		}

#pragma endregion
		break;

	case FIGHTM:
#pragma region FIGHT
		randomOne = rand() % 5;
		randomTwo = rand() % CRIT;
		damage = monster.getStr() + randomTwo;
		defense = character.getCon() + randomOne;
		if (damage >= defense)
		{
			// calculate the total damage
			damage = damage - defense;
			// hurt the player
			character.HurtHP(damage);
			cout << "\nYOU TOOK " << damage << " DAMAGE\n";

		}
		else
		{
			cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
		}

#pragma endregion
		break;

	case DOUBLEDMGM:
#pragma region DOUBLE Damage

		randomOne = rand() % 5;
		randomTwo = rand() % CRIT;
		damage = (monster.getStr() + randomTwo) * 2;
		defense = character.getCon() + randomOne;
		if (damage >= defense)
		{
			// calculate the total damage
			damage = damage - defense;
			// hurt the player
			character.HurtHP(damage);
			cout << monster.getName() << " HURT YOU " << damage;

		}
		else
		{
			cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
		}
#pragma endregion
		break;

	case DMGDISM:
#pragma region DISADVANTAGE

		randomOne = rand() % CRIT;
		randomTwo = rand() % CRIT;
		if (randomOne <= randomTwo)
		{
			randomTwo = rand() % 5;
			damage = monster.getStr() + randomOne;
			defense = character.getCon() + randomTwo;
			if (damage >= defense)
			{
				// calculate the total damage
				damage = damage - defense;
				// hurt the player
				character.HurtHP(damage);
				cout << monster.getName() << " HURT YOU " << damage;

			}
			else
			{
				cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
			}
		}
		else
		{
			randomOne = rand() % 5;
			damage = monster.getStr() + randomTwo;
			defense = character.getCon() + randomOne;
			if (damage >= defense)
			{
				// calculate the total damage
				damage = damage - defense;
				// hurt the player
				character.HurtHP(damage);
				cout << monster.getName() << " HURT YOU " << damage;

			}
			else
			{
				cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
			}
		}

#pragma endregion
		break;

	case ADVM:
#pragma region ADVANTAGE
		randomOne = rand() % CRIT;
		randomTwo = rand() % CRIT;
		if (randomOne <= randomTwo)
		{
			randomOne = rand() % 5;
			damage = monster.getStr() + randomTwo;
			defense = character.getCon() + randomOne;
			if (damage >= defense)
			{
				// calculate the total damage
				damage = damage - defense;
				// hurt the player
				character.HurtHP(damage);
				cout << monster.getName() << " HURT YOU " << damage;

			}
			else
			{
				cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
			}
		}
		else
		{
			randomTwo = rand() % 5;
			damage = monster.getStr() + randomOne;
			defense = character.getCon() + randomTwo;
			if (damage >= defense)
			{
				// calculate the total damage
				damage = damage - defense;
				// hurt the player
				character.HurtHP(damage);
				cout << monster.getName() << " HURT YOU " << damage;

			}
			else
			{
				cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
			}
		}
#pragma endregion
		break;

	case NOTURNM:
		// do nothing so that the monster has no turn
		break;

	case TWOATTACKSM:
#pragma region TWO ATTACKS
		// the code from FIGHTM twice
		randomOne = rand() % 5;
		randomTwo = rand() % CRIT;
		damage = monster.getStr() + randomTwo;
		defense = character.getCon() + randomOne;
		if (damage >= defense)
		{
			// calculate the total damage
			damage = damage - defense;
			// hurt the player
			character.HurtHP(damage);
			cout << "\nYOU TOOK " << damage << " DAMAGE\n";

		}
		else
		{
			cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
		}
		// second part of the turn
		randomOne = rand() % 5;
		randomTwo = rand() % CRIT;
		damage = monster.getStr() + randomTwo;
		defense = character.getCon() + randomOne;
		if (damage >= defense)
		{
			// calculate the total damage
			damage = damage - defense;
			// hurt the player
			character.HurtHP(damage);
			cout << "\nYOU TOOK " << damage << " DAMAGE ON HIS SECOND ATTACK!\n";
		}
		else
		{
			cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S SECOND ATTACK!\n";
		}
#pragma endregion
		break;

	case TALKM:
#pragma region TALKING
		randomOne = rand() % 8;
		randomTwo = rand() % CRIT;
		compareMonster = monster.getCharisma() + randomTwo;
		comparePlayer = character.getInt() + randomOne;
		// verify which is higher
		if (compareMonster >= comparePlayer)
		{
			// if compareMonster is greater, subtract one from talking_place
			talking_place--;
			cout << "\nTHE MONSTER GROWLS AT YOU, IT'S FRIGHTENING (DON'T BE FRIGHTENED)\n";
		}
		else
		{
		    // increase talking_place by one
			talking_place++;
			cout << "\nTHE MONSTER ATTEMPTS TO GROWL AT YOU, BUT INSTEAD TRIPS\n";
		}
#pragma endregion
		break;

	case SIXDMG:
#pragma region PLUS SIX DAMAGE
		// the code from FIGHTM WITH AN ADDED SIX
		randomOne = rand() % 5;
		randomTwo = rand() % CRIT;
		damage = monster.getStr() + randomTwo + 6;
		defense = character.getCon() + randomOne;
		if (damage >= defense)
		{
			// calculate the total damage
			damage = damage - defense;
			// hurt the player
			character.HurtHP(damage);
			cout << "\nYOU TOOK " << damage << " DAMAGE\n";

		}
		else
		{
			cout << "\nYOU DEFENDED AGAINST " << monster.getName() << "'S ATTACK!\n";
		}
#pragma endregion

		break;

	default:
		break;
	}

	return 0;
}

#pragma endregion

#pragma endregion

#pragma region Victory parts

void Fight::DisplayConquests(CharacterMain & player, MonsterMain & monster)
{
	// clear
	system("CLS");

	cout << "CONGRATULATIONS!  YOU WON!  NOW YOU GET " << monster.getXP() << "XP AND " << monster.getMoney() << " PIECES OF CURRENCY\n";

	player.increaseMoney(monster.getMoney());
	player.increaseXP(monster.getXP());
	system("PAUSE");
}

#pragma endregion

#pragma region Donovos fight
#pragma region Donovo Fight set up
void Fight::DonovoFight(CharacterMain & character, int strenth_mod, int charisma_mod, int diplomacy_mod)
{
	// form donovo
	// make him stronger in strength if alice is dead
	if (character.get_alice_situation() == 0)
		strength_modifier = 2;
	else
		strength_modifier = 0;
	if (character.get_daniel_situation() == 0)
		dexterity_modifier = 2;
	else
		dexterity_modifier = 0;
	if (character.get_barimus_situation() == 0)
		diplomacy_modifier = 2;
	else
		diplomacy_modifier = 0;

	MonsterMain donovo = MonsterMain("DONOVO", 250, 150, 6 + strength_modifier, 8, 6 + dexterity_modifier, 7 + diplomacy_modifier, 6, 8);
	const int FOUR = 4;
	const int SIX = 6;
	// start monsterVariable at a random point
	monsterVariable = rand() % 2;
	// set talking_place to zero
	talking_place = zero;
	// set playerLife and monsterLife to their respective healths
	playerLife = character.getHP();
	monsterLife = donovo.getHP();
	// part tells you which ai track to follow
	part = rand() % 2;

	// start a do while loop for the battle
	do
	{
		FightSetup(character, donovo);

		// the the user input
		UserChoice(character, donovo, strenth_mod, charisma_mod, diplomacy_mod);

		// if the monster is now at zero life, kill it
		if (donovo.getHP() <= zero)
		{
			// congratulate the player for winning
			cout << "CONGRATULATIONS! YOU WON!\n";
			character.set_donovo_situation(0);
			// pause so that they can read it
			system("PAUSE");
			DisplayConquests(character, donovo);
			// break
			break;
		}// end if

#pragma region Ifs for talking
		if (comparePlayer == INTIMIDATE_WORK || comparePlayer == DIPLOMACY_WORK || comparePlayer == BLUFF_WORK || comparePlayer == CHARM_WORK)
		{
			talking_place++;
			comparePlayer = zero;
		}
		else
		{
			talking_place--;
			comparePlayer = zero;
		}

		if (talking_place >= SIX)
		{
			cout << "\nCONGRATULATIONS! YOU ENDED THE CONFLICT PEACEFULLY!  YOU HAVE A NEW FRIEND!\n";
			system("PAUSE");
			DisplayConquests(character, donovo);
			character.set_donovo_situation(TWO);
			break;
		}

		if (talking_place <= FAILURE)
		{
			talking_place = zero;
			compareMonster = donovo.getStr();
			compareMonster = compareMonster * rand() % 5 + 1;
			character.HurtHP(compareMonster);
			cout << "THE MONSTER HATES YOU! IT DEALT " << compareMonster << " DAMAGE TO YOU!\n";
			system("PAUSE");
		}

#pragma endregion

		zero = 0;
		// break if comparePlayer equals 1
		if (comparePlayer == RUN_WORK)
		{
			// set comparePlayer to 0
			comparePlayer = zero;
			// break
			break;
		}// end if

		 // call the monster fight function
		DonovoAI(donovo, character, strenth_mod, charisma_mod, diplomacy_mod);
		MonsterFight(donovo, character, monsterVariable);
		// call the MonsterAction function
		MonsterAction(character, donovo);

		//  break if either playerLife equals zero or monsterLife equals zero;
		if (character.getHP() <= zero)
		{
			cout << "SORRY BUT YOU LOST\n";
			character.setRegion(DEAD);
			system("PAUSE");
			break;
		}

		// IF THE MONSTER HAS ESCAPED, BREAK
		if (monsterChoice == RUNM)
		{
			cout << donovo.getName() << " HAS ESCAPED\n";
			system("PAUSE");
			break;
		}

		// pause before restarting
		system("PAUSE");

	} while (true); // end while loop
	character.setHP(character.getTotalHP());
}
#pragma endregion
#pragma region Donovo AI

int Fight::DonovoAI(MonsterMain & donovo, CharacterMain & player, int strenth_mod, int charisma_mod, int diplomacy_mod)
{
	// Constants for the monster to fight
	// here run is heal
	const int RUNM = 1;
	const int FIGHTM = 2;
	// this is crying / skip turn
	const int DOUBLEDMGM = 3;
	const int DMGDISM = 4;
	const int ADVM = 5;
	const int NOTURNM = 6;
	const int TWOATTACKSM = 7;
	const int TALKM = 8;
	const int SIXDMG = 9;

	do
	{
#pragma region 1/4 HP?
		if (donovo.getHP() < donovo.getTotalHP() * FOURTH)
		{
			if (health_potions > 0)
			{
				monsterChoice = HEALM;
			}
			fealings = donovo_fell_good(donovo);
			if (fealings == 1)
			{
				monsterChoice = CRYM;
				break;
			}
			else
			{
				monsterChoice = FIGHTM;
				break;
			}
		}
#pragma endregion
#pragma region attacked me? / scary?
		if (firstChoice == ATTACK || choice == INTIMIDATE)
		{
			fealings = donovo_fell_good(donovo);
			if (fealings == 1)
			{
				monsterChoice = CRYM;
				break;
			}
			else
			{
				monsterChoice = FIGHTM;
				break;
			}
		}
#pragma endregion
#pragma region if Donovo likes you
		if (talking_place == THREE)
		{
			randomOne = rand() % THREE + 1;
			if (comparePlayer == BLUFF_WORK || comparePlayer == DIPLOMACY_WORK)
			{
				monsterChoice = DIPLOMACYM;
				break;
			}
			if (comparePlayer == CHARM_WORK)
			{
				monsterChoice == CHARMM;
				break;
			}
			// now for if he's not being nice
			fealings = donovo_fell_good(donovo);
			if (fealings == 1)
			{
				monsterChoice = CRYM;
				break;
			}
			if (comparePlayer == BLUFF_NOT_WORK)
			{
				if (randomOne == 1)
					monsterChoice = BLUFFM;
				if (randomOne == TWO)
					monsterChoice = FIGHTM;
				if (randomOne == THREE)
					monsterChoice = HEALM;
				break;
			}
			if (comparePlayer == CHARM_NOT_WORK)
			{
				if (randomOne == 1)
					monsterChoice = DOUBLEDMGM;
				if (randomOne == TWO)
					monsterChoice = FIGHTM;
				if (randomOne == THREE)
					monsterChoice = BLUFFM;
				break;
			}
			if (comparePlayer == DIPLOMACY_NOT_WORK)
			{
				if (randomOne == 1)
					monsterChoice = BLUFFM;
				if (randomOne == TWO)
					monsterChoice = DOUBLEDMGM;
				if (randomOne == THREE)
					monsterChoice = HEALM;
				break;
			}
		}
#pragma endregion
#pragma region If donovo doesnt like you
		else
		{
			fealings = donovo_fell_good(donovo);
			if (fealings == 1)
			{
				monsterChoice = CRYM;
				break;
			}
			
			randomOne = rand() % THREE + 1;
			
			if (comparePlayer == BLUFF_WORK || comparePlayer == DIPLOMACY_WORK || comparePlayer == CHARM_WORK)
			{
				monsterChoice = DIPLOMACYM;
				break;
			}
			
			if (player.getHP() < player.getTotalHP() * FOURTH)
			{
				monsterChoice = BLUFFM;
				break;
			}
			else
			{
				monsterChoice = FIGHTM;
				break;
			}
		}
#pragma endregion
		// in case it's not working right, let him just fight and break
		monsterChoice = FIGHTM;
		break;
	} while (true);
	// return 0
	return monsterChoice;
}

#pragma endregion
#pragma region Donovo Actions
int Fight::donovo_Action(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod, int donovoChoice)
{
	// constants for the switch
#pragma region constants
	const int FIGHTM = 2;
	const int DOUBLEDMGM = 3;
	const int CHARMM = 10;
	const int DIPLOMACYM = 11;
	const int BLUFFM = 12;
	const int HEALM = 13;
	const int CRYM = 14;
#pragma endregion

	switch (monsterChoice)
	{
	case HEALM:
		randomOne = rand() % TEN + 1;
		monster.changeHP(-CRIT - randomOne);
		break;
	case DOUBLEDMGM:
#pragma region two fight sequences
		Attack(character, monster);
		if (damage > defense)
		{
			damage = damage - defense;
			character.setHP(character.getHP() - damage);
			cout << "YOU HAVE TAKEN " << damage << " DAMAGE\n";
			Sleep(1000);
		}
		else
		{
			cout << "YOU HAVE DEFENDED YOURSELF FROM DONOVO'S FIRST ATTACK\n";
			Sleep(1000);
		}
		// SECOND ATTACK
		Attack(character, monster);
		if (damage > defense)
		{
			damage = damage - defense;
			character.setHP(character.getHP() - damage);
			cout << "YOU HAVE TAKEN " << damage << " DAMAGE IN DONOVO'S SECOND ATTACK\n";
			system("PAUSE");
		}
		else
		{
			cout << "YOU HAVE DEFENDED YOURSELF FROM DONOVO'S SECOND ATTACK\n";
			system("PAUSE");
		}
#pragma endregion
		break;
	case FIGHTM:
#pragma region FIGHT SEQUENCE
		Attack(character, monster);
		if (damage > defense)
		{
			damage = damage - defense;
			character.setHP(character.getHP() - damage);
			cout << "YOU HAVE TAKEN " << damage << " DAMAGE\n";
			system("PAUSE");
		}
		else
		{
			cout << "YOU HAVE DEFENDED YOURSELF FROM DONOVO'S ATTACK\n";
			system("PAUSE");
		}
#pragma endregion
		break;
	case CHARMM:
#pragma region CHARM
		compareMonster= monster.getCharisma();
		comparePlayer = character.getCon();
		randomOne = rand() % CRIT;
		randomTwo = rand() % CRIT;
		if (randomOne == CRIT)
		{
			compareMonster = compareMonster + (randomOne * MULTIPLIER);
		}
		else
		{
			compareMonster = compareMonster + randomOne;
		}

		// multiply compareMonster by it's multiplier
		if (randomTwo == CRIT)
		{
			comparePlayer = comparePlayer + (randomTwo * MULTIPLIER);
		}
		else
		{
			comparePlayer = comparePlayer + randomTwo;
		}

		// verify which is greater
		if (comparePlayer < compareMonster)
		{
			cout << "DONOVO BEGANS TO FLATTER YOU/n";
			talking_place--;
		}
		else
		{
			cout << "IS DONOVO TRYING TO CHARM ME?\n";
			talking_place++;
		}
		break;
#pragma endregion
	case DIPLOMACYM:
#pragma region DIPLOMACY
		comparePlayer = character.getWis();
		compareMonster = monster.getIntell();
		randomOne = rand() % CRIT + 1;
		randomTwo = rand() % CRIT + 1;
		if (randomOne == CRIT)
		{
			comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
		}
		else
		{
			comparePlayer = comparePlayer + randomOne;
		}

		// multiply compareMonster by it's multiplier
		if (randomTwo == CRIT)
		{
			compareMonster = compareMonster + (randomTwo * MULTIPLIER);
		}
		else
		{
			compareMonster = compareMonster + randomTwo;
		}

		// verify which is greater
		if (comparePlayer < compareMonster)
		{
			cout << "\nMAYBE LEAVING HIM ALONE IS THE BEST OPTION?\n";
			talking_place--;
			system("PAUSE");
		}
		else
		{
			cout << "\nHE ATTEMPTS TO TALKS, BUT BEGINS TO CRY\n";
			talking_place++;
			system("PAUSE");
		}
		break;
#pragma endregion
	case BLUFFM:
#pragma region BLUFFM
		comparePlayer = character.getInt();
		compareMonster = monster.getWis();
		randomOne = rand() % CRIT;
		randomTwo = rand() % CRIT;
		if (randomOne == CRIT)
		{
			comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
		}
		else
		{
			comparePlayer = comparePlayer + randomOne;
		}

		// multiply compareMonster by it's multiplier
		if (randomTwo == CRIT)
		{
			compareMonster = compareMonster + (randomTwo * MULTIPLIER);
		}
		else
		{
			compareMonster = compareMonster + randomTwo;
		}

		// verify which is greater
		if (comparePlayer < compareMonster)
		{
			cout << "\nDONOVO TELLS YOU ABOUT HIS PAST, THE POOR CHILD\n";
			talking_place--;
		}
		else
		{
			cout << "\nIS DONOVO LYING TO ME?\n";
			talking_place++;
		}
		break;
#pragma endregion
	case CRYM:
#pragma region CRYING
		randomOne = rand() % TEN + 1;
		randomTwo = rand() % TEN + 1;
		if (randomOne == CRIT)
			compareMonster = monster.getCharisma() + randomOne * MULTIPLIER;
		else
			compareMonster = monster.getCharisma() + randomOne;
		if (randomTwo == CRIT)
			comparePlayer = character.getInt() + randomTwo * MULTIPLIER;
		else
			comparePlayer = character.getInt() + randomTwo;
		if (compareMonster >= comparePlayer)
		{
			cout << "DONOVO BEGINS TO CRY\n";
			talking_place--;
		}
		else
		{
			cout << "DONOVO BEGINS TO CRY\n";
			talking_place++;
		}
		break;
#pragma endregion
	default:
		break;
	}
	return 0;
}
#pragma endregion
#pragma region felling
int Fight::donovo_fell_good(MonsterMain & donovo)
{
	randomOne = rand() % SIX;
	randomTwo = rand() % SIX;
	if (donovo.getCon() + randomOne > donovo.getIntell() + randomTwo)
		fealings = 0;
	else
		fealings = 1;
	return fealings;
}
#pragma endregion

#pragma region Player Controls
#pragma region user choice
int Fight::UserChoice(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod)
{
	// set comparePlayer to 0
	comparePlayer = 0;
	cin >> choice;
	choice = toupper(choice[0]);
	// set firstChoice to choice for the monsters fight function
	firstChoice = choice;

	if (choice != ATTACK && choice != RUN && choice != ITEM && choice != TALK)
	{
		do
		{
			cout << "WAIT, WHAT SHOULD I DO AGAIN?\n";
			cin >> choice;
			choice = toupper(choice[0]);
			// set firstChoice to choice for the monsters fight function
			firstChoice = choice;
		} while (choice != ATTACK && choice != RUN && choice != ITEM && choice != TALK);

	}
	if (choice == ATTACK)
	{
		KillEmAll(character, monster, strenth_mod, charisma_mod, diplomacy_mod);
	}
	if (choice == RUN)
	{
		RunAway(character, monster, strenth_mod, charisma_mod, diplomacy_mod);
	}
	if (choice == ITEM)
	{
		Item(character, monster, strenth_mod, charisma_mod, diplomacy_mod);
	}
	if (choice == TALK)
	{
		Talk(character, monster, strenth_mod, charisma_mod, diplomacy_mod);
	}
	return 0;
}

#pragma endregion

#pragma region Kill them all updated
int Fight::KillEmAll(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod)
{
	damage = character.getSTR() + strenth_mod;
	int randomOne = rand() % CRIT;
	int randomTwo = rand() % 4 + 1;
	// if randomOne = 4, set damage to be equal to damage * multiplier * randomOne
	if (randomOne == CRIT)
	{
		damage = damage + (MULTIPLIER * randomOne);
	}
	// else just multiply damage by randomOne
	else
	{
		damage = damage + randomOne;
	}
	// set the defense of the monster to the con and randomTwo
	int defense = monster.getCon() + randomTwo;

	// if damage is greater than or equal to defense
	if (damage > defense)
	{
		// take the damage and take out the defense
		damage = damage - defense;
		// change the hp of the monster
		monster.setHP(damage);
		// comment how much they hurt the monster
		cout << "\nYOU HURT THE " << monster.getName() <<" " << damage << "\n";
	}
	else
	{
		// tell the player that ______ defended against them
		cout << "\nTHE " << monster.getName() << " DEFENDED AGAINST YOUR ATTACK!\n";
	}

	// return 0
	return 0;
}

#pragma endregion

#pragma region Run Away
int Fight::RunAway(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod)
{
	// get the players dex and monsters str
	randomOne = rand() % CRIT;
	randomTwo = rand() % FOUR;
	comparePlayer = character.getDEX() + randomOne;
	compareMonster = monster.getStr() + randomTwo;
	// compare them
	if (comparePlayer >= compareMonster)
	{
		// if the player is higher, set comparePlayer to 1
		comparePlayer = RUN_WORK;
		// say congratulations
		cout << "CONGRATULATIONS! YOU ESCAPE!\n";
	}
	// else set comparePlayer to 0
	else
	{
		comparePlayer = 0;
		// let them know that they failed
		cout << "WHILE FLEEING FROM DONOVO, YOU HAVE TAKEN A WRONG TURN AND HE NOW HAS YOU CORNERED\n";
	}

	// return 0
	return 0;
}

#pragma endregion

#pragma region Items
int Fight::Item(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod)
{

	// clear the screen
	system("CLS");
	// goto the Retrieve_Items function
	item_choice = character.Retrieve_Items();
#pragma region ITEM EFFECTS
#pragma region super potion
	if (item_choice == SUPER_POTION)
	{
		if (character.getHP() < character.getTotalHP())
		{
			character.setHP(character.getHP() + TEN + TEN);
			if (character.getHP() > character.getTotalHP())
				character.setHP(character.getTotalHP());
			cout << "YOU DRINK THE SUPER POTION, IT RESTORES SOME HP\n";
		}
		else
		{
			cout << "YOU DRINK THE SUPER POTION, YET YOU ALREADY HAVE FULL LIFE\n";
		}
		// ATTACK PART
#pragma region ATTACK PART OF THE POTION
		damage = character.getSTR() + strenth_mod + TWO;
		int randomOne = rand() % CRIT + SIX;
		int randomTwo = rand() % FOUR + 1;
		// if randomOne = 4, set damage to be equal to damage * multiplier * randomOne
		if (randomOne >= CRIT + FOUR)
		{
			damage = damage + (MULTIPLIER * randomOne);
		}
		// else just multiply damage by randomOne
		else
		{
			damage = damage + randomOne;
		}
		// set the defense of the monster to the con and randomTwo
		int defense = monster.getCon() + randomTwo;

		// if damage is greater than or equal to defense
		if (damage > defense)
		{
			// take the damage and take out the defense
			damage = damage - defense;
			// change the hp of the monster
			monster.setHP(damage);
			// comment how much they hurt the monster
			cout << "\nYOU ARE EVEN STRONGER FROM THE SUPER POTION, YOU HURT THE MONSTER " << damage << "\n";
		}
		else
		{
			// tell the player that ______ defended against them
			cout << monster.getName() << " DEFENDED AGAINST YOUR ATTACK!\n";
		}
#pragma endregion
	}
#pragma endregion

#pragma region HEALTH POTION

	if (item_choice == HEALTH_POTION)
	{
		if (character.getHP() < character.getTotalHP())
		{
			character.setHP(character.getHP() + TEN + TEN);
			if (character.getHP() > character.getTotalHP())
				character.setHP(character.getTotalHP());
			cout << "YOU DRINK A HEALTH POTION, IT RESTORES SOME HP\n";
		}
		else
		{
			cout << "YOU DRINK A HEALTH POTION, YET YOU ALREADY HAVE FULL LIFE\n";
		}
	}
#pragma endregion

#pragma region ATTACK POTION
	if (item_choice == ATTACK_POTION)
	{
		damage = character.getSTR() + strenth_mod;
		int randomOne = rand() % CRIT + TEN;
		int randomTwo = rand() % FOUR + 1;
		// if randomOne = 4, set damage to be equal to damage * multiplier * randomOne
		if (randomOne >= CRIT + SIX)
		{
			damage = damage + (MULTIPLIER * randomOne);
		}
		// else just multiply damage by randomOne
		else
		{
			damage = damage + randomOne;
		}
		// set the defense of the monster to the con and randomTwo
		int defense = monster.getCon() + randomTwo;

		// if damage is greater than or equal to defense
		if (damage > defense)
		{
			// take the damage and take out the defense
			damage = damage - defense;
			// change the hp of the monster
			monster.setHP(damage);
			// comment how much they hurt the monster
			cout << "\nYOU HURT THE MONSTER " << damage << "\n";
		}
		else
		{
			// tell the player that ______ defended against them
			cout << monster.getName() << " DEFENDED AGAINST YOUR ATTACK!\n";
		}
	}
#pragma endregion

#pragma region XP MULTIPLIER (INCREASER)
	if (item_choice == XP_MULTIPLIER)
	{
		monster.increaseXP(TEN);
	}
#pragma endregion

#pragma region ESCAPE
	if (item_choice == ESCAPE)
	{
		comparePlayer = RUN_WORK;
	}
#pragma endregion

#pragma endregion

	// pause
	system("PAUSE");
	// return 0
	return 0;
}

#pragma endregion

#pragma region Talk

int Fight::Talk(CharacterMain &character, MonsterMain &monster, int strenth_mod, int charisma_mod, int diplomacy_mod)
{

	// clear the screen
	system("CLS");
	// present the options
	cout << "INTIMIDATE (I) DIPLOMACY (D)   BLUFF (B)   CHARM (C) STOP (S) (WILL SKIP TURN)\n";
	// ALLOW USER INPUT
	cin >> choice;
	// RAISE IT TO UPPERCASE AND THE FIRST LETTER
	choice = toupper(choice[0]);
	// verify that it works
#pragma region VERIFY THE CHOICE

	if (choice != INTIMIDATE && choice != DIPLOMACY && choice != BLUFF && choice != CHARM && choice != STOP)
	{
		// GO INTO A LOOP UNTIL A PROPER ENTRY IS PUT IN
		do
		{
			cout << "WHAT WAS THAT?\n";
			cin >> choice;
			choice = toupper(choice[0]);
		} while (choice != INTIMIDATE && choice != DIPLOMACY && choice != BLUFF && choice != CHARM && choice != STOP);
	}

#pragma endregion

#pragma region DIPLOMACY
	// IF DIPLOMACY IS USED, COMPARE int to wis
	if (choice == DIPLOMACY)
		{
			comparePlayer = character.getInt() + diplomacy_mod;
			compareMonster = monster.getWis();
			randomOne = rand() % CRIT + 1;
			randomTwo = rand() % CRIT + 1;
			if (randomOne == CRIT)
			{
				comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
			}
			else
			{
				comparePlayer = comparePlayer + randomOne;
			}

			// multiply compareMonster by it's multiplier
			if (randomTwo == CRIT)
			{
				compareMonster = compareMonster + (randomTwo * MULTIPLIER);
			}
			else
			{
				compareMonster = compareMonster + randomTwo;
			}

			// verify which is greater
			if (comparePlayer >= compareMonster)
			{
				cout << "\nCONGRATULATIONS! YOU HAD A NICE DISCUSSION WITH THE ";
				cout << monster.getName();
				comparePlayer = DIPLOMACY_WORK;
				worked = 1;
				cout << "\n";
			}
			else
			{
				cout << "\nALAS, YOUR ATTEMPTS TO CONVERSE WITH HIM FAILED, ";
				cout << monster.getName();
				cout << " WILL STRIKE BACK";
				comparePlayer = DIPLOMACY_NOT_WORK;
				worked = 0;
				cout << "\n";
			}
		}
#pragma endregion
#pragma region INTIMIDATE
		// IF INTIMIDATE IS USED, COMPARTE STR TO STR
		if (choice == INTIMIDATE)
		{
			comparePlayer = character.getSTR() + strenth_mod;
			compareMonster = monster.getStr();
			randomOne = rand() % CRIT;
			randomTwo = rand() % CRIT;
			if (randomOne == CRIT)
				comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
			else
				comparePlayer = comparePlayer + randomOne;			

			// multiply compareMonster by it's multiplier
			if (randomTwo == CRIT)
			{
				compareMonster = compareMonster + (randomTwo * MULTIPLIER);
			}
			else
			{
				compareMonster = compareMonster + randomTwo;
			}

			// verify which is greater
			if (comparePlayer >= compareMonster)
			{
				cout << "\nYOU HAVE PROVEN YOURSELF TO BE GREATER THAN DONOVO";
				comparePlayer = INTIMIDATE_WORK;
				worked = 1;
				cout << "\n";
			}
			else
			{
				cout << "YOU COULD NOT MAKE YOUR OPPONENT COWER IN FEAR";
				comparePlayer = INTIMIDATE_NOT_WORK;
				worked = 0;
				cout << "\n";
			}
		}
#pragma endregion
#pragma region BLUFF
		// IF BLUFF IS USED
		if (choice == BLUFF)
		{
			comparePlayer = character.getWis();
			compareMonster = monster.getIntell();
			randomOne = rand() % CRIT;
			randomTwo = rand() % CRIT;
			if (randomOne == CRIT)
			{
				comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
			}
			else
			{
				comparePlayer = comparePlayer + randomOne;
			}

			// multiply compareMonster by it's multiplier
			if (randomTwo == CRIT)
			{
				compareMonster = compareMonster + (randomTwo * MULTIPLIER);
			}
			else
			{
				compareMonster = compareMonster + randomTwo;
			}

			// verify which is greater
			if (comparePlayer >= compareMonster)
			{
				cout << "\nYOU HAVE LIED TO THE ENEMY, HE BELIEVES\n";
				comparePlayer = BLUFF_WORK;
				worked = 1;
				cout << "\n";
			}
			else
			{
				cout << "\nWHY WOULD YOU LIE TO THE ENEMY!?!?!\n";
				comparePlayer = BLUFF_NOT_WORK;
				worked = 0;
				cout << "\n";
			}
		}
#pragma endregion
#pragma region Charm
		// IF CHARM IS USED
		if (choice == CHARM)
		{
			comparePlayer = character.getCharisma() + charisma_mod;
			compareMonster = monster.getIntell();
			randomOne = rand() % CRIT;
			randomTwo = rand() % CRIT;
			if (randomOne == CRIT)
			{
				comparePlayer = comparePlayer + (randomOne * MULTIPLIER);
			}
			else
			{
				comparePlayer = comparePlayer + randomOne;
			}

			// multiply compareMonster by it's multiplier
			if (randomTwo == CRIT)
			{
				compareMonster = compareMonster + (randomTwo * MULTIPLIER);
			}
			else
			{
				compareMonster = compareMonster + randomTwo;
			}

			// verify which is greater
			if (comparePlayer >= compareMonster)
			{
				cout << "\nYOU HAVE MADE YOUR ENEMY LIKE YOU\n";
				comparePlayer = CHARM_WORK;
				worked = 1;
				cout << "\n";
			}
			else
			{
				cout << "\nTHE ENEMY IS DISGUSTED AT YOUR ADVANCES\n";
				comparePlayer = CHARM_NOT_WORK;
				worked = 0;
				cout << "\n";
			}
		}
#pragma endregion

		// if stop is used

		return 0;
}

#pragma endregion

#pragma endregion
#pragma endregion

#pragma region Alice Fight set up
///
/// Purpose: to allow Alice to fight
///
void Fight::AliceFight(CharacterMain & character, int strenth_mod, int charisma_mod, int diplomacy_mod)
{
	constitution_modifier = 0;
	// form donovo
	// make him stronger in strength if alice is dead
	if (character.get_donovo_situation() == 0)
	{
		strength_modifier = 2;
		constitution_modifier += 1;
	}
	else
		strength_modifier = 0;
	if (character.get_daniel_situation() == 0)
	{
		dexterity_modifier = 2;
		constitution_modifier += 1;
	}
	else
		dexterity_modifier = 0;
	if (character.get_barimus_situation() == 0)
	{
		constitution_modifier += 1;
		diplomacy_modifier = 2;
	}
	else
		diplomacy_modifier = 0;

	// create Alice
	MonsterMain Alice = MonsterMain("ALICE", 250, 150, 8 + strength_modifier, 6 + constitution_modifier, 4 + dexterity_modifier, 5 + diplomacy_modifier, 5, 7);
	const int FOUR = 4;
	const int SIX = 6;
	// start monsterVariable at a random point
	monsterVariable = rand() % 3;
	// set talking_place to zero
	talking_place = zero;
	// set playerLife and monsterLife to their respective healths
	playerLife = character.getHP();
	monsterLife = Alice.getHP();
	/*
	will do multiple tracks later, one path is plenty for right now
	// part tells you which ai track to follow
	part = rand() % 2;
	*/

	// start a do while loop for the battle
	do
	{
		FightSetup(character, Alice);

		// the the user input
		UserChoice(character, Alice, strenth_mod, charisma_mod, diplomacy_mod);

		// if the monster is now at zero life, kill it
		if (Alice.getHP() <= zero)
		{
			// congratulate the player for winning
			cout << "CONGRATULATIONS! YOU WON!\n";
			character.set_alice_situation(0);
			// pause so that they can read it
			system("PAUSE");
			DisplayConquests(character, Alice);
			// break
			break;
		}// end if

#pragma region Ifs for talking
		if (comparePlayer == INTIMIDATE_WORK || comparePlayer == DIPLOMACY_WORK || comparePlayer == BLUFF_WORK || comparePlayer == CHARM_WORK)
		{
			talking_place++;
			comparePlayer = zero;
		}
		else
		{
			talking_place--;
			comparePlayer = zero;
		}

		if (talking_place >= SIX)
		{
			cout << "\nCONGRATULATIONS! YOU ENDED THE CONFLICT PEACEFULLY!  YOU HAVE A NEW FRIEND!\n";
			system("PAUSE");
			DisplayConquests(character, Alice);
			character.set_donovo_situation(TWO);
			break;
		}
		else if (talking_place <= FAILURE)
		{
			talking_place = zero;
			compareMonster = Alice.getStr() * rand() % 5 + 1;
			character.HurtHP(compareMonster);
			cout << "ALICE HATES YOU! SHE DEALT " << compareMonster << " DAMAGE TO YOU!\n";
			system("PAUSE");
		}

#pragma endregion

		zero = 0;
		// break if comparePlayer equals 1
		if (comparePlayer == RUN_WORK)
		{
			// set comparePlayer to 0
			comparePlayer = zero;
			// break
			break;
		}// end if

		 // call the monster fight function
		AliceAI(Alice, character);
		MonsterFight(Alice, character, monsterVariable);
		// call the MonsterAction function
		MonsterAction(character, Alice);

		//  break if either playerLife equals zero or monsterLife equals zero;
		if (character.getHP() <= zero)
		{
			cout << "SORRY BUT YOU LOST\n";
			character.setRegion(DEAD);
			system("PAUSE");
			break;
		}
		// pause before restarting
		system("PAUSE");

	} while (true); // end while loop
	character.setHP(character.getTotalHP());
}
void Fight::AliceAI(MonsterMain & alice, CharacterMain & player)
{
	switch (monsterVariable) {
	case 1:
		for (int i = 0; i <= 1; i++)
		{
			Attack(player, alice);
			if (damage > defense)
			{
				damage = damage - defense;
				player.setHP(player.getHP() - damage);
				cout << "YOU HAVE TAKEN " << damage << " DAMAGE FROM ALICE'S ATTACK\n";
				Sleep(1000);
			}
			else
			{
				cout << "YOU HAVE DEFENDED YOURSELF FROM ALICE'S ATTACK NUMBER " << i << "\n";
				Sleep(1000);
			}
		}
		break;
	case 2: // two thirds more likely to do a normal attack than special
	case 3:
		Attack(player, alice);
		if (damage > defense)
		{
			damage = damage - defense;
			player.setHP(player.getHP() - damage);
			cout << "YOU HAVE TAKEN " << damage << " DAMAGE FROM ALICE'S ATTACK\n";
			Sleep(1000);
		}
		else
		{
			cout << "YOU HAVE DEFENDED YOURSELF FROM ALICE'S ATTACK\n";
			Sleep(1000);
		}
		break;
	default:
		break;
	}
}
#pragma endregion

Fight::~Fight()
{
}
