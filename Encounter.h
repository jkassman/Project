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
  void displayResult(bool win, int encounter, int trait);
  void resetScreen(Player*);
  string encounter2str(int);
  string trait2str(int);
  string attribute2str(int);
  int getZone();
  static void changeZone(int);
  static int getMultiplier();
 private:
  static int myZone;
};

#endif
