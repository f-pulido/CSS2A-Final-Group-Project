/*
	Author: Fernando Pulido
	Other Contributors: Oswaldo Cortes
	Last Modified: 5-14-2022
	Desciption: This class has the necessary implementation code
  to simulate a vending machine. It mainly displays and does
	transactions.
*/
#include "Vending.hpp"

VendingMachine::VendingMachine() {
  slots[0][0] = {"Twix", 1.50};
  slots[0][1] = {"Kit Kat", 1.50};
  slots[0][2] = {"Snickers", 1.50};
  slots[1][0] = {"M&Ms", 1.50};
  slots[1][1] = {"Crunch", 1.00};
  slots[1][2] = {"Reese's", 1.50};
  slots[2][0] = {"Lays", 2.00};
  slots[2][1] = {"Fritos", 2.00};
  slots[2][2] = {"Doritos", 2.50};
  slots[3][0] = {"Coke", 1.50};
  slots[3][1] = {"Sprite", 1.50};
  slots[3][2] = {"Minute Maid", 1.00};
}
void VendingMachine::buy(int row, int column, Player& user) {
  assert(row >= 0 && row <= 3);
  assert(column >= 0 && column <= 2);
  slotCheck(row, column, user);
}
void VendingMachine::displayItems() {
  for (int r = 0; r <= 3; r++) {
    for (int c = 0; c <= 2; c++) {
      cout << "[" << r << "]"
           << "[" << c << "] ";
      slots[r][c].display();
      cout << "\t\t";
    }
    cout << endl;
  }
}

void VendingMachine::purchaseFood(Player& user) {
  int row, column;
  char choice;

  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  do {
    VendingMachine test;
		cout << user << endl << endl;
    cout << "---------------------------------------------------------------\n";
    cout << "Here are our available snacks!\n" << endl;
    test.displayItems();
    cout << "\n---------------------------------------------------------------"
            "\n";
    cout << "\nWhat would you like to purchase? [row][column]\n";
    cout << "Enter Row: ";
    cin >> row;
    cout << "Enter Column: ";
    cin >> column;
    cout << endl;
    test.buy(row, column, user);
    cout << "\nWould you like to buy something else? (y/n): ";	
    cin >> choice;
    cout << endl;
		cout<< u8"\033[2J\033[1;1H";
  } while (tolower(choice) == 'y');
}

void VendingMachine::slotCheck(int row, int column, Player& user) {
  char choice;
  cout << "You picked: ";
  slots[row][column].display();
  cout << "\n\nAre you sure you want to purchase? (y/n): ";
  cin >> choice;
  if (toupper(choice) == 'Y') {
		user.setBalance(user.getBalance()-slots[row][column].getCost());
    cout << "\nYour purchase was complete!\n";
  } else {
    cout << "Cancelled!" << endl;
  }
}