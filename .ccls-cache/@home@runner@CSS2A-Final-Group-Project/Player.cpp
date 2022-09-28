#include "Player.hpp"

Player::Player()
{
  setUsername("");
  setBalance(0.0);
  setNetBalance(0);
  setChips(0);
}

Player::Player(string username, double balance, int net_balance, int chips)
{
  setUsername(username);
  setBalance(balance);
  setNetBalance(net_balance);
  setChips(chips);
}

void Player::setUsername(string username)
{
  bool hasSpace = false;
  for(int i = 0; i < username.length(); i++)
  {
    if(username[i] == ' ')
    {
      hasSpace = true;
    }
  }
  assert(!hasSpace);
  this->username = username;
}

void Player::setBalance(double balance)
{
  assert(balance >= 0);
  this->balance = balance;
}

void Player::setChips(int chips)
{
  assert(chips >= 0);
  this->chips = chips;
}

void Player::signUp()
{
  cout << "Welcome to the Panther Casino!" << endl;
  cout << "To play you will need to sign up!\n\n";
  cout << "\t\tAccount Sign Up" << endl;
  cout << "-------------------------------" << endl;
  cout << "Username: ";
  getline(cin, username);
  cout << "Starting Balance: ";
  cin >> balance;
  // Comand to clear the console
  cout << u8"\033[2J\033[1;1H";
}

ostream& operator << (ostream& out, Player& user)
{
  out << "\t\tAccount Information" << endl;
  out << "-----------------------------------" << endl;
  out << "Username: " << user.getUsername() << endl;
  out << "Balance: $" << user.getBalance() << endl;
  out << "Chips: " << user.getChips() << endl;
	out << "Net Balance: $" << user.getNetBalance() << endl;
  return out;
}