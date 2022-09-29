/*
	Author: Carlos Santiago Pacheco
	Other Contributors: Oswaldo Cortes
	Last Modified: 5-14-2022
	Desciption: This class has the necessary funtion prototypes
  to simulate a cashier that will be in charge for the
	transactions of the player like getting more cash through an
	ATM, converting chips to cash, and cash to chips.
*/
#ifndef CASHIER_H
#define CASHIER_H
#include "Player.hpp"
using namespace std;

class Cashier
{
  public:
    Cashier();
		Cashier(Player& user);
    // Setters
    void setChips(int chips);
    void setCash(double cash);
    // Getters
    int getChips()const {return chips;}
    double getCash()const {return cash;}
    // Other
    void mainMoneyDisplay();
  private:
		Player *address;
    int chips;
    double cash;
};
#endif