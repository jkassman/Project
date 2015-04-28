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
	name="Sky Runner";
}

