#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Dragon.h"
#include "Alien.h"

using namespace std;

Dragon::Dragon()
{
// The numbers between | | are the starting values for the alien's traits
	baseTrait.push_back(3); // Hostility
	baseTrait.push_back(7);	// Against player's Laser
	baseTrait.push_back(9);	// Shield
	baseTrait.push_back(4);	// Trick
	baseTrait.push_back(6);	// Diplomacy
	baseTrait.push_back(7);	// Speed
	baseTrait.push_back(5);	// Navigation
	baseTrait.push_back(8);	// Bravery
	baseTrait.push_back(4);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	for (int i =0;i<9;i++)
	  trait.push_back(baseTrait[i]+rand()%5-2); 	// Adjust starting traits
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

