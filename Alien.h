#ifndef ALIEN_H
#define ALIEN_H

#include "Player.h"

class Alien {
    public:
	Alien();
	virtual void displayEncounterText(int encounter) =0;
	void updateStats(int input, bool win);
	bool hostilityRole();	

    protected:
	int trait[9];
	int encounter[2];
	int hostility;
};

#endif //!ALIEN_H
