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
#include "Message.h"

int main() {
  bool hasQuit=0;
  Message msgs;
  srand(time(NULL));
  Dragon myDragon;
  Golem myGolem;
  StarRunner myStarRunner;
  Scribe myScribe;
  Smuggler mySmuggler;
  Alien * myAlien = &myDragon;
  Player captain;
  Encounter myEncounter;
  msgs.intro(&captain);
  //msgs.resetScreen(&captain);
  while (!hasQuit) {
    // Training Phase
    myDragon.incrTrait(); //NOTE: These are only called once now. They used to
    myGolem.incrTrait(); //be called 2-5 times. The player gets +10-15 atts.
    myStarRunner.incrTrait(); //in this same space
    myScribe.incrTrait();
    mySmuggler.incrTrait();
    switch(captain.upgradeAtt()) {
    case 1: //go to encounter
      break;
    case 2: //quit case
      hasQuit=1;
      break;
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
      if (myEncounter.start( myAlien, &captain) == 2) {
	hasQuit = 1;
      }
    }
  }
  cout<<"GAME OVER"<<endl;
  cout<<"Total number of encounter wins: "<<Encounter::getWonTotal()<<endl;
  cout<<"Total number of encounter losses: "<<Encounter::getLostTotal()<<endl;
  myEncounter.printAll(); //rough debugging
  if(Encounter::getLostTotal()==0)
    cout<<"Perfect game! You get a cookie!"<<endl;
  else
    cout<<"Win/Loss Ratio: "<<(Encounter::getWonTotal()*1.)/Encounter::getLostTotal()<<endl;
}
