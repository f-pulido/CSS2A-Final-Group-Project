/*
Authors: Carlos, Fernando,
         Edgar, Oswaldo
Status: Functional
Bugs: Not that we now of.
*/

#include "Cashier.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Roulette.hpp"
#include "Vending.hpp"
#include "NumberGuess.hpp"
#include "BlackJack.hpp"


#include <iostream>
#include <string>

using namespace std;

void printMainMenu(char& choice, Player one);
void printGameOptions(char& choice, Player one);
void printFoodOptions(char& choice, Player one);

// Constants for Item arrays
const int BURGERS_AMOUNT = 3;
const int FRIES_AMOUNT = 2;
const int BEVERAGES_AMOUNT = 6;
const int MAX_AMOUNT = 100;

// Struct for restaurant menu
struct Menu
{
  Item burgers[BURGERS_AMOUNT] = {
    Item("Hamburger", 
         "Beef - Onions - Lettuce - Spread - Tomatoes - 390 cal", 
         4.00), 
    Item("Cheeseburger", 
         "Cheese - Beef - Onions - Lettuce - Spread - Tomatoes - 480 cal", 
         4.25), 
    Item("Double-Double", 
         "2 Cheese - 2 Beefs - Onions - Lettuce - Spread - Tomatoes - 670 cal", 
         5.50)};
  Item fries[FRIES_AMOUNT] = {
    Item("French Fries", 
         "Cut Potatoes - 370 cal", 
         2.95),
    Item("Animal Fries", 
         "Cut Potaotes - Cheese - Spread - Grilled Onions - 470 cal", 
         3.50)};
  Item beverages[BEVERAGES_AMOUNT] = {
    Item("Pepsi", "12 oz - 150 cal", 2.00),
    Item("Sprite", "12 oz - 146 cal", 2.00),
    Item("Orange Juice", "12 oz - 120 cal", 1.50),
    Item("Apple Juice", "12 oz - 110 cal", 1.50),
    Item("Lemonade", "16 oz - 220 cal", 2.50),
    Item("Pink Lemonade", "16 oz - 240 cal", 2.50)};
};

// Functions used in restaurant
void runRestaurant(Player& one, Menu m);
void printFoodMenu(Menu m);

int main()
{
  Player player;
  player.signUp();

	Cashier transaction(player);
  char mainMenuChoice, foodOptionsChoice, gameOptionsChoice;

  // Set currency format
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  do{
    printMainMenu(mainMenuChoice, player);
    
    switch(mainMenuChoice)
    {
      case('c'):
			{
				transaction.mainMoneyDisplay();
				break;
			}
      
      case('g'):
				while(player.getChips() == 0)
				{
					transaction.mainMoneyDisplay();
				}
        
        do{
          printGameOptions(gameOptionsChoice, player);
          switch(gameOptionsChoice)
          {
            case('r'):
						{
							while(player.getChips() == 0)
							{
								cout << "You need at least 1 chip to play the game.\n" << endl;
								transaction.mainMoneyDisplay();
							}
							char playAgain = 'y';
							cin.ignore();
							Roulette roulette(player);
							roulette.printInstructions();
							while(tolower(playAgain) == 'y')
							{
								while(player.getChips() == 0)
								{
									transaction.mainMoneyDisplay();
								}
								cin.ignore();
								roulette.playRoulette();
								playAgain = roulette.getContinueGame();
							}
              break;
						}
            
            case('b'):
						{
							while(player.getChips() == 0)
							{
								cout << "You need at least 1 chip to play the game.\n" << endl;
								transaction.mainMoneyDisplay();
							}
              Card bj;
							char playerChoice;
              do
                {
            			cout << player << endl;
                  bj.printBJGame(player);
            			cout << "\nWould you like to play again?\n" << endl;
            			cin >> playerChoice;
            			if(player.getChips() == 0)
            			{
										char moreCash;
            				cout << "\nYou don't have chips left. Go to the cashier\n";
	            			cout << "\nEnter C to continue to the cashier: ";
										cin >> moreCash;
										cin.ignore();
                    cout<< u8"\033[2J\033[1;1H";
										transaction.mainMoneyDisplay();	
									}
									cout<< u8"\033[2J\033[1;1H";
                  
                }while (toupper(playerChoice) == 'Y');
              break;
						}
            
            case('g'):
						{
							while(player.getChips() == 0)
							{
								cout << "You need at least 1 chip to play the game.\n" << endl;
								transaction.mainMoneyDisplay();
							}
							NumberGuess j;
							j.runNumberGuess(player);
							break;
						}
              
            case('e'):
              break;
            
            default:
              cout << "Invalid option, try again." << endl;
              break;
          }
        } while(gameOptionsChoice != 'e');
        break;
      
      case('f'):
			{
        do{
          printFoodOptions(foodOptionsChoice, player);
          switch(foodOptionsChoice)
          {
            case('v'):
						{ 
							VendingMachine food;
							food.purchaseFood(player);
              break;
						}
            case('r'):
						{
                Menu menu;
                runRestaurant(player, menu);
                break;
						}
            case('e'):
              break;
            
            default:
              cout << "Invalid option, try again." << endl;
          }
        } while(foodOptionsChoice != 'e');
			}
        break;
      
      case('e'):
        break;
      
      default:
        cout << "Invalid option, try again" << endl;
        break;
    }
  } while(mainMenuChoice != 'e');
  
  cout << u8"\033[2J\033[1;1H";
  cout << "Exiting Program...";
	return 0;
}

