#ifndef ENCOUNTER_H
#define ENCOUNTER_H

//#include <string>
#include "Player.h"
#include "Alien.h"

class Encounter {
 public:
  int getTraitInput();
  bool challenge(int alienTrait, int playerTrait); //not coded
  bool decideGood(int input, int encounter); //not coded
  bool start(Alien*, Player*);
  char firstCharEntered(char* second);
  void displayResult(bool win, int encounter, int trait);
  void resetScreen(Player*);
  string encounter2str(int);
  string trait2str(int);
  string attribute2str(int);
  //void resetScreen(Player*, Alien*);
};

#endif
