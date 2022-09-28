#include "NumberGuess.hpp"
#include <cctype>

NumberGuess::NumberGuess() {
  setAmount(0);
  setBet(0);
  setGuess(0);
}
NumberGuess::NumberGuess(int amount, int bet, int guess) {
  setAmount(amount);
  setBet(bet);
  setGuess(guess);
}

void NumberGuess::display(Player& user) {
  cout << "=========================\n";
  cout << "Current Amount: " << user.getChips();
  cout << "\n=========================\n";
}


void NumberGuess::runNumberGuess(Player& user) {
  cout << "\t\t\t\t  Number Guess Game\n\n";
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
       << "\t\t\t\t\tInstructions\n"
       << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
       << "1. Enter a bet\n"
       << "2. Guess a number between 1 through 10\n"
       << "3. Guess correctly and win the betting amount (or lose it)\n"
       << "4. Be prepared for quadruple or nothing\n"
       << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  char cont;
  cout << "Enter C to continue: ";
  cin >> cont;
  while(toupper(cont) != 'C') {
    cout << "That is an invalid option.\nPlease enter C to continue: ";
    cin >> cont;
  }
  cout << u8"\033[2J\033[1;1H";

	amount = user.getChips();
  char choice;
  int winCount = 0;
  bool isActivated = false;
  
  NumberGuess game;
	game.setAmount(user.getChips());

  regularMatch(user, choice, game, winCount, isActivated); // runs game
}

void NumberGuess::regularMatch(Player& user, char choice, NumberGuess game, int winCount,
                  bool isActivated) {
  do {
    int randNum, inputB, inputC;
		cout << user << endl;
    // random number generator (1-10)
    srand(time(NULL));
    randNum = rand() % 10 + 1;
		
    if (isActivated == true) { //////// Double or Nothing
      if (game.getAmount() == 0) {
        choice = 'N';
      }
      
      cout << "Enter a guess (1-10): ";
      cin >> inputC;

      // checks that guess is within 1-10
      while (inputC > 10 || inputC < 1) {
        cout << "You entered an invalid number!\n\nPlease enter a number "
                "between 1-10: ";
        cin >> inputC;
      }
			game.setGuess(inputC);

      // quadruples amount
      if (game.getGuess() == randNum) {
        cout << "Congratulations, you won quadruple!" << endl;
				user.setNetBalance(user.getNetBalance() + 3*game.getAmount());
        game.setAmount(4*game.getAmount() );
        user.setChips(game.getAmount());
        cout << "The winning number was: " << randNum << endl;
        cout << "You entered: " << inputC << endl << endl;
        game.display(user);
      }
      // set amount to 0 chips
      else {
        cout << "You lost " << game.getAmount() << " chips" << endl;
        cout << "The winning number was: " << randNum << endl;
        cout << "You entered: " << inputC << endl << endl;
				user.setNetBalance(user.getNetBalance() - game.getAmount());
        game.setAmount(game.getAmount() - game.getAmount());
        user.setChips(game.getAmount());
				game.display(user);
        choice = 'n';
      }
    } else if (isActivated == false) { ////////////// Regular Match
      // bet
      cout << "Enter a bet amount: ";
      cin >> inputB;
      cout << endl;
      
      // checks that bet is within 1 and current amount
      while (inputB > user.getChips() || inputB < 1) {
        cout << "You entered an invalid bet!\n\nPlease enter a bet greater "
                "than 0 and less than or equal to "
             << game.getAmount() << "\nEnter bet: ";
        cin >> inputB;
				cout << endl;
      }
      game.setBet(inputB);
			user.setChips(user.getChips() - game.getBet());
      // User Guess
      cout << "Enter a guess (1-10): ";
      cin >> inputC;
      

      // checks that guess is within 1-10
      while (inputC > 10 || inputC < 1) {
        cout << "\nYou entered an invalid number!\n\nPlease enter a number "
                "between 1-10: ";
        cin >> inputC;
				cout << endl;
      }
			cout << u8"\033[2J\033[1;1H";
      game.setGuess(inputC);

      // adds the bet amount when user guesses correctly
      if (game.getGuess() == randNum) {
        cout << "Congratulations, you won " << 2*game.getBet() << " chips" << endl;
        cout << "The winning number was: " << randNum << endl;
        cout << "You entered: " << inputC << endl << endl;
        game.setAmount(game.getAmount() + game.getBet());
				user.setChips(game.getAmount());
				user.setNetBalance(user.getNetBalance() + game.getBet());
        winCount += 1;
        game.display(user);
      }
      // subtracts the bet amount when user guesses correctly
      else {
        cout << "You lost " << game.getBet() << " chips" << endl;
        cout << "The winning number was: " << randNum << endl;
        cout << "You entered: " << inputC << endl << endl;
        game.setAmount(game.getAmount() - game.getBet());
        user.setChips(game.getAmount());
				user.setNetBalance(user.getNetBalance() - game.getBet());
        game.display(user);
      }
    }

    cout << "\nTry again? (y/n): ";
    cin >> choice;
    cout << u8"\033[2J\033[1;1H";

    // checks if the user has money to play
    if (game.getAmount() == 0) {
      isActivated = false;
      choice = 'n';
    } else if (winCount >= 2 &&
               toupper(choice) != 'N') { // Activates quadruple or nothing
      cout << "It's time for quadruple or nothing!\n\nDo you wish to proceed? "
              "(y/n): ";
      cin >> choice;
      isActivated = true;
      cout << u8"\033[2J\033[1;1H";
    }

  } while ((toupper(choice) != 'N'));

  // if user has no more money, the user cannot play anymore
  if (game.getAmount() == 0) {
    cout << "Sorry, you do not have the money to play this game...Get more "
            "cash/chips from "
            "the cashier to play this game again...\n\n";
  } else {
    cout << "Thank you for playing the Number Guessing game!\nEnjoy your "
            "time at the casino!\n\n";
  }
}