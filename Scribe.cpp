#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Scribe.h"
#include "Alien.h"

using namespace std;

Scribe::Scribe()
{
	srand(time(NULL));
// The numbers between | | are the starting values for the alien's traits
	trait.push_back(3+rand()%5-2); 	// Hostility
	trait.push_back(5+rand()%5-2);	// Against player's Laser
	trait.push_back(3+rand()%5-2);	// Shield
	trait.push_back(13+rand()%5-2);	// Trick
	trait.push_back(6+rand()%5-2);	// Diplomacy
	trait.push_back(4+rand()%5-2);	// Speed
	trait.push_back(7+rand()%5-2);	// Navigation
	trait.push_back(4+rand()%5-2);	// Bravery
	trait.push_back(8+rand()%5-2);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	encounter[0] = 3; //Story
	encounter[1] = 4; //Trade
	name="Scribe";
}

//displays text for each encounter the dragon can be in, specific to the dragon.
void Scribe::displayEncounter(int thisencounter) {
	//very simple version:
  switch (thisencounter) {
  case 0: //Attack
    cout << "A Scribe attacks you!" << endl;
    break;
  case 3: //Story
    cout << "A Scribe wants to tell you a story!" << endl;
    break;
  case 4: //Trade
    cout << "A Scribe wants to trade with you!" << endl;
    break;
  }
}

