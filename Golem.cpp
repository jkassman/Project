#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Golem.h"
#include "Alien.h"

using namespace std;

Golem::Golem()
{
// The numbers between | | are the starting values for the alien's traits
	baseTrait.push_back(3); // Hostility
	baseTrait.push_back(12);	// Against player's Laser
	baseTrait.push_back(5);	// Shield
	baseTrait.push_back(2);	// Trick
	baseTrait.push_back(9);	// Diplomacy
	baseTrait.push_back(2);	// Speed
	baseTrait.push_back(5);	// Navigation
	baseTrait.push_back(8);	// Bravery
	baseTrait.push_back(7);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	for (int i =0;i<9;i++)
	  trait.push_back(baseTrait[i]+rand()%5-2); 	// Adjust starting traits
	encounter[0] = 1; //Threaten
	encounter[1] = 2; //Rob
	name="Golem";
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

