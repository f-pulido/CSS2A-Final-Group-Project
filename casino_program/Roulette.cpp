/*
	Author: Oswaldo Cortes
	Other Contributors: N/A
	Last Modified: 5-14-2022
	Desciption: This class has the necessary implementation code
  to simulate a game of roulette. It includes code that takes, 
  tracks, and validates the bets, chips of the player, chips bet,
	and net balance.
*/
#include "Roulette.hpp"

// The numbers that will be displayed in the roulette
Number Roulette::rouletteNums[37] =
																			{Number(0, "green"), Number(32, "red"), Number(15, "white"), Number(19, "red"), Number(4, "white"), Number(21, "red"),
																			Number(2, "white"), Number(25, "red"), Number(17, "white"), Number(34, "red"), Number(6, "white"), Number(27, "red"),
																			Number(13, "white"), Number(36, "red"), Number(11, "white"), Number(30, "red"), Number(8, "white"), Number(23, "red"),
																			Number(10, "white"), Number(5, "red"), Number(24, "white"), Number(16, "red"), Number(33, "white"), Number(1, "red"),
																			Number(20, "white"), Number(14, "red"), Number(31, "white"), Number(9, "red"), Number(22, "white"), Number(18, "red"),
																			Number(29, "white"), Number(7, "red"), Number(28, "white"), Number(12, "red"), Number(35, "white"), Number(3, "red"),
																			Number(26, "white")};
Roulette::Roulette(Player& user)
{
	spinShift = 0;
  winningNum = rouletteNums[0];
	setContinueGame('y');
	// this part gets the address of the user to use a form of pass by reference in the class.
	address = &user; 
}

void Roulette::setSpinShift(int num)
{
	assert(num >= 0);
	spinShift = num;
}

void Roulette::playRoulette()
{
	char continuePlaying = ' ';
	srand(time(NULL));
	do
	{
		cout << *address;
		displayBoard();
		// Spins the roulette to land on random place
		setSpinShift(rand() % 38);
		setBets();
		spinRoulette();
		displayRoulette();
		cout << "\n---------------------------------------------------------------------" << endl;
		cout << "Results:\n" << endl;
		// When 0 it displays all outside bets loose. 
		if(winningNum.getNumber() == 0)
		{
			cout << setw(46) << "*ALL OUTSIDE BETS LOOSE*" << endl;
		}
		for(int i = 0; i < 10; i++)
		{
			if(betTypes[i].length() > 0)
			{
				checkForWinner(betTypes[i], betAmounts[i]);
			}
		}
		cout << "---------------------------------------------------------------------\n" << endl;
		// Prints account info
		cout << *address;
		cout << "\nWould you like to continue playing (Y/N): ";
		cin >> continuePlaying;
		// Used in the main to loop until they enter n.
		setContinueGame(continuePlaying);
		// Ignores because the next thing would be a getline if they choose to play again.
		cin.ignore();
		if(tolower(continuePlaying) == 'y')
		{
			cout<< u8"\033[2J\033[1;1H";
			if(address->getChips() == 0)
			{
				// Used as a way to allow the user to proceed by entering somethin.
				char empty;
				cout << "You do not have any chips. Go back to the cashier to get chips." << endl;
				cout << "\nEnter any character to continue: ";
				cin >> empty;
				// Used as a way to allow the user to proceed by entering somethin.
				cin.ignore();
				continuePlaying = 'n';
				cout<< u8"\033[2J\033[1;1H";
			}
		}
		else
		{
			cout << u8"\033[2J\033[1;1H";
		}
	}while(tolower(continuePlaying) == 'y');
	
}

void Roulette::spinRoulette()
{
	for(int i = 1; i <= getSpinShift(); i++)
	{
		Number temp;
		Number replace;
		for(int i = 0; i < 37; i++)
		{
			if(i == 0)
			{
				temp = rouletteNums[i];
				rouletteNums[i] = rouletteNums[36];
			}
			else
			{
				replace = temp;
				temp = rouletteNums[i];
				rouletteNums[i] = replace;
			}
		}
	}
	winningNum = rouletteNums[0];
}

