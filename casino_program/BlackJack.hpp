/*
Author: Carlos Santiago
Other Contributors: Fernando Pulido, Oswaldo Cortes, Edgar Hernandez
Last Modified: 5/14/2022
Description: This is the game of black jack. You must stay under or equal to 21 and beat the dealer or hope he goes over 21. It is a short and fun game that you can play for multiple rounds. 
*/
#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Player.hpp"
#include <iostream>
using namespace std;

class Card
{
  public:
    Card();
    Card(string faceValue, string suit, int value);
    // Getters
    string getFaceValue()const{return this->faceValue;}
    int getValue()const{return this->value;}
    string getSuit()const{return this->suit;}
    // Setters
    void setSuit(string suit);
    void setValue(int value);
    void setFaceValue(string faceValue);
    // Other
    void print()const;
    // void printBJGame();
    void printBJGame(Player& user);

  private:
    // Values
    string suit, faceValue;
    int value;
};

#endif