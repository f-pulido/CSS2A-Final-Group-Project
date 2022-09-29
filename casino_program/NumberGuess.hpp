/*
Author: Fernando Pulido
Other Contributors: Oswaldo Cortes & Carlos Santiago Pacheco 
Last Modified: 5/14/2022
Description: This class allows for a player to earn chips by guessing correct random generated numbers from 1-10
*/


#ifndef NUMBERGUESS_H
#define NUMBERGUESS_H
#include "Player.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

class NumberGuess
{
	public:
	  NumberGuess();
	  NumberGuess(int userAmount, int userBet, int userGuess);
	  // Getters
	  int getAmount() const { return amount; }
	  int getBet() const { return bet; }
	  int getGuess() const { return guess; }
	  // Setters
	  void setAmount(int amount) { this->amount = amount; }
	  void setBet(int bet) { this->bet = bet; }
	  void setGuess(int guess) { this->guess = guess; }
	  // Other
	  void display(Player& user);
		void runNumberGuess(Player& user);
		void regularMatch(Player& user, char choice, NumberGuess game,
											int winCount, bool isActivated);
	private:
	  int amount, bet, guess;
};

#endif