void Roulette::setBets()
{
	char anotherBet = ' ';
	int numBets = 0;
	do{
		cout << " Enter your bet type (Inner or Outer Bets - Max limit 10): ";
		
		getline(cin, betTypes[numBets]);
		while(!validateBet(betTypes[numBets]))
		{
			cout << "\n That is not a valid bet. Please try again: ";
			getline(cin, betTypes[numBets]);
		}
		cout << endl;
		cout << " Enter the amount of chips you wil bet: ";
		cin >> betAmounts[numBets];
		while(betAmounts[numBets] <= 0 || betAmounts[numBets] > 50000 || betAmounts[numBets] > address->getChips())
		{
			cout << "\n That is not a valid amount. Please try again: ";
			cin >> betAmounts[numBets];
		}
		// Subtract bet money from person class
		address->setChips(address->getChips()-static_cast<int>(betAmounts[numBets]));
		numBets++;
		cout << endl;
		if(numBets != 10)
		{
			cout << " Would you like to do another bet? (Y/N): ";
			cin >> anotherBet;
		}
	
		if(tolower(anotherBet) == 'n' || numBets == 10)
		{
			char spin;
			cout << u8"\033[2J\033[1;1H";
			cout << *address;
			displayRoulette();
			cout << "\tYour bets have been placed. Enter 'S' to spin the wheel...";
			cin >> spin;
			if(toupper(spin) == 'S')
			{
				cout<< u8"\033[2J\033[1;1H";
			}
			break;
		}
		cin.ignore();
		cout << endl;
	} while(numBets <= 10 && tolower(anotherBet) == 'y');

	// Sets the remaining indices in array to default values
	for(int i = numBets; i < 10; i++)
	{
		betTypes[i] = "";
		betAmounts[i] = 0;
	}
}

// Display functions
void Roulette::displayBoard()
{
	displayRoulette();
	displayOptions();
}
void Roulette::displayRoulette()
{
	cout << setw(40) << "Winning Number" << endl;
	cout << setw(38) << "⬇️" << setw(12) << endl;
	cout << rouletteNums[31] << setw(6);
	cout << rouletteNums[32] << setw(6);
	cout << rouletteNums[33] << setw(6);
	cout << rouletteNums[34] << setw(6);
	cout << rouletteNums[35] << setw(6);
	cout << rouletteNums[36] << setw(6);
	cout << rouletteNums[0] << setw(6);
	cout << rouletteNums[1] << setw(6);
	cout << rouletteNums[2] << setw(6);
	cout << rouletteNums[3] << setw(6);
	cout << rouletteNums[4] << setw(6);
	cout << rouletteNums[5] << setw(6);
	cout << rouletteNums[6] << endl << setw(12) << endl;
	cout << rouletteNums[30] << setw(2) << "\t\t\t\t\t\t\t\t\t\t\t " << setw(4);
	cout << rouletteNums[7] << endl << setw(12) << endl;
	cout << rouletteNums[29] << setw(2) << "\t\t\t\t\t\t\t\t\t\t\t " << setw(4);
	cout << rouletteNums[8] << endl << setw(12) << endl;
	cout << rouletteNums[28] << setw(2) << "\t\t\t\t\t\t\t\t\t\t\t " << setw(4);
	cout << rouletteNums[9] << endl << setw(12) << endl;
	cout << rouletteNums[27] << setw(2) << "\t\t\t\t\t\t\t\t\t\t\t " << setw(4);
	cout << rouletteNums[10] << endl << setw(12) << endl;
	cout << rouletteNums[26] << setw(2) << "\t\t\t\t\t\t\t\t\t\t\t " << setw(4);
	cout << rouletteNums[11] << endl << setw(12) << endl;
	cout << rouletteNums[25] << setw(2) << "\t\t\t\t\t\t\t\t\t\t\t " << setw(4);
	cout << rouletteNums[12] << endl << setw(12) << endl;
		
	cout << rouletteNums[24] << setw(6);
	cout << rouletteNums[23] << setw(6);
	cout << rouletteNums[22] << setw(6);
	cout << rouletteNums[21] << setw(6);
	cout << rouletteNums[20] << setw(6);
	cout << rouletteNums[19] << setw(11);
	cout << rouletteNums[18] << setw(6);
	cout << rouletteNums[17] << setw(6);
	cout << rouletteNums[16] << setw(6);
	cout << rouletteNums[15] << setw(6);
	cout << rouletteNums[14] << setw(6);
	cout << rouletteNums[13] << endl << endl << endl;
	cout << "\033[0;37m";

}
void Roulette::displayOptions()
{
	cout << setw(35) << "Bets" << endl << endl;
	for(int j = 3; j > 0; j--)
	{
		for(int i = 0; i <= 33; i += 3)
		{
			cout << " |" << j + i << "|"<< setw(2);
		}
		if(j == 3)
		{
			cout << " " << j-2 << "st row" << endl;
		}
		else if(j == 2)
		{
			cout << " " << j << "nd row" << endl;
		}
		else
		{
			cout << " " << j+2 << "rd row" << endl;
		}
	}
	cout << endl;
	cout << " |¯¯¯¯¯¯¯¯¯¯¯¯¯¯| |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯| |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|  |¯¯¯¯¯|" << endl;
	cout << " |    1st 12    | |     2nd 12      | |     3rd 12      |  |     |" << endl;
	cout << " |______________| |_________________| |_________________|  |  0  |" << endl;

	cout << " |¯¯¯¯¯¯|¯¯¯¯¯¯¯| |¯¯¯¯¯¯¯¯|¯¯¯¯¯¯¯¯| |¯¯¯¯¯¯|¯¯¯¯¯¯¯¯¯¯|  |     |" << endl;
	cout << " | 1-18 | EVEN  | |   RED  | WHITE  | | ODD  |  19-36   |  |     |" << endl;
	cout << " |______|_______| |________|________| |______|__________|  |_____|" << endl;
	cout << endl;
}

