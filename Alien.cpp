#include <iostream>
#include "Alien.h"
#include "Player.h"

using namespace std;

Alien::Alien() {
  //Not sure why this is needed?
}

//updates the alien's stats based on the result of the encounter.
//if the alien lost (win is false), alien gains a point in the corresponding trait. 
//Also, hostility is changed (NOTE: Should this be separate function?)
void Alien::updateStats(int input, bool win) {
  //nothing yet
}

//virtual function; each alien class will override it with their own fancy
//encounter text.
//void Alien::displayEncounter(int encounter) {
  //nothing ever.
//}

//Decides if the alien will attack. True = attack.
bool Alien::hostilityRole() {
  //nothing yet
  return false;
}

//select shouldb be between 0 and 1. Returns one of two encounters.
int Alien::getEncounter(int select) {
  if (select >= 0 && select <= 1) {
    return encounter[select];
  } else {
    cout << "Error, invalid encounter selection in Alien.cpp" << endl;
    return -1;
  }
}

int Alien::getTrait(int select) {
  return trait[select]; //Add input (select) checking!
}
