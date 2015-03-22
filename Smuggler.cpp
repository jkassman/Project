#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Smuggler.h"
#include "Alien.h"

using namespace std;

Smuggler::Smuggler()
{
	srand(time(NULL));
	trait.push_back(0); 	// Store dummy in 0
// The numbers between | | are the starting values for the alien's traits
	trait.push_back(3+rand()%5-2);	// Against player's Laser
	trait.push_back(7+rand()%5-2);	// Shield
	trait.push_back(5+rand()%5-2);	// Trick
	trait.push_back(5+rand()%5-2);	// Diplomacy
	trait.push_back(6+rand()%5-2);	// Speed
	trait.push_back(9+rand()%5-2);	// Navigation
	trait.push_back(9+rand()%5-2);	// Bravery
	trait.push_back(6+rand()%5-2);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	encounter[0] = 2; //Rob
	encounter[1] = 4; //Trade
	hostility = 3; //Just to initialize it, I forgot what we decided on hostility randomness.
	name="Smuggler";
}

//displays text for each encounter the dragon can be in, specific to the dragon.
void Smuggler::displayEncounter(int thisencounter) {
	//very simple version:
  switch (thisencounter) {
  case 0: //Attack
    cout << "A Smuggler attacks you!" << endl;
    break;
  case 2: //Rob
    cout << "A Smuggler is trying to rob you!" << endl;
    break;
  case 4: //Trade
    cout << "A Smuggler wants to trade with you!" << endl;
    break;
  }
}

