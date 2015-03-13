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

using namespace std;

Player::Player() {
  srand(time(NULL));
  for(int i = 0; i <= 4; i++) {
    Attributes.push_back(6);
   }
 // Attributes: 0 = Energy, 1 = Intelligence, 2 = Engines, 3 = Sanity
  for(int j = 0; j < 9; j++) {
    Traits.push_back(rand() % 3 + 1);
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
  for (m = 0; m < (int) Traits.size()-1; m++) {
    cout << Traits[m] << " ";
  }
}

int Player::getAttribute(int n) {
   return Attributes[n-1];
}

void Player::upgradeAtt() {
  int num = 42;
  char choice;
   while(num != 4) {
   cout << "Which of your stats would you like to upgrade?" << endl;
   cout << "Press S for Sanity, Press G for Engines, I for Intelligence, E for Energy, or Q to quit." << endl;
   cin >> choice;
   switch (choice) {
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
      num = 4;
      break;
    default:
       cout << "Please enter something else." << endl;
    }
   if(num == 4) {
     num = 4;
     break;
   }
   num = rand() % 4 + 1;
   cout << endl << "Num " << num << endl;
  }
}
  
void Player::updateStats(int TraitUsed, bool win) { //True if Player wins
  int NewTrait, NewCompTrait;
  if(win) {
     NewTrait = Traits[TraitUsed-1] + 1;
     Traits[TraitUsed-1] = NewTrait;
     cout << "Trait that should be +1" << NewTrait << endl;
     if(TraitUsed % 2) {
       NewCompTrait = Traits[TraitUsed]--;
       Traits[TraitUsed] = NewCompTrait;
     }else{
       NewCompTrait = Traits[TraitUsed-2]--;
       Traits[TraitUsed-2] = NewCompTrait;  
     }
  }else{
       if(TraitUsed == 1 || TraitUsed == 2) {
          Attributes[0]--;
          Traits[7]++;
       }if(TraitUsed == 3 || TraitUsed == 4) {
          Attributes[1]--;
          Traits[7]++;
       }if(TraitUsed == 5 || TraitUsed == 6) {
          Attributes[2]--;
          Traits[7]++;
       }if(TraitUsed == 7 || TraitUsed == 8) {
          Attributes[3]--;
          Traits[7]++;
    }   
  }
}

int Player::getTrait(int n) {
   return Traits[n-1];
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
  cout << "Your sanity level has increased " << raise << " points!" << endl;
  cout << "Your total sanity is " << NewSan << "." << endl;
  Attributes[3] = NewSan;
}

void Player::upgradeEngines() {
  srand(time(NULL));
  int raise, NewEng;
  cout << "You double check that your engines are in working condition.  Looks like they'll last a little while longer." << endl << endl;
  raise = rand() % 4 + 1;
  NewEng = Attributes[2] + raise;
  cout << "Your engines' level has increased " << raise << " points!" << endl;
  cout << "The total level of your engines is " << NewEng << "." << endl;
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
  cout << "Your intelligence level has increased " << raise << " points!" << endl;
  cout << "Your total intellgence level is " << NewIntel << "." << endl;
  Attributes[1] = NewIntel;
}

void Player::upgradeEnergy() {
  srand(time(NULL));
  int raise, NewEner;
  cout << "You fiddle with the power and shield systems aboard the ship." << endl;
  cout << "These adjustments will definitely help in the long run." << endl << endl;
  raise = rand() % 4 + 1;
  NewEner = Attributes[0] + raise;
  cout << "Your energy level has increased " << raise << "points!" << endl;
  cout << "You total energy level is" << NewEner << "." << endl;
  Attributes[0] = NewEner;
}
   
