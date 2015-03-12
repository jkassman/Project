#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Dragon.h"
#include "Player.h"
#include "Encounter.h"

int main() {
  Dragon myDragon;
  Alien* alienDragon = &myDragon;
  Player captain;
  Encounter myEncounter;
  bool quit = false;
  while (!quit) {
    captain.upgradeAtt();
    switch (rand()% 5) {
    case 0:
      myEncounter.start( alienDragon, &captain);
      break;
    default:
      cout << "Not coded, come back later!" << endl;
    }
  }
}
