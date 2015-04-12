#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
#include <math.h> //consider removing after move to Message
#include "Player.h"
#include "Alien.h"
#include "Encounter.h"
#include "Message.h"
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
	case 'Q':
	  return 10;
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
//TAKES INTO ACCOUNT WHICH ZONE YOU ARE IN
bool Encounter::challenge(int alienTrait, int playerTrait) {
  int modifier = getMultiplier(); //2^zone
  alienTrait *= modifier;
  //if you have 0 in any trait, instantly lose.
  if (alienTrait <= 0) {
    return true;
  } else if (playerTrait <=0) {
    return false;
  }
  //create a random number from 0 to max of player/alienTrait.
  int modAlien = rand() % max(alienTrait, playerTrait);
  int modPlayer = rand() % max(alienTrait, playerTrait);
<<<<<<< HEAD
	////cout<<"ALIEN: "<<alienTrait<<" PLAYER: "<<playerTrait<<endl;
	////cout<<"MODALIEN: "<<modAlien<<" MODPLAYER: "<<modPlayer<<endl;
  if ((playerTrait + modPlayer) >= (alienTrait + modAlien)) {
=======
  ////cout<<"ALIEN: "<<alienTrait<<" PLAYER: "<<playerTrait<<endl;
  ////cout<<"MODALIEN: "<<modAlien<<" MODPLAYER: "<<modPlayer<<endl;
  int modifier = getMultiplier();
  if ((playerTrait + modPlayer) >= (modifier * (alienTrait + modAlien))) {
>>>>>>> fb8723c47ce426e7eb067a352a20984c9ec37e8b
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
    // power shields navigation speed
    if (input == 1 || input == 2 || input == 6 || (input == 5)) {
      return true;
    } else {
      break;
    }
  case 1: //Threaten
    // power bravery trickery speed
    if (input == 1 || input == 7 || input == 3 || (input == 5)) {
      return true;
    } else {
      break;
    }
  case 2: //Rob
    // power shields caution speed
    if (input == 1 || input == 2 || input == 8 || input == 5) {
      return true;
    } else {
      break;
    }
  case 3: //Story
    // power diplomacy caution speed
    if (input == 1 || input == 4 || input == 8 || input == 5) {
      return true;
    } else {
      break;
    }
  case 4: //Trade
    // power diplomacy trickery speed
    if (input == 1 || input == 4 || input == 3 || input == 5) {
      return true;
    } else {
      break;
    }
  case 5: //Race
    // power navigation bravery speed
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
int Encounter::start(Alien* myAlien, Player* captain) {
  int encounter, input;
  int win;
  Message msgs;
  encounter = myAlien->getEncounter(rand()%2);
  if (myAlien->hostilityRole()) {
    encounter = 0; //fight
  }
  msgs.newEncounter(encounter,myAlien->getName());
  input = getTraitInput();
  ////////// Debugging
  while(input==9) {
    myAlien->displayTraits();
    input = getTraitInput();
  }
  //////////
  if(input==10)
    return 2;
  if (decideGood(input, encounter)) {
    int playersum=captain->getTrait(input) + captain->getAttribute((input-1)/2);
    if (challenge(myAlien->getTrait(input), playersum)) {
      win = 1;
    } else {
      win = 0;
    }
  } else {
    win = 0;
  }
  captain->updateStats(input, win);
  myAlien->updateStats(encounter, input, win);
  msgs.resetScreen(captain);
  msgs.encResults(encounter, input, win, myAlien->getName());
  return win;
}


int Encounter::getZone()
{
  return myZone;
}
//increments zone if select is positive, decrements if negative
//does nothing if zero.
void Encounter::changeZone(int select)
{
  myZone = select;
  /*
    if (select > 0) {
    myZone++;
    } else if (select <0) {
    myZone--;
    } else {
    //do nothing
    }
  */
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
