/* Lauren Kuta
   CSE 20212
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

using namespace std;

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

int Player::getAttribute(int n) {
   return Attributes[n];
}

//NOTE: Needs message
//asks the user to upgrade attributes 4 times.
//each time is 25% of total point allocation (10-15 * zone).
int Player::upgradeAtt() {
  char choice;
  
  //how many upgrade points you can spend this upgrade phase:
  int multiplier;
  multiplier = Encounter::getMultiplier(); //2^zone
  Encounter test;
  int points = (rand() % 6 + 10) * multiplier; //(10-15) * multiplier
  for (int i = 4; i > 0; i--) {
    cout << "Which of your stats would you like to upgrade?" << endl;
    cout << "Press S for Sanity, Press E for Engines, I for Intelligence, P for Power, or Q to quit." << endl;
    if (i == 4) {
      cout << "To warp to a new zone, type the number of the zone you would like to warp to." << endl;
    }
    cin >> choice;
    cout << endl;
    switch (toupper(choice)) {
    case 'P':
      Attributes[0] += points/i; //assign 25% of points to power
      points -= points/i;
      test.resetScreen(this);
      break;
    case 'I':
      Attributes[1] += points/i;
      points -= points/i;
      test.resetScreen(this);
      break;
    case 'E':
      Attributes[2] += points/i;
      points -= points/i;
      test.resetScreen(this);
      break;
    case 'S':
      Attributes[3] += points/i;
      points -= points/i;
      test.resetScreen(this);
      break;
    case 'Q':
      system("clear");
      return 2;		// User quit
      break;
    case '0':
      Encounter::changeZone(0);
      return 1;
    case '1':
      Encounter::changeZone(1);
      return 1;
    case '2':
      Encounter::changeZone(2);
      return 1;
    case '3':
      Encounter::changeZone(3);
      return 1;
    case '4':
      Encounter::changeZone(4);
      return 1;
    case '5':
      Encounter::changeZone(5);
      return 1;
    case '?':
      debug();
    i++;
    break;
    default:
      cout << "Please enter something else." << endl;
      i++;
      break;
    }
  }
  return 1;		// Go to encounter
}
  
void Player::updateStats(int TraitUsed, bool win) { //True if Player wins
  int NewTrait;
  int AttrUsed; //which attribute was used.
  int toReduce; //number to reduce Attribute by
  if(win) {
     NewTrait = Traits[TraitUsed] + 1;	// Increase winning trait by 1
     Traits[TraitUsed] = NewTrait;
    //// cout << "Trait that should be +1: " << NewTrait << endl;
     if(TraitUsed % 2) {	// if traitused is odd
       Traits[TraitUsed+1]--;	// Decrease corresponding trait
     }else{
       Traits[TraitUsed-1]--; 	// Decrease corresponding trait
     }
     Traits[7]++; //Increase bravery
     Traits[8]--; //Decrease caution
  }else{ //Player Lost
	toReduce = rand()%5 + 4; //4-8
	AttrUsed = (TraitUsed-1)/2;
	Attributes[AttrUsed] -= toReduce;
	cout << "Reduced " << AttrUsed << " by " << toReduce << "." << endl;
	Traits[8]++; //Increase caution
	Traits[7]--; //Decrease bravery
  }
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
/*
void Player::upgradeSanity() {
  Encounter screen; //I'm not sure this is the best way to do this.
  srand(time(NULL));
  int raise, NewSan;
  raise = rand() % 4 + 1;
  NewSan = Attributes[3] + raise;
  Attributes[3] = NewSan;
  screen.resetScreen(this);
  cout << "You decide to take a nap on your ratty cot to calm your nerves and improve your concentration." << endl << endl;
}

void Player::upgradeEngines() {
  Encounter screen; //I'm not sure this is the best way to do this.
  srand(time(NULL));
  int raise, NewEng;
  raise = rand() % 4 + 1;
  NewEng = Attributes[2] + raise;
  Attributes[2] = NewEng;
  screen.resetScreen(this);
  cout << "You double check that your engines are in working condition.  Looks like they'll last a little while longer." << endl << endl;
}

void Player::upgradeIntel() {
  Encounter screen; //I'm not sure this is the best way to do this.
  srand(time(NULL));
  int raise, NewIntel;
  raise = rand() % 4 + 1;
  NewIntel = Attributes[1] + raise;
  Attributes[1] = NewIntel;
  screen.resetScreen(this);
  cout << "You flip through the pages of some the old lore books stached in a nook of the ship." << endl;
  cout << "(you're too old fashioned to use the ship's databases)." << endl; 
  cout << "Some of this information could be helpful for the encounters ahead!" << endl << endl;
}

void Player::upgradePower() {
  Encounter screen; //I'm not sure this is the best way to do this.
  srand(time(NULL));
  int raise, NewPow;
  raise = rand() % 4 + 1;
  NewPow = Attributes[0] + raise;
  Attributes[0] = NewPow;
  screen.resetScreen(this);
  cout << "You fiddle with the power and shield systems aboard the ship." << endl;
  cout << "These adjustments will definitely help in the long run." << endl << endl;
}
*/

void Player::debug() {
	cout<<"DEBUGGING"<<endl;
	printAttributes();
	cout<<endl;
	printTraits();
	cout<<endl;
}
   
