#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Player.h"
#include "Alien.h"

class Encounter {
 public:
  int getTraitInput();
  bool challenge(int alienTrait, int playerTrait);
  bool decideGood(int input, int encounter);
  int start(Alien*, Player*);
  char firstCharEntered(char* second);
  static int getZone();
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
  static bool tryUnlock();
  static void printAll(); //debugging
  static void printInZone(); //debugging
 private:
  static int myZone;
  static bool systemsCheck; //whether you have won a race with navigation
  //This value is reset each zone.
  static int encountersInZone[2][6]; //won-lost, encounter #
  static int encountersTotal[2][6]; //won-lost, encounter #
  static bool unlockedZones[6]; //false is locked, true is unlocked
};

#endif
