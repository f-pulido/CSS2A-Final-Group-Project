#include "Number.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>

Number::Number()
{
	color = "";
	number = 0;
}
Number::Number(unsigned int number, string color)
{
	setColor(color);
	setNumber(number);
}
void Number::setNumber(unsigned int number)
{
	assert(number >= 0);
	this->number = number;
}
ostream& operator << (ostream& out, const Number& num)
{
	if(num.color == "red")
	{
		out << "\033[0;31m";
		out << setw(4) << num.number;
		return out;
	}
	else if(num.color == "green")
	{
		out << "\033[0;32m";
		out << setw(4) << num.number;
		
		return out;
	}
	else
	{
		out << "\033[0;37m";
		out << setw(4) << num.number;
		return out;
	}
}