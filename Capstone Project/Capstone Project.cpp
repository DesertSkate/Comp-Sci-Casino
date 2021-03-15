// Assignment: Capstone Project
// Created by Joshua Roberts
// Date: 

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Blackjack.h"
#include "GameOfLife.h"

using namespace std;

void displayMenu() 
{
	cout << "Welcome to the Casino of computer science!\n";
	cout << "Input a number to go to one of the categories below!\n";
	cout << "1. Games\n2. Simulations\n";
}


// TODO: Make file input system less sensitive
int main()
{
	bool mainMenu = true;
	bool casinoMenu = false;
	bool gameOfLifeMenu = false;
	int input;
	double money = 1000;

	while (mainMenu)
	{
		system("CLS");

		Blackjack bGame(money, 10, 1);
		game_of_life gGame;
		gGame.init_array();
		//gGame.create_blank_template();

		displayMenu();

		while (!(cin >> input))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			displayMenu();
		}

		switch (input)
		{
		case 1:
			casinoMenu = true;
			break;
		case 2:
			gameOfLifeMenu = true;
			break;
		default:
			break;
		
		}
		gGame.use_template("Blank Template.txt");
		while (casinoMenu)
		{
			system("CLS");
			bGame.print_game();

			if (bGame.hasBlackjack(bGame.get_playerHand()))
			{
				cout << "\nYou have Blackjack!\n";
				money += bGame.get_return();
				system("PAUSE");
				break;
			}

			cout << "\n\n1. To hit, 2 to stand: ";
			cin >> input;
			switch (input)
			{
			case 1:
				if (bGame.hit()) { cout << "You busted!\n"; system("PAUSE"); casinoMenu = false; };
				money -= bGame.get_bet();
				break;
			case 2:
			{
				bool stand = bGame.stand();
				int index = 1;

				while (index < bGame.get_houseHand().size() - 1)
				{
					cout << "\nHouse draws "; bGame.print_houseCards(index); cout << endl;
					index++;
					system("PAUSE");
				}
				if (stand)
				{
					cout << "\nYou win!\n\n";
					money += bGame.get_return();
				}
				else
				{
					cout << "\nYou lose\n";
					money -= bGame.get_bet();
				}
				bGame.print_game();
				system("PAUSE");
				casinoMenu = false;
			}
			default:
				break;
			}
		}
		while (gameOfLifeMenu)
		{
			system("CLS");
			gGame.print_game();
			gGame.simulate_generation();
			cout << "\n";
			system("PAUSE");
		}
		input = NULL;
	}

	return 0;
}
