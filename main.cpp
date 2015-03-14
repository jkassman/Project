#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Player.h"
#include "Encounter.h"

#include "Dragon.h"
#include "Golem.h"
#include "StarRunner.h"
#include "Scribe.h"
#include "Smuggler.h"

int main() {
  Dragon myDragon;
  Golem myGolem;
  StarRunner myStarRunner;
  Scribe myScribe;
  Smuggler mySmuggler;
  Alien * myAlien = &myDragon;
  Player captain;
  Encounter myEncounter;

  while (1) {
    if(captain.upgradeAtt()) return 1;	// Returns if user quit
    switch (rand()% 5) {
    case 0:
      myAlien=&myDragon;
      break;
    case 1:
      myAlien=&myGolem;
      break;
    case 2:
      myAlien=&myStarRunner;
      break;
    case 3:
      myAlien=&myScribe;
      break;
    case 4:
      myAlien=&mySmuggler;
      break;
    default:
      cout << "Not coded, come back later!" << endl;
    }
    myEncounter.start( myAlien, &captain);
  }
}
