#include "Alien.h"
#include "Player.h"


//updates the alien's stats based on the result of the encounter.
//if the alien lost (win is false), alien gains a point in the corresponding trait. 
//Also, hostility is changed (NOTE: Should this be separate function?)
void Alien::updateStats(int input, bool win) {
  //nothing yet
}

//virtual function; each alien class will override it with their own fancy
//encounter text.
virtual void Alien::displayEncounterText(int encounter) {
  //nothing ever.
}

//Decides if the alien will attack. True = attack.
bool Alien::hostilityRole() {
  //nothing yet
}
