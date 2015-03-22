#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "Smuggler.h"
#include "Alien.h"

using namespace std;

Smuggler::Smuggler()
{
// The numbers between | | are the starting values for the alien's traits
	baseTrait.push_back(3); // Hostility
	baseTrait.push_back(3);	// Against player's Laser
	baseTrait.push_back(7);	// Shield
	baseTrait.push_back(5);	// Trick
	baseTrait.push_back(5);	// Diplomacy
	baseTrait.push_back(6);	// Speed
	baseTrait.push_back(9);	// Navigation
	baseTrait.push_back(9);	// Bravery
	baseTrait.push_back(6);	// Caution
// The numbers between| | correspond to different encounters. Must match cases below
	for (int i =0;i<9;i++)
	  trait.push_back(baseTrait[i]+rand()%5-2); 	// Adjust starting traits
	encounter[0] = 2; //Rob
	encounter[1] = 4; //Trade
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

