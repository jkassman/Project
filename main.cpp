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
  srand(time(NULL));
  Dragon myDragon;
  Golem myGolem;
  StarRunner myStarRunner;
  Scribe myScribe;
  Smuggler mySmuggler;
  Alien * myAlien = &myDragon;
  Player captain;
  Encounter myEncounter;
  myEncounter.resetScreen(&captain);

  while (1) {

    // Training Phase
    int num = rand()% 4 + 2; 		// Randomly does 2 to 4 upgrades before encounter
    for(int i=0;i<num;i++) 
    {
      myAlien=&myDragon;
      myAlien->incrTrait();
      myAlien=&myGolem;
      myGolem.incrTrait();
      myAlien=&myStarRunner;
      myStarRunner.incrTrait();
      myAlien=&myScribe;
      myScribe.incrTrait();
      myAlien=&mySmuggler;
      mySmuggler.incrTrait();
      switch(captain.upgradeAtt()) {
	case 1:
	  i--;
	  break;
	case 2:
	  return 1;	// Returns if user quit
      }
    }

    // Encounter Phase
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
