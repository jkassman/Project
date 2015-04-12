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

