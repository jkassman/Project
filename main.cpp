#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Dragon.h"
#include "Player.h"

int main() {
  Dragon myDragon;
  Player captain;
  bool quit = false;
  while (!quit) {
    captain.upgradeAtt();
    switch (rand()% 5) {
    case 0:
      myDragon.startEncounter(&captain);
      break;
    default:
      cout << "Not coded, come back later!" << endl;
    }
    
  }
}
