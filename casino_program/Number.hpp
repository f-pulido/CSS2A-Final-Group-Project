/*
Author: Oswaldo Cortes
Other Contributors: N/A
Last Modified: 5/14/2022
Description: This class is used in the roulette to make the number
						 datatype to assign colors to the numbers.
*/

#ifndef NUMBER_H
#define NUMBER_H

#include <fstream>
#include <string>
using namespace std;

class Number
{
	public:
		Number();
		Number(unsigned int number, string color);
		// Getters
		string getColor() const {return color;}
		int getNumber() const {return number;}
		// Setters
		void setColor(string color) {this->color = color;}
		void setNumber(unsigned int number);
		// Other
		friend ostream& operator << (ostream& out, const Number& num);
	private:
		string color;
		unsigned int number;
};

#endif