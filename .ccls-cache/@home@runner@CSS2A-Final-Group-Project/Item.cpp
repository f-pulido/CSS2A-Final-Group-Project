#include "Item.hpp"

Item::Item()
{
  setName("");
  setDescription("");
  setCost(0);
}

Item::Item(string name, string description, double cost)
{
  setName(name);
  setDescription(description);
  setCost(cost);
}

void Item::setCost(double cost)
{
  assert(cost >= 0);
  this->cost = cost;
}

ostream& operator << (ostream& out, const Item& item)
{
  out << "(*) " << item.getName() << endl;
  out << item.getDescription() << endl;
  out << "Cost: $" << item.getCost() << endl;
  out << endl;
  return out;
}

// Functions used in runRestaurant and without
// being members of Item::
void printItemArray(Item item[], int amount)
{
  for(int i = 0; i < amount; i++)
  {
    cout << item[i];
  }
}

// Changes all characters in string to lowercase
string lowerString(string s)
{
  for(int i = 0; i < s.length(); i++)
  {
    s[i] = tolower(s[i]);
  }
  return s;
}

bool checkItem(Item item[], int amount, string check, Item& chosenItem)
{
  string lowerItem;
  for(int i = 0; i < amount; i++)
  {
    check = lowerString(check);
    lowerItem = lowerString(item[i].getName());
    if(check == lowerItem)
    {
      chosenItem = item[i];
      return true;
    }
  }
  return false;
}