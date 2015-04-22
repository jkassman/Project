#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Player.h"
#include "Alien.h"

class Encounter {
 public:
  const static int maxZones = 4; //min zone is 0.
  int getTraitInput();
  bool challenge(int alienTrait, int playerTrait);
  bool decideGood(int input, int encounter);
  int start(Alien*, Player*);
  char firstCharEntered(char* second);
  static int getZone();
	static int maxZone();
  static int changeZone(int);
  static int getMultiplier();
  static void updateMemory(int encounter, int win, int trait);
  static int getNumTotal();
  static int getWonTotal();
  static int getLostTotal();
  static int getNumInZone();
  static int getLostInZone();
  static int getWonInZone();
  static int getWonInZone(int encounter);
  static bool checkNextUnlock();
  static bool unlockNext();
  static void getLastEncounter(int[3]); //Modifies the given array to be what previousEncunter is.
  static void printAll(); //debugging
  static void printInZone(); //debugging
 private:
  static int myZone;
  static int previousEncounter[3]; //type, won-lost, trait used
  static int encountersInZone[2][6]; //won-lost, encounter #
  static int encountersTotal[2][6]; //won-lost, encounter #
  static bool unlockedZones[6]; //false is locked, true is unlocked
};

#endif
