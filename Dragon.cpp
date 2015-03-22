#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Dragon.h"
#include "Alien.h"

using namespace std;

Dragon::Dragon()
{
	srand(time(NULL));
// The numbers between | | are the starting values for the alien's traits
	trait.push_back(3+rand()%5-2); 	// Hostility
	trait.push_back(7+rand()%5-2);	// Against player's Laser
	trait.push_back(9+rand()%5-2);	// Shield
	trait.push_back(4+rand()%5-2);	// Trick
	trait.push_back(6+rand()%5-2);	// Diplomacy
	trait.push_back(7+rand()%5-2);	// Speed
	trait.push_back(5+rand()%5-2);	// Navigation
	trait.push_back(8+rand()%5-2);	// Bravery
	trait.push_back(4+rand()%5-2);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	encounter[0] = 1; //Threaten
	encounter[1] = 5; //Race
	name="Dragon";
}

//displays text for each encounter the dragon can be in, specific to the dragon.
void Dragon::displayEncounter(int thisencounter) {
	//very simple version:
  switch (thisencounter) {
  case 0: //Attack
    cout << "A Dragon attacks you!" << endl;
    break;
  case 1: //Threaten
    cout << "A Dragon threatens you!" << endl;
    break;
  case 5: //Race
    cout << "A Dragon wants to race you!" << endl;
    break;
  }
}

