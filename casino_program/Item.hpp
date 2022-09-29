/*
Author: Edgar Hernandez
Other Contributors: N/A
Last Modified: 5/14/2022
Description: This class represents an Item in a Food Menu,
            It also contains functions that assist in processing
            a order as it would be in a restaurant.
*/
#ifndef ITEM_H
#define ITEM_H

#include "Player.hpp"
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

class Item
{
  public:
    // Constructors
    Item();
    Item(string name, string description, double cost);

    // Setters
    void setName(string name) {this->name = name;}
    void setDescription(string description) {this->description = description;}
    void setCost(double cost);

    // Getters
    string getName()const {return this->name;}
    string getDescription()const {return this->description;}
    double getCost()const {return this->cost;}

    // Overloaded Operator
    friend ostream& operator << (ostream& out, const Item& item);

  private:
    string name, description;
    double cost;
};

// Functions defined in the implementation file
void printItemArray(Item item[], int amount);
string lowerString(string s);
bool checkItem(Item ites[], int amount, string check, Item& chosenItem);

#endif