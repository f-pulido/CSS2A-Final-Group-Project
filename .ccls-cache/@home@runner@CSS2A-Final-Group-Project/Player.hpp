/*
Author: Edgar Hernandez
Other Contributors: N/A
Last Modified: 5/14/2022
Description: The Player class is initialized at the
      beginning of the program with the signUp member
      function, its member variables represent the users
      balance, cash, chips, and net_balance throughout 
      the whole casino.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>
#include<cassert>
#include<cctype>

using namespace std;

class Player
{
  public:
    Player();
    Player(string username, double balance, int net_balance, int chips);

    void setUsername(string username);
    void setBalance(double balance);
    void setNetBalance(int net_balance) {this->net_balance = net_balance;}
    void setChips(int chips);

    string getUsername()const {return this->username;}
    double getBalance()const {return this->balance;}
    int getNetBalance()const {return this->net_balance;}
    int getChips()const {return this->chips;}

    void signUp();

    friend ostream& operator << (ostream& out, Player& user);

  private:
    string username;
    double balance;
    int net_balance;
    int chips;
};

#endif