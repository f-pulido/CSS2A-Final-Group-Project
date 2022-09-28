/*
	Author: Carlos Santiago Pacheco
	Other Contributors: Oswaldo Cortes
	Last Modified: 5-14-2022
	Desciption: This class has the necessary implementation code
  to simulate a cashier that will be in charge for the
	transactions of the player like getting more cash through an
	ATM, converting chips to cash, and cash to chips.
*/
#include "Cashier.hpp"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

Cashier::Cashier()
{
  chips = 0;
  cash = 0;
}
Cashier::Cashier(Player& user)
{
	address = &user;
  setCash(user.getBalance());
  setChips(user.getChips());
}
void Cashier::setChips(int chips)
{
  assert(chips >= 0);
  this->chips = chips;
}
void Cashier::setCash(double cash)
{
  assert(cash >= 0);
  this->cash = cash;
}
void Cashier::mainMoneyDisplay()
{
  double amountWanted;
  char choice;
  char option;
	// The loop allows the user to keep making transactions as long
	// as they would like to.
  do{
		cash = address->getBalance();
		chips = address->getChips();
		// Displays the account information and transaction options
    cout << "Welcome to the Panther Casino!\n";
		cout << *address << endl;
    cout << "Would you like to \n1) Exchange Money for Chips\n2) Exchange chips for money\n3) Access the ATM to get more cash\n4) Exit\n\n";
    cin >> option;
		// Checks if the transaction option is valid.
		while(!(option >= 49 && option <= 52))
		{
			cout << "That was not an option. Please try again\n";
			cin >> option;
		}
		cout << u8"\033[2J\033[1;1H";
		// Exchange money for chips
    if (option == '1')
    {
			cout << *address << endl;
      cout << "How much money would you like to exchange?\n";
      cin >> amountWanted;
			while(amountWanted > cash)
			{
				cout << "You don't have that much money. Double check the value and try again\n";
				cin >> amountWanted;
			}
			// Sets variables in Player equal to the transaction made
      cash -= static_cast<int>(amountWanted);
			address->setBalance(cash);
      chips += static_cast<int>(amountWanted);
			address->setChips(chips);
      cout << "Cash: $" << cash << endl;
      cout << "Chips: " << chips << endl;
      
      cout << "Do you want to make another transaction? (y/n)\n";
      cin >> choice;
			cout << u8"\033[2J\033[1;1H";
    }
		// Exchange chips for money
    else if (option == '2')
    {
			cout << *address << endl;
      cout << "How many chips would you like in cash?\n";
      cin >> amountWanted;
			while(amountWanted > chips)
			{
				cout << "You don't have that many chips. Double check the value and try again\n";
				cin >> amountWanted;
			}
			// Sets variables in Player equal to the transaction
      cash += static_cast<int>(amountWanted);
			address->setBalance(cash);
      chips -= static_cast<int>(amountWanted);
			address->setChips(chips);

      cout << "Cash: $" << cash << endl;
      cout << "Chips: " << chips << endl;
      
      cout << "Do you want to make another transaction? (y/n)\n";
      cin >> choice; 
			cout << u8"\033[2J\033[1;1H";
    }
		// ATM to get more cash
    else if (option == '3')
    {
			cout << *address << endl;
      cout << "How much money would you like to take out?\n";
      cin >> amountWanted;
      cash += amountWanted;
			address->setBalance(cash);

      cout << "Cash: $" << cash << endl;
      cout << "Do you want to make another transaction? (y/n)\n";
      cin >> choice;
			cout << u8"\033[2J\033[1;1H";
    }
		else if (option == '4')
		{
			choice = 'n';
			cout << u8"\033[2J\033[1;1H";
		}
  }while (choice != 'n');

}