bool Roulette::validateBet(string bet)
{
	const string possibleBets[49] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
																	"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
																	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
																	"30", "31", "32", "33", "34", "35", "36", "1st 12", "2nd 12",
																	"3rd 12", "1-18", "even", "red", "white", "odd", "19-36",
																	"1st row", "2nd row", "3rd row" };
	for(int i = 0; i < bet.length(); i++)
	{
		bet[i] = tolower(bet[i]);
	}
	for(int i = 0; i < 49; i++)
	{
		if(bet == possibleBets[i])
		{
			return true;
		}
	}
	return false;
}

void Roulette::checkForWinner(string bet, unsigned int amount)
{
	// In all the folllowing code in the function. The address->setters or getters
	// are used to change the player chips and netbalance. Results vary if they win or loose.
	if(winningNum.getColor() == "green")
	{
		if(bet == "0")
		{
			cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 36*amount << " chips" << endl;
			address->setChips(address->getChips()+(36*static_cast<int>(amount)));
			address->setNetBalance(address->getNetBalance()+static_cast<int>(35*amount));
		}
		else
		{
			address->setNetBalance(address->getNetBalance()-static_cast<int>(amount));
		}
	}
	else if(bet.length() <= 2 && stoi(bet) == winningNum.getNumber())
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 36*amount << " chips" << endl;
		address->setChips(address->getChips()+(36*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(35*amount));
	}
	else if(bet == "even" && winningNum.getNumber() % 2 == 0)
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 2*amount << " chips" << endl;
		address->setChips(address->getChips()+(2*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(amount));
	}
	else if(bet == "odd" && winningNum.getNumber() % 2 == 1)
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 2*amount << " chips" << endl;
		address->setChips(address->getChips()+(2*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(amount));
	}
	else if(bet == "1-18" && winningNum.getNumber() <= 18)
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 2*amount << " chips" << endl;
		address->setChips(address->getChips()+(2*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(amount));
	}
	else if(bet == "19-36" && (winningNum.getNumber() <= 36 && winningNum.getNumber() >= 19))
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 2*amount << " chips" << endl;
		address->setChips(address->getChips()+(2*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(amount));
	}
	else if(bet == "1st 12" && winningNum.getNumber() <= 12)
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 3*amount << " chips" << endl;
		address->setChips(address->getChips()+(3*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(2*amount));
	}
	else if(bet == "2nd 12" && (winningNum.getNumber() <= 24 && winningNum.getNumber() >= 13))
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 3*amount << " chips" << endl;
		address->setChips(address->getChips()+(3*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(2*amount));
	}
	else if(bet == "3rd 12" && (winningNum.getNumber() <= 36 && winningNum.getNumber() >= 25))
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 3*amount << " chips" << endl;
		address->setChips(address->getChips()+(3*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(2*amount));
	}
	else if(bet == "1st row")
	{
		for(int i = 3; i <= 36; i+= 3)
		{
			if(i == winningNum.getNumber())
			{
				cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 3*amount << " chips" << endl;
				address->setChips(address->getChips()+(3*static_cast<int>(amount)));
				address->setNetBalance(address->getNetBalance()+static_cast<int>(2*amount));
				break;
			}
		}
	}
	else if(bet == "2nd row")
	{
		for(int i = 2; i <= 36; i+= 3)
		{
			if(i == winningNum.getNumber())
			{
				cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 3*amount << " chips" << endl;
				address->setChips(address->getChips()+(3*static_cast<int>(amount)));
				address->setNetBalance(address->getNetBalance()+static_cast<int>(2*amount));
				break;
			}
		}
	}
	else if(bet == "3rd row")
	{
		for(int i = 1; i <= 36; i+= 3)
		{
			if(i == winningNum.getNumber())
			{
				cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 3*amount << " chips" << endl;
				address->setChips(address->getChips()+(3*static_cast<int>(amount)));
				address->setNetBalance(address->getNetBalance()+static_cast<int>(2*amount));
				break;
			}
		}
	}
	else if(bet == "red" && winningNum.getColor() == "red")
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 2*amount << " chips" << endl;
		address->setChips(address->getChips()+(2*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(amount));
	}
	else if(bet == "white" && winningNum.getColor() == "white")
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Winning Amount: " << 2*amount << " chips" << endl;
		address->setChips(address->getChips()+(2*static_cast<int>(amount)));
		address->setNetBalance(address->getNetBalance()+static_cast<int>(amount));
	}
	else
	{
		cout << "Bet: " << left << setw(10) << bet << " Bet Amount: " << left << setw(10) << amount << right << "Lost Amount: " << amount << " chips" << endl;
		address->setNetBalance(address->getNetBalance()-static_cast<int>(amount));
	}
}
void Roulette::printInstructions()
{
	cout << setw(52) << "Welcome to the Game of Roulette" << endl;
	cout << "\nIn this game you can bet on the odds that a given number"
 			 << " lands in a spin. The values in the roulette range from 0 to 36, where each number has"
		   << " certain characteristics like being even or odd, being low or high numbers, etc. You can"
			 << " make a total of 10 maixmum bets with the maximum betting amount of 50,000 chips. The bets"
			 << " can be either inside bets, which are the individual values and you can win 36 times the amount you bet."
			 << " The other bets are outside bets." << endl;
	
	cout << "\nThe outside bets include:" << endl;
	cout << "- Even numbers            2x Profit" << endl;
	cout << "- Odd numbers             2x Profit" << endl;
	cout << "- High numbers (19-36)    2x Profit" << endl;
	cout << "- Low numbers (1-18)      2x Profit" << endl;
	cout << "- Red numbers             2x Profit" << endl;
	cout << "- White numbers           2x Profit" << endl;
	cout << "- 1st 12 numbers          3x Profit" << endl;
	cout << "- 2nd 12 numbers          3x Profit" << endl;
	cout << "- 3rd 12 numbers          3x Profit" << endl;
	cout << "- 1st row of numbers      3x Profit" << endl;
	cout << "- 2nd row of numbers      3x Profit" << endl;
	cout << "- 3rd row of numbers      3x Profit" << endl;

	cout << "\nNote that when the winning number is 0. All outside bets loose." << endl;

	char gotIt = ' ';
	cout << "\nIf you understand the instructions, enter C to continue: ";
	cin >> gotIt;
	cout<< u8"\033[2J\033[1;1H";

}