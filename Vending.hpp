/*
	Author: Fernando Pulido
	Other Contributors: Oswaldo Cortes
	Last Modified: 5-14-2022
	Desciption: This class has the necessary function prototypes
  to simulate a vending machine. It mainly displays and does
	transactions.
*/
#ifndef VENDING_H
#define VENDING_H
#include "Player.hpp"
#include "Slot.hpp"

class VendingMachine
{
  public:
    VendingMachine();
    // Getters
    Slot getSlot()const{return slots[4][3];}
    // Other
    void buy(int row, int column, Player& user);
    void slotCheck(int row, int column, Player& user);
    void displayItems();
		void purchaseFood(Player& user);
  private:
    Slot slots[4][3];
};

#endif