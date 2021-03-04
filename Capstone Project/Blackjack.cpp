#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Blackjack.h"

using namespace std;

void Blackjack::print_playerCards(int index)
{
	if (index == -1)
	{
		for (int i = 0; i < playerHand.size(); i++)
		{
			(playerHand[i] == 1) ? cout << "Ace" : cout << playerHand[i];
			cout << " ";
		}
	}
	else
	{
		cout << (playerHand[index] == 1) ? 'Ace' : char(playerHand[index]);
		cout << " ";
	}
}

void Blackjack::print_game()
{
	cout << "House's Card: " << get_houseHand()[0] << endl;
	cout << "Your cards: "; print_playerCards(-1); cout << endl;
	cout << "Your total: " << get_total(playerHand) << endl;
}

int Blackjack::get_card()
{
	srand((unsigned)time(0) + rand());
	
	// Generate a number between 1 and 10
	int card = rand() % 10 + 1;
	return card;
}

int Blackjack::get_total(vector<int> hand)
{
	int total = 0;
	int aces = 0;
	for(int i = 0; i < hand.size(); i++)
	{
		if (hand[i] == 1) 
		{
			aces++;
			total += 11;
		}
		else
		{
			total += hand[i];
		}
		
	}

	if(total > 21 && aces > 0)
	{
		// Subract 11, add 1
		total -= 10 * aces;
	}
	return total;
}

vector<int> Blackjack::get_playerHand() const
{
	return playerHand;
}

vector<int> Blackjack::get_houseHand() const
{
	return houseHand;
}

void Blackjack::add_to_player(int card)
{
	playerHand.push_back(card);
}

void Blackjack::add_to_house(int card)
{	
	houseHand.push_back(card);
}

bool Blackjack::hit()
{
	add_to_player(get_card());
	return (get_total(playerHand) > 21) ? 1 : 0;
}

bool Blackjack::stand()
{
	// TODO: Make friend function to handle ai so this function is not as long
	switch (get_difficulty())
	{
	case 1:
		while (get_total(houseHand) < 17)
		{
			add_to_house(get_card());
		}
		if (get_total(houseHand) >= 17)
		{
			return (get_total(houseHand) > get_total(playerHand) && get_total(houseHand) <= 21);
		}
		break;
	default:
		break;
	}
}

Blackjack::Blackjack(double m, double b, int difficulty) : casino_game(m, b, difficulty)
{
	add_to_house(get_card()); add_to_house(get_card());
	add_to_player(get_card()); add_to_player(get_card());
}