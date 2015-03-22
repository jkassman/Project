#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "StarRunner.h"
#include "Alien.h"

using namespace std;

StarRunner::StarRunner()
{
// The numbers between | | are the starting values for the alien's traits
	baseTrait.push_back(3); // Hostility
	baseTrait.push_back(4);	// Against player's Laser
	baseTrait.push_back(6);	// Shield
	baseTrait.push_back(6);	// Trick
	baseTrait.push_back(5);	// Diplomacy
	baseTrait.push_back(13);// Speed
	baseTrait.push_back(8);	// Navigation
	baseTrait.push_back(2);	// Bravery
	baseTrait.push_back(6);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	for (int i =0;i<9;i++)
	  trait.push_back(baseTrait[i]+rand()%5-2); 	// Adjust starting traits
	encounter[0] = 3; //Story
	encounter[1] = 5; //Race
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

