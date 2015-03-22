#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "StarRunner.h"
#include "Alien.h"

using namespace std;

StarRunner::StarRunner()
{
	srand(time(NULL));
	trait.push_back(0); 	// Store dummy in 0
// The numbers between | | are the starting values for the alien's traits
	trait.push_back(4+rand()%5-2);	// Against player's Laser
	trait.push_back(6+rand()%5-2);	// Shield
	trait.push_back(6+rand()%5-2);	// Trick
	trait.push_back(5+rand()%5-2);	// Diplomacy
	trait.push_back(13+rand()%5-2);	// Speed
	trait.push_back(8+rand()%5-2);	// Navigation
	trait.push_back(2+rand()%5-2);	// Bravery
	trait.push_back(6+rand()%5-2);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	encounter[0] = 3; //Story
	encounter[1] = 5; //Race
	hostility = 3; //Just to initialize it, I forgot what we decided on hostility randomness.
	name="Star Runner";
}

//displays text for each encounter the dragon can be in, specific to the dragon.
void StarRunner::displayEncounter(int thisencounter) {
	//very simple version:
  switch (thisencounter) {
  case 0: //Attack
    cout << "A Star Runner attacks you!" << endl;
    break;
  case 3: //Story
    cout << "A Star Runner wants to tell you a story!" << endl;
    break;
  case 5: //Race
    cout << "A Star Runner wants to race you!" << endl;
    break;
  }
}

