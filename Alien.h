#ifndef ALIEN_H
#define ALIEN_H

#include "Player.h"

class Alien {
    public:
	Alien();
	int getTraitInput();
	bool challenge(int alienTrait, int playerTrait);
	bool decideGood(int input, int encounter);
	virtual void startEncounter(&Player) =0;
	virtual void displayEncounterText(int encounter) =0;
	void updateStats(int input, bool win);

    protected:
	int trait[9];
	int encounter[2];
};

#endif //!ALIEN_H
