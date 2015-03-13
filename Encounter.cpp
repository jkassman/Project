#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm>
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

//Decides the outcome of the encounter.
//TRUE means player won, false means player lost
bool Encounter::challenge(int alienTrait, int playerTrait) {
  //if you have 0 in any trait, instantly lose.
  if (alienTrait <= 0) {
    return true;
  } else if (playerTrait <=0) {
    return false;
  }

  //create a random number from 0 to max of player/alienTrait.
  int modAlien = rand() % max(alienTrait, playerTrait);
  int modPlayer = rand() % max(alienTrait, playerTrait);

  if ((playerTrait + modPlayer) >= (alienTrait + modAlien)) {
    return true;
  } else {
    return false;
  }
}

//Decides if the chosen trait works in the given encounter.
//For example: Using diplomacy when a golem tries to rob you isn't going to help
bool Encounter::decideGood(int input, int encounter) {
  if (input >= 1 && input <= 8 && encounter >= 0 && encounter <= 5) {
    //nothing, good.
  } else {
    cout << "This shouldn't happen, but invalid input was passed to decideGood" << endl;
  }
  switch (encounter) {
  case 0: //Fight
    //	power 	      shields 	    navigation 	  speed
    if (input == 1 || input == 2 || input == 6 || input == 5) {
      return true;
    } else {
      break;
    }
  case 1: //Threaten
    //	power 	      bravery	    trickery	  speed
    if (input == 1 || input == 7 || input == 3 || input == 5) {
      return true;
    } else {
      break;
    }
  case 2: //Rob
    //	power 	      shields	    caution	  speed
    if (input == 1 || input == 2 || input == 8 || input == 5) {
      return true;
    } else {
      break;
    }
  case 3: //Story
    //	power 	      diplomacy	    caution	  speed
    if (input == 1 || input == 4 || input == 8 || input == 5) {
      return true;
    } else {
      break;
    }
  case 4: //Trade
    //	power 	      diplomacy	    trickery	  speed
    if (input == 1 || input == 4 || input == 3 || input == 5) {
      return true;
    } else {
      break;
    }
  case 5: //Race
    //	power 	      navigation    bravery	  speed
    if (input == 1 || input == 6 || input == 7 || input == 5) {
      return true;
    } else {
      break;
    }
  }
  //it only gets here if it doesn't return true, so the person chose wrong.
  cout << "You have chosen...poorly..." << endl;
  return false;
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
  myAlien->updateStats(encounter, input, win);
}

