#ifndef ALIEN_H
#define ALIEN_H

#include<vector>
#include "Player.h"

class Alien {
    public:
	Alien();
	virtual void displayEncounter(int) =0; //defined in each alien
	void updateStats(int encounterType, int whichTrait, bool win); //not coded
	bool hostilityRole();
	int getEncounter(int select);
	int getTrait(int select);
	void displayTraits();

    protected:
	vector <int> trait;
	int encounter[2];
	int hostility;
};

#endif //!ALIEN_H
