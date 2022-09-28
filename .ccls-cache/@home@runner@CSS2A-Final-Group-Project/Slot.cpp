#include "Slot.hpp"
#include <cassert>

Slot::Slot() {
  setName("");
  setCost(0.00);
}
Slot::Slot(string name, double cost) {
  setName(name);
  setCost(cost);
}
void Slot::setCost(double cost) {
  assert(cost >= 0);
  this->cost = cost;
}
void Slot::display() { cout << name << " ($" << cost << ")"; }