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
int wins=0,losses=0, enc;
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
enc=myEncounter.start( myAlien, &captain);
switch (enc) {
case 0:
losses++;
break;
case 1:
wins++;
break;
case 2:
hasQuit=1;
break;
}
}
}
cout<<"GAME OVER"<<endl;
cout<<"Total number of encounter wins: "<<wins<<endl;
cout<<"Total number of encounter losses: "<<losses<<endl;
if(losses==0)
cout<<"Perfect game! You get a cookie!"<<endl;
else
cout<<"Win/Loss Ratio: "<<(wins*1.)/losses<<endl;
}
