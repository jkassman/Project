#ifndef ALIEN_H
#define ALIEN_H

#include<vector>
#include "Player.h"
#include<string>

class Alien {
    public:
	Alien();
	void updateStats(int encounterType, int whichTrait, bool win);  //updates the alien's stats based on the result of the encounter.
	bool hostilityRole();		//Decides if the alien will attack.
	int getEncounter(int select);	// Returns the encounter that the alien will have
	int getTrait(int select);	// Returns the value of given trait
	void incrTrait();		// Increase the alien's various traits
	void displayTraits();		// Display's aliens traits for debugging purposes
	string getName();

    protected:	// All initialized in each species' constructor
	vector <int> trait;		// Vector storing all of the aliens traits. trait[0]=hostility
	vector <int> baseTrait;		// Stores the alien's starting traits
	int encounter[2];
	string name;
};

#endif //!ALIEN_H
