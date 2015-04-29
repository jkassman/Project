#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Player.h"
#include "Alien.h"

class Encounter {
 public:
  const static int MAX_ZONES = 2; //min zone is 0.
  bool challenge(int alienTrait, int playerTrait);	//Decides the outcome of the encounter.
  bool decideGood(int input, int encounter);		//Decides if the chosen trait works in the given encounter.
  int start(Alien*, Player*);				//main encounter logic.
  static int getZone();
  static int changeZone(int);			//increments zone if select is positive, decrements if negative
  static int getMultiplier();			// Returns the multiplier based on current zone
  static void updateMemory(int encounter, int win, int trait);
  static int getNumTotal();			
  static int getWonTotal();
  static int getLostTotal();
  static int getNumInZone();
  static int getLostInZone();
  static int getWonInZone();
  static int getWonInZone(int encounter);	//the number of encounters of the specified type completed successfully in the zone
  static bool checkNextUnlock();		//returns whether or not the next zone is locked
  static bool unlockNext();
  static void getLastEncounter(int[3]); 	//Modifies the given array to be what previousEncunter is.
 private:
  static int myZone;
  static int previousEncounter[3]; //type, won-lost, trait used
  static int encountersInZone[2][6]; //won-lost, encounter #
  static int encountersTotal[2][6]; //won-lost, encounter #
  static bool unlockedZones[6]; //false is locked, true is unlocked
};

#endif
