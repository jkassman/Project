#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Golem.h"
#include "Alien.h"

using namespace std;

Golem::Golem()
{
	srand(time(NULL));
	trait.push_back(0); 	// Store dummy in 0
// The numbers between | | are the starting values for the alien's traits
	trait.push_back(12+rand()%5-2);	// Against player's Laser
	trait.push_back(5+rand()%5-2);	// Shield
	trait.push_back(9+rand()%5-2);	// Diplomacy
	trait.push_back(2+rand()%5-2);	// Trick
	trait.push_back(2+rand()%5-2);	// Speed
	trait.push_back(5+rand()%5-2);	// Navigation
	trait.push_back(8+rand()%5-2);	// Bravery
	trait.push_back(7+rand()%5-2);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	encounter[0] = 1; //Threaten
	encounter[1] = 2; //Rob
	hostility = 3; //Just to initialize it, I forgot what we decided on hostility randomness.
}

//displays text for each encounter the Golem can be in, specific to the Golem.
void Golem::displayEncounter(int thisencounter) {
	//very simple version:
  switch (thisencounter) {
  case 0: //Attack
    cout << "A Golem attacks you!" << endl;
    break;
  case 1: //Threaten
    cout << "A Golem threatens you!" << endl;
    break;
  case 2: //Rob
    cout << "A Golem is trying to rob you!" << endl;
    break;
  }
}