void printMainMenu(char& choice, Player one)
{
  cout << one;
  cout << "\n\n\t\tMain Menu" << endl;
  cout << "-------------------------" << endl;
  cout << "[C] Cashier" << endl;
  cout << "[G] Games" << endl;
  cout << "[F] Food" << endl;
  cout << "[E] Exit" << endl;
  cout << "Hello, " << one.getUsername() << endl;
  cout << "Enter one of the options: ";
  cin >> choice;
  choice = tolower(choice);
  // after user selects option from main menu
  // we clear the screen again.
  cout << u8"\033[2J\033[1;1H";
}

void printGameOptions(char& choice, Player one)
{
	cout << one << endl << endl;
  cout << "\t\tGame Options" << endl;
  cout << "----------------------------" << endl;
  cout << "[R] Roulette" << endl;
  cout << "[B] Black Jack" << endl;
  cout << "[G] Guess (1-10)" << endl;
	cout << "[E] Exit" << endl;
  cout << "Enter one of the options: ";
  cin >> choice;
  choice = tolower(choice);
  // after taking in user input, clear the screen
  cout << u8"\033[2J\033[1;1H";
}

void printFoodOptions(char& choice, Player one)
{
  cout << one << endl << endl;
  cout << "\t\tFood Options" << endl;
  cout << "----------------------------" << endl;
  cout << "[V] Vending Machine" << endl;
  cout << "[R] Restaurant" << endl;
  cout << "[E] Exit" << endl;
  cout << "Enter one of the options: ";
  cin >> choice;
  choice = tolower(choice);
  // after taking in user input, clear the screen
  cout << u8"\033[2J\033[1;1H";
}

// Function used in restaurant
void runRestaurant(Player& one, Menu menu)
{
  Item receipt[MAX_AMOUNT];
  Item chosenItem;
  int orderedItems = 0;
  double total = 0.0, payment, change;
  char choice, mainChoice;
  string userItem;
  bool hasPayed;

  do
  {
    cout << one << endl << endl;
    cout << "\t\tOptions" << endl;
    cout << "-----------------------" << endl;
    cout << "[O] Order" << endl;
    cout << "[E] Exit" << endl;
    cout << "Enter one of the options: ";
    cin >> mainChoice;
    cin.ignore();
    mainChoice = tolower(mainChoice);
    cout << u8"\033[2J\033[1;1H";

    switch(mainChoice)
    {
      case('o'):
        cout << "\n\n\nWelcome to Edgar's Restaurant!" << endl;
        cout << "To order, please refer to our menu." << endl;
        printFoodMenu(menu);

        // re-initialize variables to order again
        choice = 'a';
        hasPayed = false;
        orderedItems = 0;
        total = 0;
        
        do
        {
          // When order begins, the first choice is always 'a'.
          switch(choice)
          {
            case('a'):
              cout << "Enter the item (*) name you would like to order" << endl;
              getline(cin, userItem);
              
              if((checkItem(menu.burgers, BURGERS_AMOUNT, userItem, chosenItem)) || 
                (checkItem(menu.fries, FRIES_AMOUNT, userItem, chosenItem)) || 
                (checkItem(menu.beverages, BEVERAGES_AMOUNT, userItem, chosenItem)))
              {
                receipt[orderedItems] = chosenItem;
                orderedItems++;
                total += chosenItem.getCost();
								cout << "\n-----------------------------------------------------------";
                cout << "\nYour Order (Total: $" << total << ")\n\n";
                printItemArray(receipt, orderedItems);
              }
              else
              {
                cout << "Item is not in menu, please try again" << endl;
              }
              break;
            
            case('m'):
              printFoodMenu(menu);
              break;
      
            case('p'):
              cout << u8"\033[2J\033[1;1H";
              cout << one << endl << endl;
              cout << "Order Total: $" << total << endl;
              cout << "Enter Payment Amount: $";
              cin >> payment;
              
              if(one.getBalance() > payment && payment >= total)
              {
                change = payment - total;
                cout << "Your change is: $" << change << endl;
                cout << "Enjoy your food! :)\n\n\n";
                one.setBalance((one.getBalance() - payment) + change);
								char next;
								cout << "Enter C to contiue: ";
								cin >> next;
								cin.ignore();
								cout << u8"\033[2J\033[1;1H";
              }
              else
              {
                cout << "\nPayment failed, you could visit the" << endl;
                cout << "cashier where there is an ATM.\n\n";
								char next;
								cout << "Enter C to contiue: ";
								cin >> next;
								cin.ignore();
								cout << u8"\033[2J\033[1;1H";
              }
              hasPayed = true;
              break;
      
            default:
              cout << "Invalid option, try again." << endl;
              break;
          }
      
          if(!hasPayed)
          {
            cout << "\n\t\tOptions" << endl;
            cout << "-----------------------" << endl;
            cout << "[A] - Add Item To Order" << endl;
            cout << "[M] - Display Menu Again" << endl;
            cout << "[P] - Pay Order" << endl;
            cout << "Type your option: ";
            cin >> choice;
            cin.ignore();
            choice = tolower(choice);
            cout << endl;
          }
          else
          {
            choice = 'r';
          }
        } while(choice != 'r');
        break;
      
      case('e'):
        break;
      
      default:
        cout << "Invalid option, try again." << endl;
      }
  } while(mainChoice != 'e');
}

// Function used in restaurant.
void printFoodMenu(Menu m)
{
  cout << "\nThe Menu\n\n";
  cout << "\nBurgers\n\n";
  printItemArray(m.burgers, BURGERS_AMOUNT);
  cout << "\nFries\n\n";
  printItemArray(m.fries, FRIES_AMOUNT);
  cout << "\nBeverages\n\n";
  printItemArray(m.beverages, BEVERAGES_AMOUNT);
}