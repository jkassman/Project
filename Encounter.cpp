#include <string>
#include <sstream>
#include <iostream>
#include "Player.h"
#include "Alien.h"

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
		return 1;
	    case 'S':
		if (second == 'H')
		{
		    return 2;
		}
		else if (second == 'P')
		{
		    return 5;
		}
		else break;
	    case 'T':
		return 3;
	    case 'D':
		return 4;
	    case 'N':
		return 6;
	    case 'B':
		return 7;
	    case 'C':
		return 8;
	}
	cout << "Invalid input. Please try again" << endl;
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
}

//Decides if the chosen trait works in the given encounter.
//For example: Using diplomacy when a golem tries to rob you isn't going to help
bool Encounter::decideGood(int input, int encounter) {
  //nothing yet
}

//main encounter logic. Displays text, get's the user's response, determines the
//outcome, and updates player and alien stats based on that outcome.
void Encounter::start(Alien* myAlien, Player* captain) {
  int encounter, input;
  bool win;
  encounter = myAlien->encounter[rand()%2];
  if (myAlien->hostilityRole()) {
    encounter = 0; //fight
  }
  Alien->displayEncounter(encounter);
  input = getTraitInput();
  if (decideGood(input)) {
    if (challenge(myAlien->trait[input], captain->getTrait(input))) {
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

