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
  int wins=0,losses=0;
  bool hasQuit=0;

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

  while (!hasQuit) {

    // Training Phase
    int num = rand()% 4 + 2; 		// Randomly does 2 to 5 upgrades before encounter
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
	case 1: //invalid input/debug (?)
	  i--;
	  break;
	case 2: //quit case
	  hasQuit=1;
	  i=num;
	  break;
      }
    }

    if(!hasQuit) {
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
      if(myEncounter.start( myAlien, &captain)) wins++;
      else losses++;
    }
  }

  cout<<"Total number of encounter wins: "<<wins<<endl;
  cout<<"Total number of encounter losses: "<<losses<<endl;
  cout<<"Win/Loss Ratio: "<<(wins*1.)/losses<<endl;
}
