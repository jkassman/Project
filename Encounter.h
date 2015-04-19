#ifndef ENCOUNTER_H
#define ENCOUNTER_H

//#include <string>
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
  static void changeZone(int);
  static int getMultiplier();
  static void updateMemory(int encounter, int win);
  static int getNumTotal();
  static int getWonTotal();
  static int getLostTotal();
  static int getNumInZone();
  static int getLostInZone();
  static int getWonInZone();
  static int getTradesInZone();
  static int getStoriesInZone();
  static void printAll(); //debugging
  static void printInZone(); //debugging
 private:
  static int myZone;
  static int encountersInZone[2][6]; //won-lost, encounter #
  static int encountersTotal[2][6]; //won-lost, encounter #
};

#endif
