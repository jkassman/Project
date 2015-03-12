#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Player.h"
#include "Alien.h"

class Encounter {
 public:
  int getTraitInput();
  bool challenge(int alienTrait, int playerTrait);
  bool decideGood(int input, int encounter);
  void start(Alien*, Player*);
  char firstCharEntered(char* second);
};

#endif
