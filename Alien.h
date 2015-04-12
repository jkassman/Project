#ifndef ALIEN_H
#define ALIEN_H

#include<vector>
#include "Player.h"
#include<string>

class Alien {
    public:
	Alien();
	void updateStats(int encounterType, int whichTrait, bool win);
	bool hostilityRole();
	int getEncounter(int select);
	int getTrait(int select);
	void incrTrait();
	void displayTraits();
	string getName();

    protected:	// All initialized in each species' constructor
	vector <int> trait;
	vector <int> baseTrait;
	int encounter[2];
	string name;
};

#endif //!ALIEN_H
