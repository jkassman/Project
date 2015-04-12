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
<<<<<<< HEAD
  int start(Alien*, Player*);
=======
  bool start(Alien*, Player*);
>>>>>>> 8e0973494f7c9245d8ee6a8ad2fba341dfda1068
  char firstCharEntered(char* second);
  void displayResult(bool win, int encounter, int trait);
  void resetScreen(Player*);
  string encounter2str(int);
  string trait2str(int);
  string attribute2str(int);
<<<<<<< HEAD
=======
  int getZone();
  void changeZone(int select);
 private:
  static int myZone;
>>>>>>> 8e0973494f7c9245d8ee6a8ad2fba341dfda1068
};

#endif
