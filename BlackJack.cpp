#include "BlackJack.hpp"
#include <iostream>
#include <ctime>//randnum
#include <cstdlib>//randnum
#include <cassert>
#include <string>
using namespace std;

Card::Card()
{
  suit = "Spades";
  value = 1;
  faceValue = "A";
}
Card::Card(string faceValue, string suit, int value) 
{
  setFaceValue(faceValue);
  setSuit(suit);
  setValue(value);
}

// Setter Functions
void Card::setSuit(string suit)
{
  assert(suit == "Spades" || suit == "Hearts" || suit == "Diamonds" || suit == "Clubs");
  this->suit = suit;
}
void Card::setValue(int value)
{
  assert(value >= 1 && value <= 11); 
  this->value = value; 
}
void Card::setFaceValue(string faceValue)
{
  assert(toupper(faceValue == "A") || faceValue == "2" || faceValue == "3" || 
          faceValue == "4" || faceValue == "5" || faceValue == "6" ||
          faceValue == "7" || faceValue == "8" || faceValue == "9" || 
          faceValue == "10" || toupper(faceValue == "J") || 
          toupper(faceValue == "Q") ||toupper(faceValue == "K"));
  this->faceValue = faceValue;
}
void Card::print()const
{
  cout << faceValue << " of " << suit << endl;
}

  const Card CARD_FACES[13] = {Card("A", "Spades", 1),  Card("2", "Spades", 2), Card("3", "Spades", 3), Card("4", "Spades", 4), Card("5", "Spades", 5), Card("6", "Spades", 6), Card("7", "Spades", 7), Card("8", "Spades", 8), Card("9", "Spades", 9), Card("10", "Spades", 10), Card("J", "Spades", 10), Card("Q", "Spades", 10), Card("K", "Spades", 10)};

  const string SUITS[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
  
  void initArray(Card cards[], int size);
  void drawCard();


void Card::printBJGame(Player& user)
{
  
  int random, aceNum, count = 0, amount = 0;
  int aceValue;
  int dealerNum;
  Card cardsArr[52];
  Card tempCard;
  char choice;

  int playerBet;

  srand(time(0));
  initArray(cardsArr, 52);
  for (int i = 0; i < 52; i++)
    {
      tempCard = cardsArr[i];
      random = rand() % 51 + 1;
      cardsArr[i] = cardsArr[random];
      cardsArr[random] = tempCard;
    }
 
  cout << "\t\t\t\t  Black Jack \n\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
       << "\t\t\t\t\tRules\n"
       << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
       << "1. Get as close to 21 without going over\n"
       << "2. Beat the dealer by getting a number bigger than him\n"
       << "   You can also hope the dealer goes over 21\n"
       << "3. The dealer must have at least 17\n"
       << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  
  cout << "\n" << endl;
  cout << "How much would you like to bet?\n";
	cin >> playerBet;
	while(playerBet <= 0 || playerBet > user.getChips())
	{
		cout << "That is not a valid amount. Try again: ";
		cin >> playerBet;
	}
  user.setChips(user.getChips() - playerBet);
  cout << "\n\nYour cards are:\n";
  
  do
  {
    
    if (count == 0)
    {
      for (int i = 0; i < 1; i++)
        {
          // In case the first two cards are an Ace
          if (cardsArr[0].getFaceValue() == "A")
          {
            cardsArr[0].print();
            cout << "What value would you like the Ace to have? (1/11)\n";
            cin >> aceValue;
            while (aceValue != 1 && aceValue != 11)
              {
                cout << "That is not a valid numer. Try again: ";
                cin >> aceValue;
              }
            amount += aceValue;
          }
          else if (cardsArr[0].getFaceValue() != "A")
          {
            cardsArr[0].print();
            amount += cardsArr[0].getValue();
          }

          if (cardsArr[1].getFaceValue() == "A")
          {
            cardsArr[1].print();
            cout << "What value would you like the Ace to have? (1/11)\n";
            cin >> aceValue;
            while (aceValue != 1 && aceValue != 11)
              {
                cout << "That is not a valid numer. Try again: ";
                cin >> aceValue;
              }
            amount += aceValue;
          }
            else if (cardsArr[1].getFaceValue() != "A")
          {
            cardsArr[1].print();
            amount += cardsArr[1].getValue();
          }
          
        }
      count = 2;
    }
    else if (count > 0)
    {
      // In case any other card is an Ace
      if (cardsArr[count].getFaceValue() == "A")
        {
          cardsArr[count].print();
          cout << "What value would you like the Ace to have? (1/11)\n";
          cin >> aceValue;
          while (aceValue != 1 && aceValue != 11)
              {
                cout << "That is not a valid numer. Try again: ";
                cin >> aceValue;
              }
          amount += aceValue;
        }
      // Any card other than an Ace
      else if (cardsArr[count].getFaceValue() != "A")
      {
        cardsArr[count].print();
        amount += cardsArr[count].getValue(); 
        count++;
      }
      
    }

    cout << "Would you like another card?\n";
		cin >> choice;
    
  }while(tolower(choice) == 'y');
  cout << endl;
  cout << "Number of cards: " << count << endl;
  cout << "Total amount: " << amount << endl;

  
    srand(time(NULL));  // Initialize random number generator.
    dealerNum = rand()%9+17;

  if (amount > 0 && dealerNum > 0)
  {
    if (amount <= 21 && dealerNum <= 21 && amount > dealerNum)
    {
      cout << "Dealer Num: " << dealerNum << endl;
			cout << "You win! \tYou remained below 21 and beat the dealer\n";
      user.setChips(user.getChips() + playerBet*2);
      user.setNetBalance(user.getNetBalance() + playerBet);
    } 
    else if (amount <= 21 && dealerNum > 21 )
    {
      cout << "Dealer Num: " << dealerNum << endl;
			cout << "You win! \tYou remained below 21 the dealer busted\n";
      user.setChips(user.getChips() + playerBet*2);
      user.setNetBalance(user.getNetBalance() + playerBet);
    } 
    else if (amount == dealerNum && amount <= 21)
    {
      cout << "Dealer Number: " << dealerNum << endl;
			cout << "Push! You have the same amount as the dealer \n";
      user.setChips(user.getChips() + playerBet);
    }
    else if (amount < dealerNum && dealerNum <= 21)
    {
      cout << "You lose!" << "\nDealer Number: " << dealerNum << endl;
      user.setNetBalance(user.getNetBalance() - playerBet);
    }
    else if (amount > 21)
    {
      cout << "Bust! You lose" << endl;
      user.setNetBalance(user.getNetBalance() - playerBet);
    }
  }
  
}


void initArray(Card cards[], int size)
{
    int counter = 0;
    for(int i = 0; i < size; i++)
    {
        if(i >= 0 && i <= 12)
        {
            cards[i] = CARD_FACES[counter % 13];
        }
        else if(i >= 13 && i <= 25)
        {
            cards[i] = CARD_FACES[counter % 13];
            cards[i].setSuit(SUITS[1]);
        }
        else if(i >= 26 && i <= 38)
        {
            cards[i] = CARD_FACES[counter % 13];
            cards[i].setSuit(SUITS[2]);
        }
        else
        {
            cards[i] = CARD_FACES[counter % 13];
            cards[i].setSuit(SUITS[3]);
        }
        counter++;
    }

}