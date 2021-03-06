// Assignment: Capstone Project
// Created by Joshua Roberts
// Date: 6/8/2021

// https://stackoverflow.com/questions/7035023/stdmax-expected-an-identifier/7035078
#define NOMINMAX

#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>

// *********** CLASSES ***********
#include "safe_input.h"
#include "Blackjack.h"
#include "GameOfLife.h"
#include "String Utilities.h"
#include "fileTemplate.h"
#include "Game.h"

using namespace std;



int main()
{
	bool mainMenu = true;
	bool casinoMenu = false;
	bool gameOfLifeMenu = false;
	int input;
	string sInput;
	double money = 1000;

	while (mainMenu)
	{
		system("CLS");
		fileTemplate mainMenu("Menu Templates/Main Template.txt", { "Welcome to the Casino of computer science!", "Input a number to go to one of the categories below!", "Games", "Simulations", "Generate a Maze", "Play Dungeon Delver Game" });

		Blackjack bGame(money, 10, 1);
		game_of_life gGame;
		Game game;
		gGame.init_array();

		cout << mainMenu.get_parsed_menu_string();

		safe_input<int>(&input);
		cout << mainMenu.get_parsed_menu_string();

		switch (input)
		{
		case 1:
			casinoMenu = true;
			break;
		case 2:
			gameOfLifeMenu = true;
			break;
		case 3:
		{
			int height;
			int width;
			system("CLS");

			cout << "Note that your maze size will be rounded to make sure it is properly generated." << endl;
			cout << "Warning: Using numbers that are too large(~>100) may break the program due to the nature of the algorithm" << endl;
			cout << "Enter width of maze: ";
			safe_input<int>(&width);
			cout << "\nEnter height of maze: ";
			safe_input<int>(&height);

			Maze maze(width, height);
			system("CLS");
			maze.reverse_backtrack_generate();
			maze.print_map();
			system("PAUSE");
			break;
		}
		case 4:
			system("CLS");
			game.toggle_game();
			game.run_game();
			//game.start_battle(true);
			break;
		default:
			break;
		
		}
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
			safe_input<int>(&input);
			switch (input)
			{
			case 1:
				if (bGame.hit()) { cout << "You busted!\n"; system("PAUSE"); casinoMenu = false; };
				money -= bGame.get_bet();
				break;
			case 2:
			{
				int stand = bGame.stand();
				int index = 1;

				while (index < bGame.get_houseHand().size() - 1)
				{
					cout << "\nHouse draws "; bGame.print_houseCards(index); cout << endl;
					index++;
					system("PAUSE");
				}
				if (stand == 1)
				{
					cout << "\nYou win!\n\n";
					money += bGame.get_return();
				}
				else if (stand == 2)
				{
					cout << "\nIt was a draw\n";
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
			cout << "Welcome to Conway's Game of Life!\n";
			cout << "Here you can explore the cellular automaton devised by John Conway\n";
			cout << "1. Simulate X amount of generations\n";
			cout << "2. Simulate until exited\n";
			cout << "3. Create a blank template\n";
			cout << "4. Load a custom template\n";
			cout << "5. Notes and Help\n";
			cout << "6. Back\n";

			cout << "Choice: ";
			safe_input<int>(&input);

			switch (input)
			{
			case 1:
				while (true)
				{
					system("CLS");
					gGame.print_game();
					cout << "\nGenerations simulated: " << gGame.get_amount_simulated() << "\n";
					gGame.simulate_generation();
					system("PAUSE");
				}
				break;
			case 2:
				while (!(GetKeyState('X') & 0x8000))
				{
					system("CLS");
					gGame.print_game();
					cout << "\nGenerations simulated: " << gGame.get_amount_simulated() << "\n";
					cout << "Hold X to exit\n";
					gGame.simulate_generation();
					Sleep(500);
				}
				break;
			case 3:
				gGame.create_blank_template();
				break;
			case 4:
				system("CLS");
				cout << "Enter the EXACT name of the template file: ";
				cin.ignore();
				getline(cin, sInput);
				gGame.use_template(sInput);
				break;
			case 5:
				system("CLS");
				cout << "This game of life will vary majorly depending on how big the grid is. \nRather than killing cells that go out of bounds, the program instead has the cells wrap around to the other side. \nThis means that patterns such as the R-pentomino will eventually die(rather than stabilize) because some of the cells will wrap around and disrupt the original formation. \nThe best way to test this is to use things such as \"still lifes\", \"Oscillators\", or \"Spaceships\"\n Wikipedia has some good patterns: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life \n";
				system("PAUSE");
				break;
			case 6:
				gameOfLifeMenu = false;
				break;
			default:
				break;
			}

		}
		input = NULL;
	}

	return 0;
}
