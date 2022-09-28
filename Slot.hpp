/*
Author: Fernando Pulido
Other Contributors: N/A
Last Modified: 5/14/2022
Description: This class is connected to the vending class and allows for the naming and costs of all items in the vending machine
*/

#ifndef SLOT_H
#define SLOT_H

#include <string>
#include <iostream>
#include <cassert>
using namespace std;

class Slot
{
  public:
    Slot();
    Slot(string name, double cost);
    //Getters
    string getName()const{return name;}
    double getCost()const{return cost;}
    //Setters
    void setName(string name){this->name=name;}
    void setCost(double cost);
    //Other
    void display();
  private:
    string name;
    double cost;
};
#endif