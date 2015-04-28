/*
   Player.cpp
   Contains defintions of functions initialized in the Player.h file
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "Encounter.h"
#include "Message.h"

using namespace std;

// Initialize Traits and Attributes
Player::Player() {
  srand(time(NULL));
  int val;
 // Set Attributes: 0 = Energy, 1 = Intelligence, 2 = Engines, 3 = Sanity
  for(int i = 0; i <= 4; i++) {
    Attributes.push_back(6);
  }
 // Set Traits:  1=laser, 2=shield, 3=trick, 4=diplo, 5=speed, 6=nav, 7=brav, 8=caution
    Traits.push_back(0);	// First spot dummy
  for(int j = 1; j < 8; j+=2) {
    val=rand() % 7 - 3;
    Traits.push_back(val);
    Traits.push_back(val*-1);
  }
}

void Player::printAttributes() {
  int m;
  for (m = 0; m < (int) Attributes.size()-1; m++) {
    cout << Attributes[m] << " ";
  }
}

void Player::printTraits() {
  int m;
  for (m = 1; m < (int) Traits.size(); m+=2) {
    cout << Traits[m] << " ";
    cout << Traits[m+1] << " | ";
  }
}

//asks the user to upgrade attributes 3-5 times.
//each time is a certain percentage of total point allocation (10-15 * zone).
int Player::upgradeAtt() {
  char choice;
  
  //how many upgrade points you can spend this upgrade phase:
  int multiplier;
  multiplier = Encounter::getMultiplier(); //2^zone
  Message say;
  int points = (rand() % 6 + 10) * multiplier; //(10 to 15) * multiplier
  int max = rand () % 3 + 3;
  say.resetScreen(this, 1);

  // This loop controls number of training phases
  for (int i = max; i > 0; i--) {
    choice = say.getAttrChoice();
    // Switch based on the choice
    switch (toupper(choice)) {
    case 'P':
      Attributes[0] += points/i; // assign equal fraction of points to power
      points -= points/i;	 // remove those points
      say.trainAttr('P');
      break;
    case 'I':
      Attributes[1] += points/i;
      points -= points/i;
      say.trainAttr('I');
      break;
    case 'E':
      Attributes[2] += points/i;
      points -= points/i;
      say.trainAttr('E');
      break;
    case 'S':
      Attributes[3] += points/i;
      points -= points/i;
      say.trainAttr('S');
      break;
    case 'Q':
      system("clear");
      return 2;		// User quit
      break;
    case '0':		// Switching Zones
      if (i != max) {
	say.notEnoughTime();	// Encounter has happened
	i++;			// Give another pass
      } else if (Encounter::changeZone(-1)) { //if changeZone fails
	i++;
      } else {
	return 1;
      }
      break;
    case '1':		// Switching Zones
      if (i != max) {
	say.notEnoughTime();
	i++;
      } else if (Encounter::changeZone(1)) {//if changeZone fails
	i++;
      } else {
	return 1;
      }
      break;
    case '?':	// Debug mode
      debug();
      i++;
      break;
    default:
      cout << "Please enter something else." << endl;
      i++;
      break;
    }
    say.resetScreen(this, 1);
  }
  return 1;		// Go to encounter
}
  
// Change player stats after encounter
//if you lost, reduce attributes.
//if you won, increase one trait and decrease another
//takes into account which zone you are in
void Player::updateStats(int TraitUsed, bool win) { //True if Player wins
  int NewTrait;
  int AttrUsed; //which attribute was used.
  int toReduce; //number to reduce Attribute by
  int modifier = Encounter::getMultiplier(); //2^zone
  if(win) {
    NewTrait = Traits[TraitUsed] + modifier;	// Increase winning trait by 1
    Traits[TraitUsed] = NewTrait;
    if(TraitUsed % 2) {	// if traitused is odd
      Traits[TraitUsed+1] -= modifier;	// Decrease corresponding trait
    }else{
      Traits[TraitUsed-1] -= modifier; // Decrease corresponding trait
    }
    Traits[7] += modifier; //Increase bravery
    Traits[8] -= modifier; //Decrease caution
  } else { //Player Lost
    toReduce = modifier*(rand()%4 + 13); //13-16
    AttrUsed = (TraitUsed-1)/2;
    Attributes[AttrUsed] -= toReduce;	// Reduce attribute
    cout << "Reduced " << AttrUsed << " by " << toReduce << "." << endl;
    Traits[8] += modifier; //Increase caution
    Traits[7] -= modifier; //Decrease bravery
  }
}

int Player::getAttribute(int n) {
   return Attributes[n];
}

int Player::getTrait(int n) {
   return Traits[n];
}

void Player::setAttribute(int pos, int value) {
   Attributes[pos-1] = value;
}

void Player::setTrait(int pos, int value) {
   Traits[pos-1] = value;
}

// Prints player info for debugging
void Player::debug() {
	cout<<"DEBUGGING"<<endl;
	printAttributes();
	cout<<endl;
	printTraits();
	cout<<endl;
}

int Player::highestTrait()
{
  int value, max = -2000000000;
  for (int i = 1; i <= 8; i++) {
    value = Traits[i] + Attributes[(i-1)/2];
    if (value > max) {
      max = value;
    }
  }
  return max;
}
