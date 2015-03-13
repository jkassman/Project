#ifndef ALIEN_H
#define ALIEN_H

#include "Player.h"

class Alien {
    public:
	Alien();
	virtual void displayEncounter(int encounter) =0; //defined in each alien
	void updateStats(int input, bool win); //not coded
	bool hostilityRole(); //not coded
	int getEncounter(int select);
	int getTrait(int select);

    protected:
	int trait[9];
	int encounter[2];
	int hostility;
};

#endif //!ALIEN_H
