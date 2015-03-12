#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Player.h"
#include "Alien.h"
#include "Encounter.h"

using namespace std;

//Displays a message and gets input. Only cares about the first character entered.
int Encounter::getTraitInput()
{
    char checkChar;
    char second;

    cout << "Do you want to use Lasers, Shields, Diplomacy, Trickery, " <<endl;
    cout << "Speed, Navigation, Bravery, or Caution? "; 
    while (1)
    {
    	checkChar = toupper(firstCharEntered(&second));
	second = toupper(second);
	switch (checkChar)
	{
	    case 'L':
		cout << "Lasers!" << endl;
		return 1;
	    case 'S':
		if (second == 'H')
		{
		    cout << "Shields!" << endl;
		    return 2;
		}
		else if (second == 'P')
		{
		    cout << "Speed!" << endl;
		    return 5;
		}
		else break;
	    case 'T':
		cout << "Trickery!" << endl;
		return 3;
	    case 'D':
		cout << "Diplomacy!" << endl;
		return 4;
	    case 'N':
		cout << "Navigation!" << endl;
		return 6;
	    case 'B':
		cout << "Bravery!" << endl;
		return 7;
	    case 'C':
		cout << "Caution!" << endl;
		return 8;
	}
	cout << "Invalid input. Please try again: ";
    }
}

//gets input from the user and returns the first character they typed
//whitespace characters don't count.
char Encounter::firstCharEntered(char* second)
{
  string input;
  int i = 0;
  int whiteSpace = 0;

  getline(cin,input);
  while (input[i] != '\0')
    {
      i++;
      if (isspace(input[i]) && i == whiteSpace)
        {
          whiteSpace++;
        }
    }
  *second = input[whiteSpace+1];
  return input[whiteSpace];
}

//decides the outcome of the encounter.
//TRUE means player won, false means player lost
bool Encounter::challenge(int alienTrait, int playerTrait) {
  //nothing yet
  return true;
}

//Decides if the chosen trait works in the given encounter.
//For example: Using diplomacy when a golem tries to rob you isn't going to help
bool Encounter::decideGood(int input, int encounter) {
  //nothing yet
  return true;
}

//main encounter logic. Displays text, get's the user's response, determines the
//outcome, and updates player and alien stats based on that outcome.
void Encounter::start(Alien* myAlien, Player* captain) {
  int encounter, input;
  bool win;
  encounter = myAlien->getEncounter(rand()%2);
  if (myAlien->hostilityRole()) {
    encounter = 0; //fight
  }
  myAlien->displayEncounter(encounter);
  input = getTraitInput();
  if (decideGood(input, encounter)) {
    if (challenge(myAlien->getTrait(input), captain->getTrait(input))) {
      win = true;
    } else {
      win = false;
    }
  } else {
    win = false;
  }
  captain->updateStats(input, win);
  myAlien->updateStats(input, win);
}

