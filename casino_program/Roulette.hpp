/*
	Author: Oswaldo Cortes
	Other Contributors: N/A
	Last Modified: 5-14-2022
	Desciption: This class has the necessary pototype functions
  to simulate a game of roulette. It includes code that takes,
  tracks, and validates the bets, chips of the player, chips bet,
	and net balance.
*/
#ifndef ROULETTE_H
#define ROULETTE_H
#include "Number.hpp"
#include "Player.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

class Roulette
{
	public:
		static Number rouletteNums[37];
		// Default Constructor. (Overloaded Constructor not needed)
		Roulette(Player& user);
		// Setters
		void setBets();
		void setSpinShift(int num);
		void setContinueGame(char choice) {continueGame = choice;}
		// Getters
	  int getSpinShift() const {return spinShift;}
		char getContinueGame() const {return continueGame;}
		// Others
	  void playRoulette();
		void displayBoard();
		void displayRoulette();
		void displayOptions();
		void spinRoulette();
		void displayBets();
		bool validateBet(string bet);
		void checkForWinner(string bet, unsigned int amount);
		void printInstructions();

	private:
		string betTypes[10];
		unsigned int betAmounts[10];
	  int spinShift;
		char continueGame;
		Number winningNum;
		Player *address;
};

#endif;