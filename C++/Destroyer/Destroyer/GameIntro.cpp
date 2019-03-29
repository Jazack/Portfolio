#pragma once
#include "GameIntro.h"
#pragma comment( lib, "winmm" )
//Go to section: 1532, continue with that

/// Purpose: To Introduce the player to the game and allow them the opportunity to make a name
/// NO TOUCH!
#pragma region Region Chooser

GameIntro::GameIntro()
{
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	// set the random generator to be based on the time
	srand(time(NULL));
	// set time equal to 0
	int firstTime = 0;
	// constants for the various rooms

#pragma region Constants
	// having these two groups is simply for readability so that I can better
	// understand what it is that I am doing, and so that if I need to change something
	// it can be done without making it so that I need to rewrite the entire program

	// const ints for room addresses
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
	const int DEAD = 11;
	const int EXIT_AREA = 12;

	// const ints for room setings
	const int ONE = 1;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;

#pragma endregion

// currently herSe, may be updated in the future
#pragma region Quick set up of the character class
	int xp = 0;
	int money = 10;
	int str = 3;
	int con = 4;
	int dex = 4;
	int intell = 3;
	int wis = 4;
	int charism = 2;
	int location = 0;
	CharacterMain player1(userName, xp, money, location, str, con, dex, intell, wis, charism, 1, 1, 1, 1, 1);
#pragma endregion

	// part one
	Start(player1);
	
#pragma region regions
	// a do while loop so that everytime a new place is choose it can go through and work correctly
	do
	{
		location = player1.getRegion();
		// a case statement so as to find the correct function that is needed
		switch (location)
		{
		case BEGINING:
			if (music != "begining.wav")
			{
				music = "begining.wav";
				PlaySound(TEXT("music\\caves.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Begining(player1);
			break;

		case FRONT_ROOM:
			if (music != "caves.wav")
			{
				music = "caves.wav";
				PlaySound(TEXT("music\\caves.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Cavernous_Room(player1);
			break;

		case R_ALISTAIR:
			if (music != "alistair.wav")
			{
				music = "alistair.wav";
				PlaySound(TEXT("music\\alistair.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Alistair(player1, firstTime);
			break;

		case B_HALL:
			if (music != "caves.wav")
			{
				music = "caves.wav";
				PlaySound(TEXT("music\\caves.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Botom_Hall(player1);
			break;

		case R_DONOVO:
			if (music != "donovo.wav")
			{
				music = "donovo.wav";
				PlaySound(TEXT("music\\donovo.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Donovo(player1);
			break;

		case R_DANIEL:
			if (music != "daniel.wav")
			{
				music = "daniel.wav";
				PlaySound(TEXT("music\\daniel.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Daniel(player1);
			break;

		case TOP_LIVING_ROOM:
			if (music != "caves.wav")
			{
				music = "caves.wav";
				PlaySound(TEXT("music\\caves.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			T_L_Room(player1);
			break;

		case STORE:
			if (music != "store.wav")
			{
				music = "store.wav";
				PlaySound(TEXT("music\\store.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Bath_Room(player1);
			break;

		case T_HALL:
			if (music != "caves.wav")
			{
				music = "caves.wav";
				PlaySound(TEXT("music\\caves.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Top_Hall(player1);
			break;

		case R_BARIMUS:
			if (music != "barimus.wav")
			{
				music = "barimus.wav";
				PlaySound(TEXT("music\\barimus.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Barimus(player1);
			break;

		case R_ALICE:
			if (music != "alice.wav")
			{
				music = "alice.wav";
				PlaySound(TEXT("music\\alice.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			Alice(player1);
			break;

		case DEAD:
			if (music != "dead.wav")
			{
				music = "dead.wav";
				PlaySound(TEXT("music\\dead.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			cout << "YOU LOSE\n";
			Sleep(1000);
			system("PAUSE");
			break;

		case EXIT_AREA:
			if (music != "exit.wav")
			{
				music = "exit.wav";
				PlaySound(TEXT("music\\exit.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			cout << "YOU ARE NOW EXITING\n";
			Sleep(1000);
			break;
		
		}
#pragma endregion

		if (player1.getRegion() == DEAD || player1.getRegion() == EXIT_AREA)
		{
			break;
		}

	} while (location != DEAD);
}
#pragma endregion

/// NO TOUCH
#pragma region Start load

/// a function to start the game
int GameIntro::Start(CharacterMain & player)
{
	system("CLS");
	cout << "WOULD YOU LIKE TO START A NEW GAME(N) OR PLAY A SAVED GAME(S)?\n";
	getline(cin, choice);
	choice = toupper(choice[0]);
	if (choice != SAVED && choice != NO)
	{
		do
		{
			cout << "SORRY, BUT I DID NOT GET THAT, CAN YOU REPEAT YOUR CHOICE?\n";
			getline(cin, choice);	
			choice = toupper(choice[0]);
		} while (choice != SAVED && choice != NO);// NO is "N", and as such, works for new
	}
	if (choice == NO)
	{
		cout << "DO YOU WISH TO SEE THE INTRO? (Y/N)\n";
		getline(cin, choice);
		choice = toupper(choice[0]);
		if (choice != YES && choice != NO)
		{
			do
			{
				cout << "SORRY, BUT I DID NOT GET THAT, CAN YOU REPEAT YOUR CHOICE?\n";
				getline(cin, choice);
				choice = toupper(choice[0]);
			} while (choice != YES && choice != NO);
		}
		else if (choice == YES)
		{
			player.setRegion(BEGINING);
		}
		else
		{
			cout << "PLEASE TYPE A NAME FOR YOUR CHARACTER: ";
			getline(cin, choice);
			player.setName(choice);
			player.setRegion(R_ALISTAIR);
		}// end of if else if else statement
	}// end of if statement
	else
	{
		// loading
		cout << "Which Space do you want to load from?\nslot 1\nslot 2\nslot 3\nslot 4\nslot 5\nOR PRESS \'0\' TO CANCEL AND BEGIN THE GAME\n";
		ChooseANumber(FIVE);

#pragma region Constants
		// const ints for room setings
		const int ONE = 1;
		const int TWO = 2;
		const int THREE = 3;
		const int FOUR = 4;
		const int FIVE = 5;
#pragma endregion

		switch (choice_int)
		{
		case 0:
			cout << "DO YOU WISH TO SEE THE INTRO? (Y/N)\n";
			getline(cin, choice);
			choice = toupper(choice[0]);
			if (choice != YES && choice != NO)
			{
				do
				{
					cout << "SORRY, BUT I DID NOT GET THAT, CAN YOU REPEAT YOUR CHOICE?\n";
					getline(cin, choice);
					choice = toupper(choice[0]);
				} while (choice != YES && choice != NO);
			}
			else if (choice == YES)
			{
				player.setRegion(BEGINING);
			}
			else
			{
				cout << "PLEASE TYPE A NAME FOR YOUR CHARACTER: ";
				getline(cin, choice);
				player.setName(choice);
				player.setRegion(R_ALISTAIR);
			}
			break;
		case 1:
			fileName = "SaveFiles\\FileSpace0.txt";
			break;
		case TWO:
			fileName = "SaveFiles\\FileSpace1.txt";
			break;
		case THREE:
			fileName = "SaveFiles\\FileSpace2.txt";
			break;
		case FOUR:
			fileName = "SaveFiles\\FileSpace3.txt";
			break;
		case FIVE:
			fileName = "SaveFiles\\FileSpace4.txt";
			break;
		}// end case statement
		if (choice_int > 0)
			LoadGame(player, fileName);
	}

	return 0;
}

#pragma endregion

#pragma region Areas
/// NO TOUCH
#pragma region Introduction (one time use, just for starting)
int GameIntro::Begining(CharacterMain &player)
{
	system("CLS");
	Sleep(1500);
	cout << "HEY!  ";
	Sleep(1750);
	cout << "WHERE AM I!  ";
	Sleep(1500);
	cout << "WHY CAN'T I SEE?  ";
	Sleep(1500);
	cout << "WHAT'S GOING ON!? \n\n";
	Sleep(2000);
	// change the text to yellow
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	cout << "HELLO YOUNG ONE, ";
	Sleep(1500);

	cout << "YOU'RE NEW HERE, WHAT iS YOUR NAME?\n";
	Sleep(1250);

	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);

	// ask the user for their name
	getline(cin, userName);
	// store that information within the player class ChangeName function
	player.ChangeName(userName);
	Sleep(1300);
	cout << "I'M " << userName << " WHY CAN'T I SEE?\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	cout << "YOU FELL A LONG WAYS YOUNG ONE,";
	Sleep(2000);
	cout << " AND NOW YOU ARE IN A WORLD OF DARKNESS.";
	Sleep(2000);
	cout << "\nHERE WE DO NOT SEE,";
	Sleep(1750);
	cout << " BUT RATHER FEEL WITH OUR MINDS\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	cout << "FEEL WITH OUR MINDS?";
	Sleep(1500);
	cout << " WHAT DO YOU MEAN?\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	cout << "SIMPLY THAT HERE THERE IS NO LIGHT,";
	Sleep(1750);
	cout << " HERE THERE IS DARKNESS,";
	Sleep(1700);
	cout << " AS SUCH, WE SENSE WITH OUR MINDS.\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	cout << "IS THAT WHY IT FEELS WEIRD WHEN YOU SPEAK TO ME?\n\n";
	Sleep(1800);
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	cout << "NOT NOW!  QUIET!\n\n";
	ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
	Sleep(1500);
	cout << ".";
	Sleep(1500);
	cout << ".";
	Sleep(1500);
	cout << ".\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	cout << "WHAT WAS THAT?\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	cout << "A MONSTER";
	ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
	Sleep(1500);
	cout << ".";
	Sleep(1500);
	cout << ".";
	Sleep(1500);
	cout << ".";
	Sleep(1500);
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	cout << " BUT IT'S GONE NOW.\n\n";
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	Sleep(2000);
	cout << "WHAT DOES IT WANT?\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	cout << "WHO KNOWS?";
	Sleep(1500);
	cout << " BUT NOW WE MUST GO, ";
	Sleep(1500);
	cout << "BEFORE IT RETURNS.\n\n";
	Sleep(2500);
	system("CLS");
	cout << "WELCOME TO MY HOME, ";
	Sleep(1500);
	cout << "WHY DON'T YOU REST FOR A MOMENT, ";
	Sleep(1500);
	cout << "AND REFLECT ON WHO YOU ARE\n\n";
	Sleep(2000);
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	cout << "OKAY...\n";

	ConsoleControls::ConsoleControls(FOREGROUND, GREEN);
	player.DisplayAll();
	Sleep(2500);
	cout << "\n\nDO YOU WANT TO CHANGE YOUR NAME?(y/n)\n";
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	YesOrNo();
	if (choice == YES)
	{
		player.SetName();
	}
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);
	Sleep(1500);
	cout << "HERE AT TIMES YOU MAY NEED TO FIGHT, ";
	Sleep(1500);
	cout << "DO YOU WISH TO LEARN HOW TO FIGHT?(Y/N)\n\n";
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	YesOrNo();

	// allow the player to fight the monster if they choose
	if (choice == YES)
	{
		// set the sublocation to 1 so that the proper fight setup is formed6
		subLocation = 0;
		Fight::Fight(subLocation, player);

	}
	// set the location to equal alistair's room
	player.setRegion(R_ALISTAIR);
	// return 
	return 0;
}

#pragma endregion

/// ONLY TOUCH IF UPDATING FOR WHEN YOU FIGHT HIM
#pragma region Alistairs room
/**
Purpose: To make a function that will run Alistair's room
Param 1; &player
type: CharacterMain
purpose: so that the player item can be used within the function
*/
int GameIntro::Alistair(CharacterMain &player, int &time)
{
	// const ints for room setings
	const int ONE = 1;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;
	ConsoleControls::ConsoleControls(FOREGROUND, YELLOW);// YELLOW IS ALISTAIRS COLOR, MORE ON COLORS UNDER ConsoleControls.h
	// set the title and various options
	r_title = "ALISTAIR'S HOME";
	r_one = "CAVERNOUS ROOM";
	r_two = "FIGHT ANOTHER ILLUSION";
	textColor = "RED";
	// call the simpleformation function
	SimpleFormation(r_title, r_one, r_two, textColor);
	
	// give the player random info everytime that he comes into here
	r_options = rand() % FIVE + 1;

	// IF IT IS THE USERS FIRST TIME, EXPLAIN HOW THINGS SHOULD WORK
	if (player.get_r_alistair() == 0)
	{
		cout << "\n\nAS THIS IS YOUR FIRST TIME HERE, I WILL LET YOU KNOW HOW TO USE THESE CONTROLS, WHEN THERE IS A NUMBER\nNEXT TO THE OPTION, YOU CHOOSE THE NUMBER AND HIT ENTER, WHEN THERE IS A LETTER NEXT TO THE OPTION, YOU PRESS THE LETTER\nAND HIT ENTER";
		player.set_r_alistair(1);
	}
	
#pragma region Random text
	// switch statement to show random dialogue from ALISTAIR
	switch (r_options)
	{
	case ONE:
		cout << "\n\nHELLO YOUNG ONE, AT ANY TIME YOU CAN SAVE OR LOAD THE GAME BY SELECTING S,\nAND YOU CAN VIEW YOUR INVENTORY BY PRESSING I\n";
		break;
		
	case TWO:
		cout << "\n\nWELCOME TO MY ABODE, HERE YOU MAY COME AT ANY TIME TO REST AND RELAX.  I WOULD WARN TO BEWARE THE OTHER,\nDENIZENS, ESPECIALY ALICE WHO LIVES AT THE TOP OF THE WORLD IN THE FURTHEST REACHES OF THE CAVERN\n";
		break;

	case THREE:
		cout << "\n\nYOU REALLY OUGHT TO LEARN HOW TO SEE, THE SETTING THOUGHT-RUNES ARE REALLY QUITE LOVELY\n";
		break;

	case FOUR:
		cout << "\n\nFOR THE RECORD, I HEAR THAT ANNABELE MCALLISTAIR IS RAISING UP THE DEAD, I SUPPOSE JOHN WILL\nNEED TO DO SOMETHING AFTER ALL THIS IS DONE\nOH, ALSO, YOU CAN LEAVE BY PRESSING THE E BUTTON\n";
		break;
	
	case FIVE:
		cout << "\n\nFROM WHAT I CAN SEE FROM YOUR MIND, YOU DON'T TRULY WANT TO COME BACK HOME, WHY IS THAT?\n";
		break;

	default:
		break;
	}// end of the case statement
#pragma endregion
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	// let the player make his decison
	SimpleChooser();


	// do a switch statement of ifs to find out what the user has choosen
	if (choice == SAVED)
	{
		// save
		SaveOrLoad(player);
	}
	if (choice == ITEMS)
	{
		choice = player.Retrieve_Items_Not_Combat();
		if (choice == EXTRA_HEALTH)
		{
			player.setHP(player.getHP() + TEN);
		}
	}
	if (choice == CHOICE_ONE)
	{
		player.setRegion(FRONT_ROOM);
	}
	if (choice == CHOICE_TWO)
	{
		// have the player fight another illusion
		PlaySound(TEXT("music\\fight.wav"), NULL, SND_ASYNC);
		MonsterMain Practice_Illusion = MonsterMain("Practice Illusion", 0, 0, 2, 3, 1, 1, 1, 2);
		Fight::Fight(player, Practice_Illusion);
		PlaySound(TEXT("music\\alistair.wav"), NULL, SND_ASYNC);
	}

	if (choice == EXIT)
	{
		player.setRegion(EXIT_AREA);
	}
	// return 0;
	return 0;
}

#pragma endregion

/// ONLY TOUCH IF UPDATING THE MONSTERS
#pragma region Cavernous room
/**
A FUNCTION TO SET UP THE CAVERNOUS ROOM
PARAM 1: player
TYPE: CharacterMain
PURPOSE: IN CASE A FIGHT TAKES PLACE
*/
void GameIntro::Cavernous_Room(CharacterMain & player)
{
	
	do
	{
	r_title = "CAVERNOUS ROOM";
	r_one = "ALISTAIR";
	r_two = "UPPER CAVERN";
	r_three = "END HALL";
	int const HUNDRED = 100;
	double const THREE_FOURTHS = 0.75;
	r_options = rand() % HUNDRED;
	percentage = HUNDRED * THREE_FOURTHS;

	// if the percentage is in the top twenty five percent, set up a fight
	if (r_options > percentage)
	{
		PlaySound(TEXT("music\\fight.wav"), NULL, SND_ASYNC);
		r_options = rand() % THREE;
		if (r_options == 0)
		{
			MonsterMain monster = MonsterMain("CAVE DWELLER", rand() % 15 + FIVE + TEN, rand() % 15 + 1, rand() % 6 + TWO, rand() % 6 + TWO, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1);
			Fight::Fight(player, monster);
			monster.~MonsterMain();
		}
		if (r_options == 1)
		{
			MonsterMain monster = MonsterMain("MONSTROUS RODENT", rand() % 15 + TEN, rand() % 15 + 1, rand() % FOUR + 1, rand() % FOUR + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % TWO + 1);
			Fight::Fight(player, monster);
			monster.~MonsterMain();
		}
		if (r_options == 2)
		{
			MonsterMain monster = MonsterMain("FUR BALL", rand() % 15 + THREE + TEN, rand() % 15 + 1, rand() % 6 + 1, rand() % FOUR + 1, rand() % 6 + 1, rand() % FOUR + TWO, rand() % 6 + 1, rand() % 6 + TWO);
			Fight::Fight(player, monster);
			monster.~MonsterMain();
		}
		PlaySound(TEXT("music\\caves.wav"), NULL, SND_ASYNC);
	}
	if (player.getRegion() == DEAD)
		break;
	
	ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
	LivingFormation(r_title, r_one, r_two, r_three, textColor);

	// INITIALIZE VARIABLES NEEDED FOR THE SWITCH STATEMENT
#pragma region VARIABLES
	r_options = rand() % FIVE;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
#pragma endregion

	switch (r_options)
	{
	case 0:
		cout << "YOU CAN FEEL A GENTLE BREEZE FLOWING FROM A CAVERN ABOVE YOU, WHAT COULD BE UP THERE?\n";
		break;
	case 1:
		cout << "AS YOU ENTER INTO THIS CAVERN, A STRANGE SENSE OF FAMILIARITY COMES UPON YOU\n";
		break;
	case TWO:
		cout << "STRANGE SOUNDS ECHO ACROSS THE CAVERN COMING FROM FURTHER DOWN A SMALL PASSAGE WAY\n";
		break;
	case THREE:
		cout << "HE ALWAYS FELT THAT SOMETHING WAS WRONG WITH HIM.\nAND SO ONE DAY HE DECIDED TO FIX THAT\n";
		break;
	case FOUR:
		cout << "YOU CAN HEAR THE DISTINCT SOUND OF DRIPPING WATER FROM SOMEWHERE NEAR BY, HOWEVER\nYOU DO NOT KNOW WHERE EXACTLY IT IS COMING FROM\n";
		break;
	default:
		break;
	}
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	NormalChooser();
	const int R_ALISTAIR = 2;
	const int B_HALL = 3;
	const int TOP_LIVING_ROOM = 6;

	// do a switch statement to find out what the user has choosen
	if (choice == SAVED)
	{
		// save
		SaveOrLoad(player);
	}
	if (choice == ITEMS)
	{
		choice = player.Retrieve_Items_Not_Combat();
		if (choice == EXTRA_HEALTH)
		{
			player.setHP(player.getHP() + TEN);
		}
	}
	if (choice == FIRST)
	{
		player.setRegion(R_ALISTAIR);
	}
	if (choice == LAST)
	{
		player.setRegion(B_HALL);
	}
	if (choice == NEXT)
	{
		player.setRegion(TOP_LIVING_ROOM);
	}
	if (choice == EXIT)
	{
		// exit
		player.setRegion(EXIT_AREA);
	}
	break;
}while (true);
}


#pragma endregion

/// ONLY TOUCH IF UPDATING THE MONSTERS
#pragma region Bottom Hall
void GameIntro::Botom_Hall(CharacterMain &player)
{
	do
	{
		r_title = "END HALL";
		r_one = "DONOVO'S ROOM";
		r_two = "CAVERNOUS ROOM";
		r_three = "DANIEL'S ROOM";
		int const HUNDRED = 100;
		double const THREE_FOURTHS = 0.75;
		r_options = rand() % HUNDRED;
		percentage = HUNDRED * THREE_FOURTHS;

		// if the percentage is in the top twenty five percent, set up a fight
		if (r_options > percentage)
		{
			PlaySound(TEXT("music\\fight.wav"), NULL, SND_ASYNC);
			r_options = rand() % THREE;
			if (r_options == 0)
			{
				MonsterMain monster = MonsterMain("CAVE DWELLER", rand() % 15 + FIVE + TEN, rand() % 15 + 1, rand() % 6 + TWO, rand() % 6 + TWO, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			if (r_options == 1)
			{
				MonsterMain monster = MonsterMain("MONSTROUS RODENT", rand() % 15 + TEN, rand() % 15 + 1, rand() % FOUR + 1, rand() % FOUR + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % TWO + 1);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			if (r_options == 2)
			{
				MonsterMain monster = MonsterMain("FUR BALL", rand() % 15 + THREE + TEN, rand() % 15 + 1, rand() % 6 + 1, rand() % FOUR + 1, rand() % 6 + 1, rand() % FOUR + TWO, rand() % 6 + 1, rand() % 6 + TWO);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			PlaySound(TEXT("music\\caves.wav"), NULL, SND_ASYNC);
		}
		if (player.getRegion() == DEAD)
			break;
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		LivingFormation(r_title, r_one, r_two, r_three, textColor);

		// INITIALIZE VARIABLES NEEDED FOR THE SWITCH STATEMENT
#pragma region VARIABLES
		r_options = rand() % FIVE;
		const int TWO = 2;
		const int THREE = 3;
		const int FOUR = 4;
#pragma endregion

		switch (r_options)
		{
		case 0:
			cout << "YOU BUMP INTO A FAR WALL, APPARENTLY THE CAVERN DOESN'T DESCEND ANY LOWER THAN THIS\n";
			break;
		case 1:
			cout << "YOU CAN FELL THE STRANGE GROOVES RUNNING ALONG THE CAVERN, BUT WHAT COULD THEY MEAN?\n";
			break;
		case TWO:
			cout << "YOU HEAR SOMETHING MAKING A THUMPING NOISE COMING FROM ONE OF THE CAVERNS NEARBY\n";
			break;
		case THREE:
			cout << "ONCE UPON A TIME, THERE WAS A YOUNG MAN WHO DID NOT KNOW WHAT TO DO WITH HIMSELF\n";
			break;
		case FOUR:
			cout << "YOU CAN HEAR THE DISTINCT SOUND OF DRIPPING WATER FROM SOMEWHERE NEAR BY, HOWEVER\nYOU DO NOT KNOW WHERE EXACTLY IT IS COMING FROM\n";
			break;
		default:
			break;
		}
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		NormalChooser();

		// do a switch statement to find out what the user has choosen
		if (choice == SAVED)
		{
			// save
			SaveOrLoad(player);
		}
		if (choice == ITEMS)
		{
			choice = player.Retrieve_Items_Not_Combat();
			if (choice == EXTRA_HEALTH)
			{
				player.setHP(player.getHP() + TEN);
			}
		}
		if (choice == FIRST)
		{
			player.setRegion(R_DONOVO);
		}
		if (choice == LAST)
		{
			player.setRegion(R_DANIEL);
		}
		if (choice == NEXT)
		{
			player.setRegion(FRONT_ROOM);
		}
		if (choice == EXIT)
		{
			// exit
			player.setRegion(EXIT_AREA);
		}
		break;
	} while (true);
}

#pragma endregion

/// BELIEVED TO BE FINISHED, COULD HAVE SOMETHING INCORRECT, BETA TESTERS WILL BE IMPORTANT
#pragma region DonovoS CODE

#pragma region Donovo Room

void GameIntro::Donovo(CharacterMain &player)
{

	ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
	// const ints for room setings
	const int ONE = 1;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;

	// set the title and various options
	r_title = "DONOVO'S ROOM";
	r_one = "CAVERNOUS HALL";
	if (player.get_donovo_situation() != 0)
	{
		r_two = "TALK WITH DONOVO";
	}
	else
	{
		r_two = "LOOK AROUND DONOVO'S AREA";
	}
	textColor = "RED";
	// call the simpleformation function
	SimpleFormation(r_title, r_one, r_two, textColor);

	// give the player random info everytime that he comes into here
	r_options = rand() % FIVE + 1;

#pragma region Random text
	// only do these if Donovo is still alive
	if (player.get_donovo_situation() == 1)
	{
		// switch statement to show random dialogue from ALISTAIR
		switch (r_options)
		{
		case ONE:
			cout << "\n\nIT FEELS SO DARK HERE, I DON'T WANT TO KEEP GOING\n";
			break;

		case TWO:
			cout << "\n\nWHY ARE WE HERE?  WHAT ARE WE EVEN DOING?\n";
			break;

		case THREE:
			ConsoleControls::ConsoleControls(FOREGROUND, BLACK);
			cout << "\n\nWHY?  WHY DID YOU LEAVE ME?\n";
			break;

		case FOUR:
			cout << "\n\nI WISH IT WOULD ALL JUST END\n";
			break;

		case FIVE:
			cout << "\n\nWHAT DO YOU WANT NOW?\n";
			break;

		default:
			break;
		}// end of the case statement
	}
	if (player.get_donovo_situation() == ALIVE || player.get_donovo_situation() == THREE)
	{
		// switch statement to show random dialogue from ALISTAIR 
		switch (r_options)
		{
		case ONE:
			cout << "\n\nARE YOU GOING TO STAY WITH ME?\n";
			break;

		case TWO:
			cout << "\n\nWHERE ARE YOU GOING NOW?\n";
			break;

		case THREE:
			ConsoleControls::ConsoleControls(FOREGROUND, BLACK);
			cout << "\n\nI WANT TO BE ALONE RIGHT NOW\n";
			break;

		case FOUR:
			cout << "\n\nI DON'T WANT TO TALK RIGHT NOW\n";
			break;

		case FIVE:
			cout << "\n\nWHAT DO YOU WANT NOW?\n";
			break;

		default:
			break;
		}// end of the case statement
	}
	if (player.get_donovo_situation() == 0)
	{
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		// switch statement to show random dialogue from ALISTAIR
		switch (r_options)
		{
		case ONE:
			cout << "\n\nTHERE'S NOTHING OF INTEREST HERE\n";
			break;

		case TWO:
			cout << "\n\nA FOUL ODOR PERMEATES THE AREA, AND FROM A FAR YOU CAN HEAR AN ECHOING SOUND OF CLANGING METAL\n";
			break;

		case THREE:
			cout << "\n\nSLOWLY A BREEZE FLOWS THROUGH THE AREA\n";
			break;

		case FOUR:
			cout << "\n\nTHIS YOUNG LAD WAS LATER FOUND, HOWEVER HE WASN'T THE SAME\n";
			break;

		case FIVE:
			cout << "\n\nTHIS AREA IS SURPRISINGLY SOFT\n";
			break;

		default:
			break;
		}// end of the case statement
	}
#pragma endregion

	 // let the player make his decison
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	SimpleChooser();

	// do a switch statement of ifs to find out what the user has choosen
	if (choice == SAVED)
	{
		// save
		SaveOrLoad(player);
	}
	if (choice == ITEMS)
	{
		choice = player.Retrieve_Items_Not_Combat();
		if (choice == EXTRA_HEALTH)
		{
			player.setHP(player.getHP() + TEN);
		}
	}
	if (choice == CHOICE_ONE)
	{
		player.setRegion(B_HALL);
	}
	if (choice == CHOICE_TWO)
	{
		
		if (player.get_donovo_situation() != 0)
		{
			Talking_With_Donovo(player);
		}
		else
		{
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "YOU RUMMAGE THROUGH HIS ITEMS, HOWEVER THERE IS NOTHING OF INTEREST HERE\n";
		}
	}

	if (choice == EXIT)
	{
		player.setRegion(EXIT_AREA);
	}
}
#pragma endregion

#pragma region Talking code
void GameIntro::Talking_With_Donovo(CharacterMain & player)
{
#pragma region CONSTANTS
	const int ONE = 1;
	const int TWO = 2;
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
#pragma endregion
	do
	{
		if (player.get_donovo_situation() == 1)
		{
#pragma region ALGORITHM FOR CONVERSING WITH DONOVO

		// clear the screen
		system("CLS");
		iosNumber = 0;
		Fight DonovoFight = Fight();
		do
		{
			switch (iosNumber)
			{
			case 0:
#pragma region Case 0 / begining of the encounter
				// Set the scene
				ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
				cout << "AS YOU DETERMINE TO TALK TO DONOVO, YOU CAN HEAR HIM SHIFTING IN THE ROOM\n";
				// Have a dialogue section
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "           WHAT ARE YOU DOING HERE?\n";
				Sleep(1000);
				cout << "                         WHAT DO YOU WANT?\n\n";
				Sleep(1000);
				// He asks why the user came
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "I WANT TO BEAT ALL THE MONSTERS! (O)NE   OR     I WANT TO HELP YOU!  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = 1;
				else
					iosNumber = TWELVE;
				// Let the user give a reply and write an actual reply 
				break;
#pragma endregion

			case 1:
#pragma region case 1 / defeat all monster
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "   AM I A MONSTER?\n\n\n";
				Sleep(500);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "NO, YOU'RE NOT.  (O)NE  OR    YES, YOU ARE.  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = EIGHT;
				else
					iosNumber = TWO;
				break;
#pragma endregion

			case TWO:
#pragma region CASE TWO / I AM A MONSTER
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "   I'M\n";
				Sleep(1000);
				cout << "      A\n";
				Sleep(1000);
				cout << "        MONSTER?\n\n";
				Sleep(1000);
				cout << "  IS THAT WHY I HURT?\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "YES, AND LET ME END IT FOR YOU.  (O)NE   OR   NO, IT ISN'T.  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = THREE;
				else
					iosNumber = FOUR;
				break;
#pragma endregion

			case THREE:
				// fighting
#pragma region CASE THREE / I REFUSE TO FALL!
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				Sleep(1000);
				cout << "                                   NO!\n";
				Sleep(1000);
				cout << "                    I DON'T WANT TO!\n";
				Sleep(1000);
				cout << "       NOT YET AT LEAST...\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				DonovoFight.DonovoFight(player, 0, 0, 0);
				player.setXP(player.getXP() + 90);
				iosNumber = FIFTEEN;
				break;
				// WILL DO THE FIGHT
#pragma endregion

			case FOUR:
#pragma region CASE FOUR / WHY DO I HURT?
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				Sleep(1000);
				cout << "WHY DO I HURT THAN?\n";
				Sleep(1000);
				cout << "          WHY DO I ALWAYS HURT?\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "I DON'T KNOW, BUT IT WILL END NOW! (O)NE  OR    LET ME HELP YOU.  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = THREE;
				else
					iosNumber = FIVE;
				break;
#pragma endregion

			case FIVE:
#pragma region CASE FIVE / YOU CANT HELP
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "   YOU        ";
				Sleep(1000);
				cout << "CAN'T     ";
				Sleep(1000);
				cout << "HELP.\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "CAN'T I TRY?  (O)NE  OR   WHY DON'T YOU TALK ABOUT IT?  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = SIX;
				else
					iosNumber = SEVEN;
				break;
#pragma endregion

			case SIX:
				// fighting
#pragma region CASE SIX / NO, NO ONE CAN (+1 TO CHARISMA & DIPLOMACY)
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "WHY?\n";
				Sleep(1000);
				cout << "  WHY DOES EVERYTHIN HAVE TO HURT?\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				DonovoFight.DonovoFight(player, 0, 1, 1);
				player.setXP(player.getXP() + 100);
				iosNumber = FIFTEEN;
				break;
#pragma endregion

			case SEVEN:
				// fighting
#pragma region CASE 7 / I DONT WANT TO TALK ABOUT IT! (-1 TO CHARISMA & DIPLOMACY)
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "I DON'T\n";
				Sleep(1000);
				cout << "    I DON'T WANT TO TALK RIGHT NOW!\n";
				Sleep(1000);
				//FIGHT
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				DonovoFight.DonovoFight(player, 0, -1, -1);
				player.setXP(player.getXP() + 75);
				iosNumber = FIFTEEN;
				break;
#pragma endregion
			case EIGHT:
#pragma region CASE EIGHT / THAT WHAT AM I?
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "IF I'M NOT\n";
				Sleep(1000);
				cout << "     IF I'M NOT A MONSTER\n";
				Sleep(1000);
				cout << "THAN WHAT AM I?\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "AN ENEMY! (O)NE  OR    YOU CAN BE MY FRIEND.  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = THREE;
				else
					iosNumber = NINE;
				break;
#pragma endregion

			case NINE:
#pragma region A FRIEND?
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "A FRIEND?\n";
				Sleep(1000);
				cout << "     YOU'LL BE MY FRIEND?\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "YES, I'LL BE YOUR FRIEND. (O)NE  OR   NO, I WOULD NEVER BE YOUR FRIEND.  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = TEN;
				else
					iosNumber = ELEVEN;
				break;
#pragma endregion
			
			case TEN:
				// end without fighting
#pragma region YOURE MY FRIEND!
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "YOU'RE MY FRIEND!\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				player.set_donovo_situation(ALIVE);
				player.setXP(player.getXP() + 400);
				iosNumber = FIFTEEN;
				break;
#pragma endregion

			case ELEVEN:
				// FIGHT
#pragma region CASE ELEVEN / LEAVE ME ALONE! (- STR & DIP & CHARISMA)
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "THEN\n";
				Sleep(1000);
				cout << "  THEN\n";
				Sleep(1000);
				cout << "     THEN LEAVE ME ALONE!\n";
				Sleep(1000);
				// FIGHT
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				DonovoFight.DonovoFight(player, -1, -1, -1);
				player.setXP(player.getXP() + 50);
				iosNumber = FIFTEEN;
				break;
#pragma endregion

			case TWELVE:
#pragma region CASE TWELVE / I WANT TO BE ALONE
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "I, I WANT TO BE ALONE!\n";
				Sleep(1000);
				cout << "              JUST GO AWAY!\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "WELL, AREN'T YOU JUST GRUMPY.  (O)NE  OR    CALM DOWN, LET'S TRY TO TALK THIS THROUGH.  (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = THIRTEEN;
				else
					iosNumber = SEVEN;
				break;
#pragma endregion

			case THIRTEEN:
#pragma region CASE THIRTEEN / NO, I HURT
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "NO,\n";
				Sleep(1000);
				cout << "  I JUST,\n";
				Sleep(1000);
				cout << "      I JUST,\n";
				Sleep(1000);
				cout << "           I JUST HURT\n\n";
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "YOU'RE HURTING?  (O)NE  OR    WHY SHOULD I CARE?\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
					iosNumber = FOUR;
				else
					iosNumber = FOURTEEN;
				break;
#pragma endregion

			case FOURTEEN:
				// fighting
#pragma region CASE FOURTEEN / I HATE YOU! (-2 STRENGTH, -1 CHARISMA, -1 DIPLOMACY)
				Sleep(1000);
				ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
				cout << "I HATE YOU!\n";
				Sleep(1000);
				cout << "    JUST GO AWAY!\n";
				Sleep(1000);
				cout << "           I HATE YOU!\n\n";
				// FIGHT
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				DonovoFight.DonovoFight(player, -2, -1, -1);
				iosNumber = FIFTEEN;
				break;
#pragma endregion

			default:
				break;
			}
			if (iosNumber == FIFTEEN)
				break;
		} while (true);
		DonovoFight.~Fight();
#pragma endregion
		break;
		}
	
		if (player.get_donovo_situation() == 0)
		{
#pragma region donovo dead
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			iosNumber = rand() % 5;
			switch (iosNumber)
			{
			case 0:
				cout << "YOU EXAMINE DONOVO'S ROOM, IT IS DULL AND EMPTY\n";
				break;
			case 1:
				cout << "A RANCID ODOR ESCAPES FROM HIS ROOM\n";
				break;
			case TWO:
				cout << "THE CHILD WAS BROUGHT BACK TO HIS HOME, BUT HE COULD NOT UNDERSTAND\n";
				break;
			case THREE:
				cout << "YOU FIND SOME FOOD AND EAT IT\n";
				break;
			case FOUR:
				cout << "AS YOU SEARCH THE CAVE, YOU HEAR POUNDING ECHOING FROM SOMEWHERE IN THE CAVE SYSTEM\n";
				break;
			default:
				break;
			}
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			system("PAUSE");
			ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
			break;
#pragma endregion
		}
		if (player.get_donovo_situation() == ALIVE || player.get_donovo_situation() == THREE)
		{
#pragma region Donovo Friend
			system("CLS");
			iosNumber = rand() % 5;
			switch (iosNumber)
			{
			case 0:
				// gives super_potion if you have room and haven't been given one yet
				if (player.get_donovo_situation() == ALIVE)
				{
					ConsoleControls::ConsoleControls(FOREGROUND, CYAN);
					for (int i = 0; i < TEN; i++)
					{
						choice = player.getItems(i);
						if (choice == EMPTY || choice == SUPER_POTION)
							break;
					}
					if (choice == EMPTY || choice == SUPER_POTION)
					{
						cout << "HEY, I HAVE SOMETHING TO GIVE TO YOU, A SUPER POTION, IT'LL ALLOW YOU TO HEAL AND DO A POWERFUL ATTACK\n";
						player.Purchase_Item(0, "SUPER_POTION");
						player.set_donovo_situation(THREE);
					}
					else
						cout << "COME BACK WITH MORE ROOM AND I CAN GIVE YOU SOMETHING SPECIAL\n";

				}// end of if statement
				else
				{
					cout << "SORRY, I GAVE YOU ALL THE SUPER POTIONS THAT I HAVE\n";
				}
				break;
			case 1:
				cout << "I'VE ALWAYS WANTED A FRIEND\n";
				break;
			case TWO:

				cout << "BE CAREFUL WITH DANIEL, HE'S SCARED OF EVERYTHING\n";
				break;
			case THREE:
				cout << "DONOVO IS WORKING WITH RUNES\n";
				break;
			case FOUR:
				ConsoleControls::ConsoleControls(FOREGROUND, BLACK);
				cout << "\nTHERE'S SO MUCH PAIN\n";
				break;
			default:
				break;
			}
#pragma endregion
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "DO YOU WISH TO TALK TO DONOVO AGAIN?(Y/N)\n";
			choice = YesOrNo();
			if (choice == NO) {
				break;
			}
			
		}
	} while (true);


}
#pragma endregion

#pragma endregion


#pragma region Daniel

#pragma region Daniels room
void GameIntro::Daniel(CharacterMain &player)
{
	// const ints for room setings
	const int ONE = 1;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;

	// set the title and various options
	r_title = "DANIEL'S ROOM";
	r_one = "CAVERNOUS HALL";
	if (player.get_daniel_situation() != 0)
	{
		r_two = "OBSERVE DANIEL";
	}
	else
	{
		r_two = "LOOK AROUND DANIEL'S AREA";
	}
	textColor = "DARKBLUE";
	ConsoleControls::ConsoleControls(FOREGROUND, BLUE);
	// call the simpleformation function
	SimpleFormation(r_title, r_one, r_two, textColor);

	// give the player random info everytime that he comes into here
	r_options = rand() % FIVE + 1;

#pragma region Random text
	// only do these if Donovo is still alive
#pragma region Alive but not firends

	if (player.get_daniel_situation() == 1)
	{
		// switch statement to show random dialogue from ALISTAIR
		switch (r_options)
		{
		case ONE:
			cout << "\n\nIT CAN'T BE.  IT CAN'T BE\n";
			break;

		case TWO:
			cout << "\n\nWHAT ARE YOU DOING?\n";
			break;

		case THREE:
			cout << "\n\ni WANT TO ESCAPE FROM HERE, i WANT TO ESCAPE FROM EVERYTHING\n";
			break;

		case FOUR:
			cout << "\n\nWHERE WERE YOU?  WHERE WERE YOU?\n";
			break;

		case FIVE:
			cout << "\n\nWHY WON'T YOU LEAVE ME ALONE?\n";
			break;

		default:
			break;
		}// end of the case statement
	}
#pragma endregion
#pragma region Alive and friends (ish)
	if (player.get_daniel_situation() == TWO)
	{
		// switch statement to show random dialogue from ALISTAIR
		switch (r_options)
		{
		case ONE:
			cout << "\n\nARE YOU GOING TO BE MY FRIEND?\n";
			break;

		case TWO:
			cout << "\n\nARE YOU HERE TO HELP ME?\n";
			break;

		case THREE:
			cout << "\n\nALICE YELLED AT ME AGAIN\n";
			break;

		case FOUR:
			cout << "\n\nCAN YOU KEEP THE MONSTERS BACK?  THEY SCARE ME\n";
			break;

		case FIVE:
			cout << "\n\n" << player.getName() << ", WHY DID YOU ABONDON ME?\n";
			break;

		default:
			break;
		}// end of the case statement
	}
#pragma endregion
#pragma region dead
	if (player.get_daniel_situation() == 0)
	{
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		// switch statement to show random dialogue from ALISTAIR
		switch (r_options)
		{
		case ONE:
			cout << "\n\nEVERYTHING IS EMPTY HERE\n";
			break;

		case TWO:
			cout << "\n\nYOU FELL TIRED AS YOU SEARCH AROUND THE ROOM\n";
			break;

		case THREE:
			cout << "\n\nWHEN HIS FAMILY CAME FOR THE CHILD, HE COULD NOT TELL WHO ANYONE WAS\n";
			break;

		case FOUR:
			cout << "\n\nSLOWLY YOU ENTER, AND YOU FELL STRANGE ENTERING INTO THIS AREA\n";
			break;

		case FIVE:
			cout << "\n\nA STENCH ARISES FROM WITHIN HERE\n";
			break;

		default:
			break;
		}// end of the case statement
	}

#pragma endregion
#pragma endregion

	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	// let the player make his decison
	SimpleChooser();

	// do a switch statement of ifs to find out what the user has choosen
	if (choice == SAVED)
	{
		// save
		SaveOrLoad(player);
	}
	if (choice == ITEMS)
	{
		choice = player.Retrieve_Items_Not_Combat();
		if (choice == EXTRA_HEALTH)
		{
			player.setHP(player.getHP() + TEN);
		}
	}
	if (choice == CHOICE_ONE)
	{
		player.setRegion(B_HALL);
	}
	if (choice == CHOICE_TWO)
	{
		if (player.get_donovo_situation() != 0)
		{
			Talking_With_Daniel(player);
		}
		else
		{
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "YOU FIND THAT HIS ROOM IS FULL OF STRANGE ITEMS\n";
			ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		}
	}
	if (choice == EXIT)
	{
		player.setRegion(EXIT_AREA);
	}
}
#pragma endregion

#pragma region Daniel talking

void GameIntro::Talking_With_Daniel(CharacterMain &player)
{

#pragma region CONSTANTS
	const int ONE = 1;
	const int TWO = 2;
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
#pragma endregion
#pragma region Alive but not friends

	if (player.get_daniel_situation() == 1)
	{
		iosNumber = 0;
		do
		{
		system("CLS");
		Hide ThisHide = Hide();
		
		switch (iosNumber)
		{
#pragma region ARE YOU HER TO PLAY

			case 0:
				ConsoleControls::ConsoleControls(FOREGROUND, BLUE);
				cout << "ARE YOU";
				Sleep(1000);
				cout << "    HERE TO";
				Sleep(1500);
				cout << "   PLAY   WITH US?\n";
				Sleep(1500);
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "WHAT ARE YOU PLAYING?    (O)NE  OR   I AM HERE TO DEFEAT ALL THE MONSTERS!    (T)WO\n";
				choice = FirstOrSecond();
				if (choice == CHOICE_ONE)
				{
					iosNumber = ONE;
				}
				else
				{
					iosNumber = THREE;
				}
				break;
#pragma endregion

#pragma region WERE PLAYING HIDE

			case ONE:
				system("CLS");
				ConsoleControls::ConsoleControls(FOREGROUND, BLUE);
				cout << "WE'RE PLAYING   ";
				for (int i = 0; i < THREE; i++)
				{
					Sleep(1000);
					cout << ". ";
				}
				Sleep(1500);
				cout << "   WE'RE  PLAYING";
				Sleep(1500);
				cout << "   WE'RE PLAYING HIDE\n";
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				Sleep(1000);
				cout << "I WANT TO PLAY TOO   (O)NE  OR    I DON'T WANT TO PLAY YOUR STUPID GAMES   (T)WO\n";
				choice = FirstOrSecond();
				
				if (choice == CHOICE_ONE)
				{
					// FIND THE iosNumber THAT LETS YOU LEAVE
					system("CLS");
					ThisHide.playHide();
					player.set_daniel_situation(ThisHide.getStatus());
					PlaySound(TEXT("music\\daniel.wav"), NULL, SND_LOOP | SND_ASYNC);
				}
				else
				{
					iosNumber = TWO;
				}
				break;
#pragma endregion

#pragma region WHY ARE YOU SO MEAN

			case TWO:
				system("CLS");
				ConsoleControls::ConsoleControls(FOREGROUND, BLUE);
				cout << "WHY?";
				Sleep(1000);
				cout << "   WHY ARE";
				Sleep(725);
				cout << "    YOU SO MEAN ? \n\n";
				Sleep(2000);
				system("CLS");
				ThisHide.playHide();
				player.set_daniel_situation(ThisHide.getStatus());
				PlaySound(TEXT("music\\daniel.wav"), NULL, SND_LOOP | SND_ASYNC);
				break;
#pragma endregion

#pragma region WHY ARE WE MONSTERS

			case THREE:
				system("CLS");
				ConsoleControls::ConsoleControls(FOREGROUND, BLUE);
				cout << "WHY?";
				Sleep(1000);
				cout << "   WHY ARE WE";
				Sleep(1000);
				cout << "   WHY ARE WE";
				Sleep(1000);
				cout << "   MONSTERS?\n";
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "YOU'RE A MONSTER BECAUSE I SAY SO!  (O)NE  OR   I DON'T KNOW WHY YOU'RE A MONSTER.   (T)WO\n";
				choice == FirstOrSecond();
				if (choice == CHOICE_ONE)
				{
					iosNumber = FOUR;
				}
				else
				{
					iosNumber = FIVE;
				}
				break;
#pragma endregion

#pragma region I DONT LIKE THAT
			case FOUR:
				system("CLS");
				ConsoleControls::ConsoleControls(FOREGROUND, BLUE);
				cout << "I";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".";
				Sleep(1000);
				cout << ".\n";
				Sleep(1500);
				cout << "    I ";
				Sleep(1500);
				cout << "   DON'T";
				Sleep(1500);
				cout << "     LIKE";
				Sleep(1500);
				cout << "   THAT.\n";
				ThisHide.playHide(1);
				player.set_daniel_situation(ThisHide.getStatus());
				PlaySound(TEXT("music\\daniel.wav"), NULL, SND_LOOP | SND_ASYNC);
				break;
#pragma endregion

#pragma region CANT WE BE FRIENDS
			case FIVE:
				system("CLS");
				ConsoleControls::ConsoleControls(FOREGROUND, BLUE);
				cout << "CAN'T WE";
				Sleep(1000);
				cout << "\n   CAN'T WE BE";
				Sleep(1000);
				cout << "\n      CAN'T WE BE FRIENDS?\n\n";
				ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
				cout << "I SUPPOSE WE CAN?  (O)NE  OR   I DON'T WANT TO BE FRIENDS WITH A MONSTER!   (T)WO\n";
				choice == FirstOrSecond();
				if (choice == CHOICE_ONE)
				{
					player.set_daniel_situation(TWO);
				}
				else
				{

					ThisHide.playHide(1);
					player.set_daniel_situation(ThisHide.getStatus());
					PlaySound(TEXT("music\\daniel.wav"), NULL, SND_LOOP | SND_ASYNC);
				}
				break;
#pragma endregion

			default:
				break;
			}
		} while (player.get_daniel_situation() == ONE);
		if (player.get_daniel_situation() == THREE)
		{
			player.setRegion(DEAD);
		}
	}
#pragma endregion
#pragma region alive and friends
	else if (player.get_daniel_situation() == TWO)
	{
		system("CLS");
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		cout << "YOU FIND THAT DANIEL HAS GONE TO SLEEP\n\n";
		Sleep(1000);
	}
#pragma endregion

}
#pragma endregion

#pragma endregion

#pragma region Top Living Room/Top Cavernous Room

void GameIntro::T_L_Room(CharacterMain &player)
{
	do
	{
		r_title = "UPPER CAVERN";
		r_one = "LOWER CAVERN";
		r_two = "STORE";
		r_three = "END HALL";
		int const HUNDRED = 100;
		double const THREE_FOURTHS = 0.75;
		r_options = rand() % HUNDRED;
		percentage = HUNDRED * THREE_FOURTHS;

		// if the percentage is in the top twenty five percent, set up a fight
		if (r_options > percentage)
		{
			PlaySound(TEXT("music\\fight.wav"), NULL, SND_ASYNC);
			r_options = rand() % THREE;
			if (r_options == 0)
			{
				MonsterMain monster = MonsterMain("MONSTROUS BEING", rand() % 15 + TEN + TEN, rand() % 15 + FIVE, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			if (r_options == 1)
			{
				MonsterMain monster = MonsterMain("STOMPER", rand() % 15 + TEN + TEN + TEN, rand() % 15 + TEN, rand() % 6 + 3, rand() % 6 + FOUR, rand() % 6 + 3, rand() % FOUR + 3, rand() % 6 + 3, rand() % FOUR + 3);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			if (r_options == 2)
			{
				MonsterMain monster = MonsterMain("BREAKER", rand() % 15 + TEN + TEN + FIVE, rand() % 15 + TEN, rand() % TWO + FOUR, rand() % 6 + TEN, rand() % FOUR + 3, rand() % THREE + THREE, rand() % 6 + 3, rand() % FOUR + FOUR);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			PlaySound(TEXT("music\\caves.wav"), NULL, SND_ASYNC);
		}
		if (player.getRegion() == DEAD)
			break;
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		LivingFormation(r_title, r_one, r_two, r_three, textColor);

		// INITIALIZE VARIABLES NEEDED FOR THE SWITCH STATEMENT
#pragma region VARIABLES
		r_options = rand() % FIVE;
		const int TWO = 2;
		const int THREE = 3;
		const int FOUR = 4;
#pragma endregion

		switch (r_options)
		{
		case 0:
			cout << "YOU CAN FELL A BREEZE FLOWING AGAINST YOU, YET YOU DO NOT KNOW WHERE IT'S\nCOMING FROM\n";
			break;
		case 1:
			ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
			cout << "HELP! HELP! I'M STUCK IN A CAVE WITH JUST TWO HOLES LETTING LIGHT IN!\n";
			break;
		case TWO:
			cout << "SLOWLY A GRATING SOUND CAN BE HEARD ECHOING ACROSS THE CAVERNS\n";
			break;
		case THREE:
			cout << "HOWEVER, AFTER SEARCHING FOR A LONG TIME, HE BEGAN TO FIND THAT HE WAS THE PROBLEM.\nAND SO HE DECIDED TO RUN AWAY\n";
			break;
		case FOUR:
			cout << "YOU CAN HEAR A DRIPPING SOUND CLOSE BY NOW\n";
			break;
		default:
			break;
		}
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	NormalChooser();

	// do a switch statement to find out what the user has choosen
	if (choice == SAVED)
	{
		// save
		SaveOrLoad(player);
	}
	if (choice == ITEMS)
	{
		choice = player.Retrieve_Items_Not_Combat();
		if (choice == EXTRA_HEALTH)
		{
			player.setHP(player.getHP() + TEN);
		}
	}
	if (choice == FIRST)
	{
		player.setRegion(FRONT_ROOM);
	}
	if (choice == NEXT)
	{
		player.setRegion(STORE);
	}
	if (choice == LAST)
	{
		player.setRegion(T_HALL);
	}
	if (choice == EXIT)
	{
		// exit
		player.setRegion(EXIT_AREA);
	}
	break;
	} while (true);
}

#pragma endregion

#pragma region Bath Room/Store
void GameIntro::Bath_Room(CharacterMain &player)
{
	// const ints for room setings
	const int ONE = 1;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;

	// set the title and various options
	r_title = "STORE";
	r_one = "LARGE CAVERN";
	r_two = "SUPPLIES";
	textColor = "RED";
	// call the simpleformation function
	ConsoleControls::ConsoleControls(FOREGROUND, MAGENTA);
	SimpleFormation(r_title, r_one, r_two, textColor);

#pragma region Random text

	// give the player random info everytime that he comes into here
	r_options = rand() % FIVE + 1;
	ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
	// switch statement to show random dialogue from ALISTAIR
	switch (r_options)
	{
	case ONE:
		cout << "\n\nWHAT A STRANGE LITTLE SHOP THIS IS\n";
		break;

	case TWO:
		cout << "\n\nWHERE COULD EVERYONE BE?\n";
		break;

	case THREE:
		cout << "\n\nSOMEWHERE IN THE DISTANCE YOU CAN HEAR A WATERFALL\n";
		break;

	case FOUR:
		cout << "\n\nSHUFFLING CAN BE HEARD OUTSIDE OF THE LITTLE SHOP\n";
		break;

	case FIVE:
		cout << "\n\nA POOR BOY WAS LOST, AND NO ONE KNEW WHERE HE HAD GONE\n";
		break;

	default:
		break;
	}// end of the case statement
#pragma endregion
	 // let the player make his decison
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	SimpleChooser();

	// do a switch statement of ifs to find out what the user has choosen
	if (choice == SAVED)
	{
		// save
		SaveOrLoad(player);
	}
	if (choice == CHOICE_ONE)
	{
		player.setRegion(TOP_LIVING_ROOM);
	}
	if (choice == CHOICE_TWO)
	{
		Store(player);
	}
	if (choice == ITEMS)
	{
		choice = player.Retrieve_Items_Not_Combat();
		if (choice == EXTRA_HEALTH)
		{
			player.setHP(player.getHP() + TEN);
		}
	}
	if (choice == EXIT)
	{
		player.setRegion(EXIT_AREA);
	}
}
#pragma endregion

#pragma region Top Hall/Cavern
void GameIntro::Top_Hall(CharacterMain &player)
{
	do
	{
		r_title = "HIGH CAVERN";
		r_one = "ALICE'S ROOM";
		r_two = "LARGE CAVERN";
		r_three = "BARIMUS' ROOM";
		int const HUNDRED = 100;
		double const THREE_FOURTHS = 0.75;
		r_options = rand() % HUNDRED;
		percentage = HUNDRED * THREE_FOURTHS;

		// if the percentage is in the top twenty five percent, set up a fight
		if (r_options > percentage)
		{
			PlaySound(TEXT("music\\fight.wav"), NULL, SND_ASYNC);
			r_options = rand() % THREE;
			if (r_options == 0)
			{
				MonsterMain monster = MonsterMain("MONSTROUS BEING", rand() % 15 + TEN + TEN, rand() % 15 + FIVE, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3, rand() % 6 + 3);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			if (r_options == 1)
			{
				MonsterMain monster = MonsterMain("STOMPER", rand() % 15 + TEN + TEN + TEN, rand() % 15 + TEN, rand() % 6 + 3, rand() % 6 + FOUR, rand() % 6 + 3, rand() % FOUR + 3, rand() % 6 + 3, rand() % FOUR + 3);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			if (r_options == 2)
			{
				MonsterMain monster = MonsterMain("BREAKER", rand() % 15 + TEN + TEN + FIVE, rand() % 15 + TEN, rand() % TWO + FOUR, rand() % 6 + TEN, rand() % FOUR + 3, rand() % THREE + THREE, rand() % 6 + 3, rand() % FOUR + FOUR);
				Fight::Fight(player, monster);
				monster.~MonsterMain();
			}
			PlaySound(TEXT("music\\caves.wav"), NULL, SND_ASYNC);
		}
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		LivingFormation(r_title, r_one, r_two, r_three, textColor);

		// INITIALIZE VARIABLES NEEDED FOR THE SWITCH STATEMENT
#pragma region VARIABLES
		r_options = rand() % FIVE;
		const int TWO = 2;
		const int THREE = 3;
		const int FOUR = 4;
#pragma endregion

		switch (r_options)
		{
		case 0:
			cout << "ANGRY THRASHES COME FROM WITHIN ALICE'S CAVERN, MAYBE IT'D BE BEST TO AVOID HER\n";
			break;
		case 1:
			cout << "YOU BUMP INTO THE END OF THE CAVERN, PERHAPS IT WOULD HAVE BEEN BETTER TO WALK SLOWER\n";
			break;
		case TWO:
			cout << "THERE IS NOTHING TO WRITE HERE.  THERE ARE NO IMPORTANT COMMENTS RIGHT NOW\n";
			break;
		case THREE:
			cout << "FAW AWAY HE RAN, BUT HE COULD NEVER RUN FAR ENOUGH AWAY.\nTHE MONSTERS WERE WITHIN HIMSELF\n";
			break;
		case FOUR:
			cout << "YOU CAN GENTLY FEEL MUTTERINGS COMING FROM BARIMUS' ROOM\n";
			break;
		default:
			break;
		}

		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		NormalChooser();

		// do a switch statement to find out what the user has choosen
		if (choice == SAVED)
		{
			// save
			SaveOrLoad(player);
		}
		if (choice == FIRST)
		{
			player.setRegion(R_ALICE);
		}
		if (choice == LAST)
		{
			player.setRegion(R_BARIMUS);
		}
		if (choice == NEXT)
		{
			player.setRegion(TOP_LIVING_ROOM);
		}
		if (choice == ITEMS)
		{
			choice = player.Retrieve_Items_Not_Combat();
			if (choice == EXTRA_HEALTH)
			{
				player.setHP(player.getHP() + TEN);
			}
		}
		if (choice == EXIT)
		{
			// exit
			player.setRegion(EXIT_AREA);
		}
		break;
	} while (true);
}
#pragma endregion
// Everything Below this needs to be finished (i.e. have the data of the rooms become individualized
#pragma region Barimus
void GameIntro::Barimus(CharacterMain &player)
{
	player.setRegion(R_ALISTAIR);
}
#pragma endregion

#pragma region Alice
void GameIntro::Alice(CharacterMain &player)
{
	// const ints for room setings
	const int ONE = 1;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;

	// set the title and various options
	r_title = "ALICE'S ROOM";
	r_one = "END CAVERN";
	if (player.get_alice_situation() == 1)
	{
		// fight
		r_two = "NUDGE ALICE";
	}
	else if (player.get_alice_situation() != 0)
	{
		r_two = "";
	}
	else
	{
		r_two = "TALK WITH ALICE";
	}
	textColor = "DARKBLUE";
	ConsoleControls::ConsoleControls(FOREGROUND, DARKMAGENTA);
	// call the simpleformation function
	SimpleFormation(r_title, r_one, r_two, textColor);

	// give the player random info everytime that he comes into here
	r_options = rand() % FIVE + 1;

#pragma region Random text
	// only do these if ALICE is still alive
#pragma region Alive
	if (player.get_alice_situation() == 1) {
		switch (r_options)
		{
		case ONE:
			cout << "\n\I ENJOY FIGHTING\n";
			break;

		case TWO:
			cout << "\n\nDID YOU COME TO ATTACK ME?\n";
			break;

		case THREE:
			cout << "\n\nSTUPID PEOPLE KEEP COMING TO ME\n";
			break;

		case FOUR:
			cout << "\n\nLEAVE ME ALONE!\n";
			break;

		case FIVE:
			cout << "\n\nWHY DID YOU COME AGAIN?\n";
			break;

		default:
			break;
		}// end of the case statement
	}
#pragma endregion
#pragma region Alive and friends (ish)
	if (player.get_alice_situation() == TWO)
	{
		// switch statement to show random dialogue from ALISTAIR
		switch (r_options)
		{
		case ONE:
			cout << "\n\I ENJOY FIGHTING\n";
			break;

		case TWO:
			cout << "\n\nDID YOU COME TO ATTACK ME AGAIN?\n";
			break;

		case THREE:
			cout << "\n\nWHY?\n";
			break;

		case FOUR:
			cout << "\n\nLEAVE ME ALONE!\n";
			break;

		case FIVE:
			cout << "\n\nWHY DID YOU COME AGAIN?\n";
			break;
		default:
			break;
		}// end of the case statement
	}
#pragma endregion
#pragma region dead
	if (player.get_alice_situation() == 0)
	{
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		// switch statement to show random dialogue from ALISTAIR
		switch (r_options)
		{
		case ONE:
			cout << "\n\nTHERE IS PLENTY OF CLUTTER HERE\n";
			break;

		case TWO:
			cout << "\n\nEMPTY CHAIRS AT EMPTY TABLES\n";
			break;

		case THREE:
			cout << "\n\nTHE CHILD FELT THAT MONSTERS WERE ALL AROUND HIM\n";
			break;

		case FOUR:
			cout << "\n\nAS YOU ENTER YOU NOTICE LIGHTS FROM THE WINDOW COMING DOWN\n";
			break;

		case FIVE:
			cout << "\n\nA FOUL ODOR CAN BE SMELLED WITHIN HERE\n";
			break;

		default:
			break;
		}// end of the case statement
	}

#pragma endregion
#pragma endregion
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	// let the player make his decison
	SimpleChooser();

	// do a switch statement of ifs to find out what the user has choosen
	if (choice == SAVED)
	{
		// save
		SaveOrLoad(player);
	}
	if (choice == ITEMS)
	{
		choice = player.Retrieve_Items_Not_Combat();
		if (choice == EXTRA_HEALTH)
		{
			player.setHP(player.getHP() + TEN);
		}
	}
	if (choice == CHOICE_ONE)
	{
		player.setRegion(T_HALL);
	}
	if (choice == CHOICE_TWO)
	{
		if (player.get_alice_situation() == 1)
		{
			// WILL CALL ANOTHER FUNCTION HERE TO GO THROUGH THAT
		}
		else if (player.get_alice_situation() == ALIVE)
		{
			ConsoleControls::ConsoleControls(FOREGROUND, DARKBLUE);
			cout << "I DON'T WANT TO TALK RIGHT NOW\n";
			ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		}
		else
		{
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "YOU FIND THAT HIS ROOM IS FULL OF STRANGE ITEMS\n";
			ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		}
	}
	if (choice == EXIT)
	{
		player.setRegion(EXIT_AREA);
	}
}
#pragma endregion

#pragma region Store

void GameIntro::Store(CharacterMain & player)
{
	do
	{
		ConsoleControls::ConsoleControls(FOREGROUND, MAGENTA);
		system("CLS");
		cout << "STORE\n";
		cout << "-------------------------------------------------------------------------------------------\n";
		cout << "YOUR CURRENCY: " << player.getMoney() << " AND YOUR XP IS " << player.getXP() << "\n\n";
		cout << "RETURN  (0)\nHEALTH_POTION  15 CURRENCY (1)\nATTACK_POTION  15 CURRENCY (2)\nXP_MULTIPLIER  25 CURRENCY (3)\nESCAPE  20 CURRENCY (4)\nEXTRA_HEALTH  50 CURRENCY (5)\nINCREASE A STAT (6)\n";

#pragma region Constants
		const int TWO = 2;
		const int THREE = 3;
		const int FOUR = 4;
		const int FIVE = 5;
		const int SIX = 6;
#pragma endregion
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		do
		{
			getline(cin, choice);
			choice_int = -1;
			try
			{
				// this first one is needed so as to verify if it is empty or not (I freaking hate the problems this was causing)
				if (choice.empty())
					throw choice;
				choice = toupper(choice[0]);
				// EXTREME ANNOYANCE AND JUST TRYING TO MAKE THIS WORK
				if (choice == " " || choice == "A" || choice == "B" || choice == "C" || choice == "D" || choice == "E" || choice == "F" || choice == "G" || choice == "H" || choice == "I" || choice == "J" || choice == "K" || choice == "L" || choice == "M" || choice == "N" || choice == "P" || choice == "O" || choice == "Q" || choice == "R" || choice == "S" || choice == "T" || choice == "U" || choice == "W" || choice == "X" || choice == "Y" || choice == "Z")
				{
					throw choice;
				}
				else
				{
					choice_int = stoi(choice);
				}
			}
			catch (string e)
			{
				ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
				cout << "AN INCORRECT ITEM WAS PLACED HERE\n";
			}
			if (choice_int >= 0 && choice_int <= SIX)
				break;
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "SORRY, I DIDN'T CATCH THAT, WHAT DID YOU WANT?\n";

		} while (true);

		switch (choice_int)
		{
		case 0:
			break;
		case 1:
			player.Purchase_Item(15, "HEALTH_POTION");
			break;
		case TWO:
			player.Purchase_Item(15, "ATTACK_POTION");
			break;
		case THREE:
			player.Purchase_Item(25, "XP_MULTIPLIER");
			break;
		case FOUR:
			player.Purchase_Item(20, "ESCAPE");
			break;
		case FIVE:
			player.Purchase_Item(50, "EXTRA_HEALTH");
			break;
		case SIX:
			IncreaseStats(player);
			break;
		default:
			break;
		}

		if (choice_int == 0)
			break;
	} while (true);
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
}

#pragma endregion

#pragma region Increase stats
void GameIntro::IncreaseStats(CharacterMain & player)
{
	ConsoleControls::ConsoleControls(FOREGROUND, MAGENTA);
	// this is the formula used in order to determine the xp that is required to increase the stat
	//5/2(x*x-x+4)
	cout << "CHOOSE THE STAT THAT YOU WANT TO INCREASE\n";
	iosNumber = FIVE_HALVES * (player.getSTR() * player.getSTR() - player.getSTR() + FOUR);
	cout << "(1)  STRENGTH  XP: " << iosNumber << "\n";

	iosNumber = FIVE_HALVES * (player.getCon() * player.getCon() - player.getCon() + FOUR);
	cout << "(2)  CONSTITUTION  XP: " << iosNumber << "\n";

	iosNumber = FIVE_HALVES * (player.getDEX() * player.getDEX() - player.getDEX() + FOUR);
	cout << "(3)  DEXTERITY  XP: " << iosNumber << "\n";

	iosNumber = FIVE_HALVES * (player.getWis() * player.getWis() - player.getWis() + FOUR);
	cout << "(4)  WISDOM  XP: " << iosNumber << "\n";

	iosNumber = FIVE_HALVES * (player.getInt() * player.getInt() - player.getInt() + FOUR);
	cout << "(5)  INTELLIGENCE  XP: " << iosNumber << "\n";

	iosNumber = FIVE_HALVES * (player.getCharisma() * player.getCharisma() - player.getCharisma() + FOUR);
	cout << "(6)  CHARISMA  XP: " << iosNumber << "\n";
	
	cout << "TO GO BACK, PRESS 0\n";
	ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
	iosNumber = ChooseANumber(SIX);
#pragma region increasing the stats algorithm
	if (iosNumber == 1)
	{
		iosNumber = FIVE_HALVES * (player.getSTR() * player.getSTR() - player.getSTR() + FOUR);
		if (player.getXP() >= iosNumber)
		{
			player.setXP(player.getXP() - iosNumber);
			player.setSTR(player.getSTR() + 1);
		}
	}

	if (iosNumber == 2)
	{
		iosNumber = FIVE_HALVES * (player.getCon() * player.getCon() - player.getCon() + FOUR);
		if (player.getXP() >= iosNumber)
		{
			player.setXP(player.getXP() - iosNumber);
			player.setCon(player.getCon() + 1);
			player.setTotalHP();
		}
	}

	if (iosNumber == 3)
	{
		iosNumber = FIVE_HALVES * (player.getDEX() * player.getDEX() - player.getDEX() + FOUR);
		if (player.getXP() >= iosNumber)
		{
			player.setXP(player.getXP() - iosNumber);
			player.setDEX(player.getDEX() + 1);
		}
	}

	if (iosNumber == 4)
	{
		iosNumber = FIVE_HALVES * (player.getWis() * player.getWis() - player.getWis() + FOUR);
		if (player.getXP() >= iosNumber)
		{
			player.setXP(player.getXP() - iosNumber);
			player.setWis(player.getWis() + 1);
		}
	}

	if (iosNumber == 5)
	{
		iosNumber = FIVE_HALVES * (player.getInt() * player.getInt() - player.getInt() + FOUR);
		if (player.getXP() >= iosNumber)
		{
			player.setXP(player.getXP() - iosNumber);
			player.setInt(player.getInt() + 1);
		}
	}

	if (iosNumber == 6)
	{
		iosNumber = FIVE_HALVES * (player.getCharisma() * player.getCharisma() - player.getCharisma() + FOUR);
		if (player.getXP() >= iosNumber)
		{
			player.setXP(player.getXP() - iosNumber);
			player.setCharisma(player.getCharisma() + 1);
		}
	}
#pragma endregion

}
#pragma endregion


#pragma region Option Choosers

#pragma region Yes or No
string GameIntro::YesOrNo()
{

	do
	{
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		getline(cin, choice);
	choice = toupper(choice[0]);
	if (choice != YES && choice != NO)
	{
		ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
		cout << "SORRY, I DIDN'T HEAR YOU, WHAT WAS THAT?\n";
	}
	else
	{
		break;
	}

	} while (choice != YES && choice != NO);

	return choice;
}
#pragma endregion

#pragma region Choose a Number

int GameIntro::ChooseANumber(int upperLimit)
{	
	choice_int = -1;
	// enter a do-while loop until an acceptable option is finished
	do
	{
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		getline(cin, choice);
		choice = toupper(choice[0]);
		// EXTREME ANNOYANCE AND JUST TRYING TO MAKE THIS WORK
		
		try
		{
			choice_int = stoi(choice);
		}
		catch (const std::exception&)
		{

		}
		

		// ask the user to redo their answer
		if (choice_int < 0 || choice_int > upperLimit)
		{
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "WAIT, WHAT SHOULD I DO AGAIN?\n";
		}
		else
		{
			break;
		}
	} while (true);

	return choice_int;
}
#pragma endregion

#pragma region SAVE OR LOADER

/**
purpose: a function to find out weather or not to save or load the game
*/
void GameIntro::SaveOrLoad(CharacterMain & player)
{
	const int ONE = 1;
	const int TWO = 2;
	const int THREE = 3;
	const int FOUR = 4;
	const int FIVE = 5;
	const int SIX = 6;
	// ask the user what number they desire
	ConsoleControls::ConsoleControls(FOREGROUND, DARKCYAN);
	cout << "\nDO YOU DESIRE TO SAVE (S) OR LOAD (L)? OR YOU CAN CANCEL (C)\n";
	// call the choose a number function
	string choice = SaveLoadChooser();
	if (choice == CANCEL)
	{
		// This is empty as if the user cancels, it will do nothing here and just allow the user to go back and play
	}
	else
	{
		ConsoleControls::ConsoleControls(FOREGROUND, DARKCYAN);
		cout << "WHAT SLOT DO YOU WISH TO TAKE?\n1\n2\n3\n4\n5\nOr press \'0\' to cancel\n";
		int fileNumber = ChooseANumber(FIVE);
		// a case statement to find out what file is to be used
		switch (fileNumber)
		{
		case 0:
			break;
		case 1:
			fileName = "FileSpace0.txt";
			break;
		case TWO:
			fileName = "FileSpace1.txt";
			break;
		case THREE:
			fileName = "FileSpace2.txt";
			break;
		case FOUR:
			fileName = "FileSpace3.txt";
			break;
		case FIVE:
			fileName = "FileSpace4.txt";
			break;
		}// end case statement
		if (choice_int > 0)
		{
			// now to save/load, depending on the option
			if (choice == SAVED)
			{
				SaveGame(player, fileName);
			}
			else
			{
				LoadGame(player, fileName);
			}// end if/else statement
		}
	}
}

#pragma endregion

#pragma region SAVER

/**
purpose: a function to save the game
param 1: player
type: CharacterMain
purpose: to use to save the info
*/
void GameIntro::SaveGame(CharacterMain & player, string fileLocation)
{

	// start the stream
	ofstream saving;
	cout << fileLocation;
	// open saving
	saving.open(fileLocation);
#pragma region Saving
		// save name
		saving << player.getName() << endl;

		// get xp
		saving << player.getXP() << endl;

		// get HP
		saving << player.getHP() << endl;

		// get money
		saving << player.getMoney() << endl;

		// get region
		saving << player.getRegion() << endl;

		// get str
		saving << player.getSTR() << endl;

		// get CON
		saving << player.getCon() << endl;

		// get Dex
		saving << player.getDEX() << endl;

		// get int
		saving << player.getInt() << endl;

		// get wis
		saving << player.getWis() << endl;

		// get Charisma
		saving << player.getCharisma() << endl;

		// get r_Alistair variable
		saving << player.get_r_alistair() << endl;

		for (int i = 0; i < TEN; i++)
		{
			saving << player.getItemsInt(i) << endl;
			saving << player.getItems(i) << endl;
		}
		// all of the situations

		saving << player.get_alistair_situation() << endl;

		saving << player.get_alice_situation() << endl;

		saving << player.get_barimus_situation() << endl;

		saving << player.get_daniel_situation() << endl;

		saving << player.get_donovo_situation() << endl;
#pragma endregion
	// close saving
		saving.close();
}

#pragma endregion

#pragma region lOADER

/**
purpose: a function to load the game
param 1: player
type: CharacterMain
purpose: to use to store the info
*/
void GameIntro::LoadGame(CharacterMain & player, string fileLocation)
{

	/**/
	// create the file stream loading
	ifstream loading;

#pragma region Loading

	// only work if it can open
	loading.open(fileLocation);
	if (loading.is_open())
	{
		// initialize variables used in the following sequence
		int intHolder;
		string nameHolder;

		while (!loading.eof())
		{

			getline(loading, nameHolder);
			player.setName(nameHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setXP(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setHP(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setMoney(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setRegion(intHolder);
			
			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setSTR(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setCon(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setDEX(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setInt(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setWis(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.setCharisma(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);

			player.set_r_alistair(intHolder);

			for (int i = 0; i < TEN; i++)
			{
				getline(loading, nameHolder);
				intHolder = stoi(nameHolder);
				player.setItemsInt(i, intHolder);

				getline(loading, nameHolder);
				player.setItems(i, nameHolder);
			}

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.set_alistair_situation(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.set_alice_situation(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.set_barimus_situation(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.set_daniel_situation(intHolder);

			getline(loading, nameHolder);
			intHolder = stoi(nameHolder);
			player.set_donovo_situation(intHolder);

			player.setTotalHP();

			// break
			break;
		}
	}
	// open the files stream loadin
	loading.close();

#pragma endregion

}

#pragma endregion

#pragma region Choose to save or load
string GameIntro::SaveLoadChooser()
{
	do
	{
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		getline(cin, choice);
		choice = toupper(choice[0]);
		if (choice != SAVED && choice != LAST && choice != CANCEL)
		{
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "SORRY, I DIDN'T HEAR YOU, WHAT WAS THAT?\n";
		}
		else
		{
			break;
		}

	} while (choice != SAVED && choice != LAST);

	return choice;
}
#pragma endregion

#pragma region Simple chooser
void GameIntro::SimpleChooser()
{
	choice = choice.empty();
	do
	{// this will just go and take the user information and figure out what the user wants to do out of hte given options
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		getline(cin, choice);
		choice = toupper(choice[0]);
		if (choice != SAVED && choice != CHOICE_ONE && choice != CHOICE_TWO && choice != EXIT && choice != ITEMS)
		{
			cout << choice << "\n";
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "SORRY, I DIDN'T HEAR YOU, WHAT WAS THAT?\n";// only when the others are false
		}
		else
		{
			break;
		}

	} while (choice != SAVED && choice != CHOICE_ONE && choice != CHOICE_TWO && choice != EXIT && choice != ITEMS);
}
#pragma endregion

#pragma region Normal chooser
/**
A FUNCTION TO GET THE USER'S CHOICE WHEN THERE ARE THREE OPTIONS AVAILABLE
*/
void GameIntro::NormalChooser()
{
	
	const string EXIT = "E";
	
	do
	{
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		getline(cin, choice);
		choice = toupper(choice[0]);
		if (choice != SAVED && choice != FIRST && choice != NEXT && choice != LAST && choice != EXIT && choice != ITEMS)
		{
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "SORRY, I DIDN'T HEAR YOU, WHAT WAS THAT?\n";
			cout << "Check point A";
		}
		else
		{
			break;
		}

	} while (choice != SAVED && choice != FIRST && choice != NEXT && choice != LAST && choice != EXIT && choice != ITEMS);
}
#pragma endregion

#pragma region First or Second
/**
A FUNCTION TO DETERMINE WHETHER OR NOT THE FIRST OR SECOND CHOICE WAS WANTED,

USED IN COMMUNICATION SEQUENCES
*/
string GameIntro::FirstOrSecond()
{
	do
	{
		ConsoleControls::ConsoleControls(FOREGROUND, WHITE);
		getline(cin, choice);
		choice = toupper(choice[0]);
		if (choice != CHOICE_ONE && choice != CHOICE_TWO)
		{
			ConsoleControls::ConsoleControls(FOREGROUND, GRAY);
			cout << "I DON'T THINK THAT I SHOULD DO THAT\n";
		}
		else
		{
			break;
		}
	} while (choice != CHOICE_ONE && choice != CHOICE_TWO);

	return choice;
}

#pragma endregion

#pragma endregion

#pragma region Formations

#pragma region Standard Formation
/// a function to set up the standard formation of the area
int GameIntro::LivingFormation(string title, string roomOne, string roomTwo, string roomThree, string colors)
{
	// clear the screen
	system("CLS");

	// place the room title in the middle
	cout << title << "\n";

	// make a line of -----
	cout << "-------------------------------------------------------------------------------------------\n";

	// give the options
	cout << roomOne << " (\"F\")IRST   " << roomTwo << " (\"N\")EXT    " << roomThree << " (\"L\")AST\n\n";

	// return 0
	return 0;
}

#pragma endregion

#pragma region Simple Formation

/**
purpose: to make a function that will creare the basic format for the room
param 1: title
type: string:
purpose: to write out the title

param 2: roomOne
type: string
purpose: to write out the room outside
*/
int GameIntro::SimpleFormation(string title, string roomOne, string optionTwo, string colors)
{
	// clear the screen
	system("CLS");

	
	// place the room title in the middle
	cout << title << "\n";

	// make a line of -----
	cout << "-------------------------------------------------------------------------------------------\n";

	// give the options
	cout << roomOne << " (\"O\")NE      " << optionTwo << " (\"T\")WO\n";
	
	
	// return 0
	return 0;
}// end of function
#pragma endregion

#pragma endregion


GameIntro::~GameIntro()
{
}
