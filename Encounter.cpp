#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
#include "Player.h"
#include "Alien.h"
#include "Encounter.h"

using namespace std;

int Encounter::myZone = 0;

//Displays a message and gets input. Only cares about the first character entered.
int Encounter::getTraitInput()
{
    char checkChar;
    char second;
    int print = 0;

    cout << "Do you want to use Lasers, Shields, Diplomacy, Trickery, " <<endl;
    cout << "Speed, Navigation, Bravery, or Caution? "; 
    while (1)
    {
    	checkChar = toupper(firstCharEntered(&second));
	second = toupper(second);
	switch (checkChar)
	{
	    case 'L':
		if (print) cout << "Lasers!" << endl;
		return 1;
	    case 'S':
		if (second == 'H')
		{
		    if (print) cout << "Shields!" << endl;
		    return 2;
		}
		else if (second == 'P')
		{
		    if (print) cout << "Speed!" << endl;
		    return 5;
		}
		else break;
	    case 'T':
		if (print) cout << "Trickery!" << endl;
		return 3;
	    case 'D':
		if (print) cout << "Diplomacy!" << endl;
		return 4;
	    case 'N':
		if (print) cout << "Navigation!" << endl;
		return 6;
	    case 'B':
		if (print) cout << "Bravery!" << endl;
		return 7;
	    case 'C':
		if (print) cout << "Caution!" << endl;
		return 8;
	    case '?':
		if (print) cout << "Debugging!" << endl;
		return 9;
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

  cin >> input;
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
	////cout<<"ALIEN: "<<alienTrait<<" PLAYER: "<<playerTrait<<endl;
	////cout<<"MODALIEN: "<<modAlien<<" MODPLAYER: "<<modPlayer<<endl;

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
    if (input == 1 || input == 2 || input == 6 || (input == 5)) {
      return true;
    } else {
      break;
    }
  case 1: //Threaten
    //	power 	      bravery	    trickery	  speed
    if (input == 1 || input == 7 || input == 3 || (input == 5)) {
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
  return false;
}

//main encounter logic. Displays text, get's the user's response, determines the
//outcome, and updates player and alien stats based on that outcome.
bool Encounter::start(Alien* myAlien, Player* captain) {
  int encounter, input;
  bool win;
  encounter = myAlien->getEncounter(rand()%2);
  if (myAlien->hostilityRole()) {
    encounter = 0; //fight
  }
  myAlien->displayEncounter(encounter);
  input = getTraitInput();
	////////// Debugging
	while(input==9) {	
	  myAlien->displayTraits();
	  input = getTraitInput();
	}
	////////// 
  if (decideGood(input, encounter)) {
	int playersum=captain->getTrait(input) + captain->getAttribute((input-1)/2);
    if (challenge(myAlien->getTrait(input), playersum)) {
      win = true;
    } else {
      win = false;
    }
  } else {
    win = false;
  }
  captain->updateStats(input, win);
  myAlien->updateStats(encounter, input, win);
  resetScreen(captain);
  displayResult(win, encounter, input);
  return win;
}

//displays a message letting the user know how the encounter went
void Encounter::displayResult(bool win, int encounter, int trait) {
  if (!decideGood(trait, encounter)) {
    cout << "You shouldn't use " << trait2str(trait) 
	 << " during a " << encounter2str(encounter) << '.' << endl;
  }
  if (win) {
    cout << "You won the encounter!" << endl;
  } else {
    cout << "You lost the encounter!" << endl;
  }
}

string Encounter::trait2str(int trait)
{
  switch (trait) {
  case 1:
    return "Lasers";
  case 2:
    return "Shields";
  case 3:
    return "Trickery";
  case 4:
    return "Diplomacy";
  case 5:
    return "Speed";
  case 6:
    return "Navigation";
  case 7:
    return "Bravery";
  case 8:
    return "Caution";
  default:
    return "ERROR: unknown trait";
  }
}

string Encounter::encounter2str(int encounter)
{
  switch (encounter) {
  case 0:
    return "Fight";
  case 1:
    return "Threaten";
  case 2:
    return "Rob";
  case 3:
    return "Story";
  case 4:
    return "Trade";
  case 5:
    return "Race";
  default:
    return "ERROR: Unkown encounter";
  }
}

string Encounter::attribute2str(int attribute)
{
  switch (attribute) {
  case 0:
    return "Power";
  case 1:
    return "Intelligence";
  case 2:
    return "Engines";
  case 3:
    return "Sanity";
  default:
    return "ERROR: Unknown attribute";
  }
}

void Encounter::resetScreen(Player* captain)
{
  int width = 3; //width of the traits; how much space padding to add.
                 //for example, 3 does: |  1|, | 42|, and |123| 
  system("clear");
  cout << "POWER            Lasers |"
       << setw(width) << captain->getTrait(1)+captain->getAttribute(0) << "|"
       << setw(width) << captain->getTrait(2)+captain->getAttribute(0)
       << "| Shields"<< endl;
  cout << "INTELLIGENCE   Trickery |"
       << setw(width) << captain->getTrait(3) + captain->getAttribute(1) <<"|"
       << setw(width) << captain->getTrait(4) + captain->getAttribute(1) 
       <<"| Diplomacy"<<endl;
  cout << "ENGINES           Speed |"
       << setw(width) << captain->getTrait(5) + captain->getAttribute(2) <<"|"
       << setw(width) << captain->getTrait(6) + captain->getAttribute(2) 
       <<"| Navigation"<<endl;
  cout << "SANITY          Bravery |"
       << setw(width) << captain->getTrait(7) + captain->getAttribute(3) <<"|"
       << setw(width) << captain->getTrait(8) + captain->getAttribute(3) 
       <<"| Caution"<<endl;

  cout << endl;
}

int Encounter::getZone()
{
    return myZone;
}

//increments zone if select is positive, decrements if negative
//does nothing if zero.
void Encounter::changeZone(int select)
{
    if (select > 0) {
	myZone++;
    } else if (select <0) {
	myZone--;
    } else {
	//do nothing
    }
}

int Encounter::getMultiplier()
{
  int multiplier = 1;
  //2^myZone:
  for (int i = 0; i < myZone; i++) {
    multiplier *= 2;
  }
  return multiplier;
}
