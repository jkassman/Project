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
 // Set Traits:  1=laser, 2=shield, 3=diplo, 4=trick, 5=speed, 6=nav, 7=brav, 8=caution
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

int Player::upgradeAtt() {
  Encounter screen; //I'm not sure this is the best way to do this.
  int num = rand()% 4 + 2; //	Randomly does 2 to 4 upgrades before encounter
  char choice;
   for(int i=0;i<num;i++) {
   cout << "Which of your stats would you like to upgrade?" << endl;
   cout << "Press S for Sanity, Press G for Engines, I for Intelligence, E for Energy, or Q to quit." << endl;
   cin >> choice;
   cout << endl;
   screen.resetScreen(this);
   switch (toupper(choice)) {
    case 'S':
      upgradeSanity();
      break;
    case 'G':
      upgradeEngines();
      break;
    case 'I':
      upgradeIntel();
      break;
    case 'E':
      upgradeEnergy();
      break;
    case 'Q':
      system("clear");
      return 1;		// User quit
      break;
    case '?':
      debug();
      i--;
      break;
    default:
      cout << "Please enter something else." << endl;
      i--;
      break;
    }
  }
  return 0;		// Go to encounter
}
  
void Player::updateStats(int TraitUsed, bool win) { //True if Player wins
  int NewTrait;
  if(win) {
     NewTrait = Traits[TraitUsed] + 1;	// Increase winning trait by 1
     Traits[TraitUsed] = NewTrait;
    //// cout << "Trait that should be +1: " << NewTrait << endl;
     if(TraitUsed % 2) {	// if traitused is odd
       Traits[TraitUsed+1]--;	// Decrease corresponding trait
     }else{
       Traits[TraitUsed-1]--; 	// Decrease corresponding trait
     }
  }else{
       if(TraitUsed == 1 || TraitUsed == 2) {
          Attributes[0]--;	// Decrease attribute used
          Traits[8]++;		// Increase caution
          Traits[7]--;		// Decrease bravery
       }if(TraitUsed == 3 || TraitUsed == 4) {
          Attributes[1]--;	// Decrease attribute used
          Traits[8]++;		// Increase caution
          Traits[7]--;		// Decrease bravery
       }if(TraitUsed == 5 || TraitUsed == 6) {
          Attributes[2]--;	// Decrease attribute used
          Traits[8]++;		// Increase caution
          Traits[7]--;		// Decrease bravery
       }if(TraitUsed == 7 || TraitUsed == 8) {
          Attributes[3]--;	// Decrease attribute used
          Traits[8]++;		// Increase caution
          Traits[7]--;		// Decrease bravery
       }   
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

void Player::upgradeSanity() {
  srand(time(NULL));
  int raise, NewSan;
  cout << "You decide to take a nap on your ratty cot to calm your nerves and improve your concentration." << endl << endl;
  raise = rand() % 4 + 1;
  NewSan = Attributes[3] + raise;
  cout << "Your sanity level has increased " << raise << " points!" << endl<< endl;
  ////cout << "Your total sanity is " << NewSan << "." << endl;
  Attributes[3] = NewSan;
}

void Player::upgradeEngines() {
  srand(time(NULL));
  int raise, NewEng;
  cout << "You double check that your engines are in working condition.  Looks like they'll last a little while longer." << endl << endl;
  raise = rand() % 4 + 1;
  NewEng = Attributes[2] + raise;
  cout << "Your engines' level has increased " << raise << " points!" << endl<< endl;
  ////cout << "The total level of your engines is " << NewEng << "." << endl;
  Attributes[2] = NewEng;
}

void Player::upgradeIntel() {
  srand(time(NULL));
  int raise, NewIntel;
  cout << "You flip through the pages of some the old lore books stached in a nook of the ship." << endl;
  cout << "(you're too old fashioned to use the ship's databases)." << endl; 
  cout << "Some of this information could be helpful for the encounters ahead!" << endl << endl;
  raise = rand() % 4 + 1;
  NewIntel = Attributes[1] + raise;
  cout << "Your intelligence level has increased " << raise << " points!" << endl<< endl;
  ////cout << "Your total intellgence level is " << NewIntel << "." << endl;
  Attributes[1] = NewIntel;
}

void Player::upgradeEnergy() {
  srand(time(NULL));
  int raise, NewEner;
  cout << "You fiddle with the power and shield systems aboard the ship." << endl;
  cout << "These adjustments will definitely help in the long run." << endl << endl;
  raise = rand() % 4 + 1;
  NewEner = Attributes[0] + raise;
  cout << "Your energy level has increased " << raise << " points!" << endl<< endl;
  ////cout << "You total energy level is " << NewEner << "." << endl;
  Attributes[0] = NewEner;
}

void Player::debug() {
	cout<<"DEBUGGING"<<endl;
	printAttributes();
	cout<<endl;
	printTraits();
	cout<<endl;
}
   
