#pragma once
#pragma comment( lib, "winmm" )
#include "Opening.h"
#include <string>
#include <iostream>
#include<cstdlib>
#include <ctype.h>
#include <string.h>
#include "Credits.h"
#include <stdlib.h>
#include "GameIntro.h"
#include <Windows.h>

// test
#include <mmsystem.h>
using namespace std;



Opening::Opening()
{
	Display();
}

int Opening::Display()
{
	int tracker = 0;
	do {
		PlaySound(TEXT("music\\soundFile1.wav"), NULL, SND_LOOP | SND_ASYNC);
		system("CLS");
		cout << "HELLO USER!  WELCOME TO THIS GAME!\nPLEASE CHOOSE ONE OF THESE OPTIONS:\nSTART (S)\nCREDITS (C)\nEND (E)\n";
		getline(cin, choice);
		UserChoice();

		if (choice != START && choice != CREDITS && choice != END)
		{
			do
			{
				cout << "SORRY, WE DO NOT RECOGNIZE YOUR ENTRY, PLEASE TRY AGAIN\n";
				cin >> choice;
				UserChoice();
			} while (choice != START && choice != CREDITS && choice != END);
		}
		tracker = SwitchLocations();
	} while (tracker != 1);
	return 0;
}

string Opening::getChoice()
{
	return choice;
}

int Opening::UserChoice()
{
	choice = toupper(choice[0]);
	return 0;
}

int Opening::SwitchLocations()
{
	if (choice == START)
	{
		GameIntro::GameIntro();
	}
	if (choice == CREDITS)
	{	
		Credits::Credits();
		Opening::Display();
	}
	if (choice == END)
	{
		return 1;
	}
	return 0;
}
Opening::~Opening()
{
}
