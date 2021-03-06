#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
#include "Player.h"
#include "Alien.h"
#include "Encounter.h"
#include "Message.h"
using namespace std;

int Encounter::myZone = 0;
int Encounter::previousEncounter[3] = {0};
int Encounter::encountersInZone[2][6] = {{0}};
int Encounter::encountersTotal[2][6] = {{0}};
bool Encounter::unlockedZones[6] = {0};

//Decides the outcome of the encounter.
//TRUE means player won, false means player lost
//TAKES INTO ACCOUNT WHICH ZONE YOU ARE IN
bool Encounter::challenge(int alienTrait, int playerTrait) {
  int modifier = getMultiplier(); //2^zone
  alienTrait *= modifier;
  //if you have 0 in any trait, instantly lose.
  if (alienTrait <= 0) {
    return true;
  } else if (playerTrait <=0) {
    return false;
  }
  //create a random number from 0 to max of player/alienTrait.
  int modAlien = rand() % max(alienTrait, playerTrait);
  int modPlayer = rand() % max(alienTrait, playerTrait);
	////cout<<"ALIEN: "<<alienTrait<<" PLAYER: "<<playerTrait<<endl;
	////cout<<"MODALIEN: "<<modAlien<<" MODPLAYER: "<<modPlayer<<endl;
  if ((playerTrait + modPlayer) >= (alienTrait + modAlien)) {
    return true;
  } else {
    return false;
  }
}

//Decides if the chosen trait works in the given encounter.
//For example: Using diplomacy when a golem tries to rob you isn't going to help
bool Encounter::decideGood(int input, int encounter) {
  if (input >= 1 && input <= 8 && encounter >= 0 && encounter <= 5) {
    //nothing, good.
  } else {
    cout << "This shouldn't happen, but invalid input was passed to decideGood" << endl;
  }
  switch (encounter) {
  case 0: //Fight
    // power shields navigation speed
    if (input == 1 || input == 2 || input == 6 || (input == 5)) {
      return true;
    } else {
      break;
    }
  case 1: //Threaten
    // power bravery trickery speed
    if (input == 1 || input == 7 || input == 3 || (input == 5)) {
      return true;
    } else {
      break;
    }
  case 2: //Rob
    // power shields caution speed
    if (input == 1 || input == 2 || input == 8 || input == 5) {
      return true;
    } else {
      break;
    }
  case 3: //Story
    // power diplomacy caution speed
    if (input == 1 || input == 4 || input == 8 || input == 5) {
      return true;
    } else {
      break;
    }
  case 4: //Trade
    // power diplomacy trickery speed
    if (input == 1 || input == 4 || input == 3 || input == 5) {
      return true;
    } else {
      break;
    }
  case 5: //Race
    // power navigation bravery speed
    if (input == 1 || input == 6 || input == 7 || input == 5) {
      return true;
    } else {
      break;
    }
  }
  //it only gets here if it doesn't return true, so the person chose wrong.
  return false;
}


//main encounter logic. Displays text, get's the user's response, determines the
//outcome, and updates player and alien stats based on that outcome.
//updates encounter type with which type of encounter was used.
int Encounter::start(Alien* myAlien, Player* captain) {
  int encounter, input;
  int win;
  Message msgs;
 
  // Figure out which encounter to do
  encounter = myAlien->getEncounter(rand()%2);
  if (myAlien->hostilityRole()) {
    encounter = 0; //fight if alien is hostile enough
  }
  msgs.newEncounter(encounter,myAlien->getName());
  msgs.resetScreen(captain, 2, myAlien->getName());
  input = msgs.getTraitChoice();
  ////////// Debugging
  while(input==9) {
    myAlien->displayTraits();
    input = msgs.getTraitChoice();
  }
  //////////
  if(input==10)
    return 2;
  if (decideGood(input, encounter)) {	// Make sure input valid
    int playersum=captain->getTrait(input) + captain->getAttribute((input-1)/2);
    if (challenge(myAlien->getTrait(input), playersum)) {	// Do encounter
      win = 1;
    } else {
      win = 0;
    }
  } else {
    win = 0;
  }
  updateMemory(encounter, win, input);
  captain->updateStats(input, win);
  msgs.resetScreen(captain, 2, myAlien->getName()); //this must be called after updateMemory
  msgs.encResults(encounter, input, win, myAlien->getName());
  myAlien->updateStats(encounter, input, win);
  return win;
}

int Encounter::getZone()
{
  return myZone;
}

//increments zone if select is positive, decrements if negative
//does nothing if zero.
int Encounter::changeZone(int select)
{
  Message say;
  //myZone = select;
  if (select > 0) {
    if (myZone < MAX_ZONES && unlockedZones [myZone + 1]) {
      myZone++;
    } else {
      say.setTopBox("You haven't unlocked zone " + say.int2str(myZone+2) +" yet!");
      return 1;
    }
  } else if (select <0) {
    if (myZone > 0) {
      myZone--;
    } else {
      say.setTopBox("There is no zone before Zone 1!");
      return 1;
    }
  } else {
    //do nothing
  }
  //clear encountersInZone
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      encountersInZone[i][j] = 0;
    }
  }
  return 0;
}
int Encounter::getMultiplier()
{
  int multiplier = 1;
  //2^myZone:
  for (int i = 0; i < myZone; i++) {
    multiplier *= 2;
  }
  return multiplier;
}

void Encounter::updateMemory(int encounter, int win, int trait) {
  if (win) {
    win = 1;
  } else {
    win = 0;
  } //truncate win to 0 and 1. Probably not necessary, but if for whatever
  //reason we want win to be 5, this code won't break.
  if (encounter >= 0 && encounter <=5) {
    encountersInZone[win][encounter]++;
    encountersTotal[win][encounter]++;
    if (trait >= 1 && trait <= 8) {
       previousEncounter[0] = encounter;
       previousEncounter[1] = win;
       previousEncounter[2] = trait;
    } else {
      cout << "An invalid trait was passed to updateMemory!" << endl;
    }
  } else {
    cout << "An invalid encounter was passed to updateMemory!" << endl;
  }
}

int Encounter::getNumTotal() {
  int sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      sum += encountersTotal[i][j];
    }
  }
  return sum;
}

int Encounter::getWonTotal() {
  int sum = 0;
  for (int j = 0; j < 6; j++) {
    sum += encountersTotal[1][j];
  }
  return sum;
}

int Encounter::getLostTotal() {
  int sum = 0;
  for (int j = 0; j < 6; j++) {
    sum += encountersTotal[0][j];
  }
  return sum;
}

int Encounter::getNumInZone() {
  int sum = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      sum += encountersInZone[i][j];
    }
  }
  return sum;
}

int Encounter::getLostInZone() {
  int sum = 0;
  for (int j = 0; j < 6; j++) {
    sum += encountersInZone[0][j];
  }
  return sum;
}

int Encounter::getWonInZone() {
  int sum = 0;
  for (int j = 0; j < 6; j++) {
    sum += encountersInZone[1][j];
  }
  return sum;
}

//the number of encounters of the specified type completed successfully in the zone
int Encounter::getWonInZone(int encounter) {
  if (encounter >=0 && encounter <= 5) {
    return encountersInZone[1][encounter];
  } else {
    cout << "Error: incorrect value passed to getWonInZone(int encounter)" << endl;
    return 0;
  }
}

//returns whether or not the next zone is locked
bool Encounter::checkNextUnlock()
{
  if (myZone < MAX_ZONES) {
    return unlockedZones[myZone+1];
  } else {
    return false;
  }
}

//returns an array of the last encounter.
//encounter type, won-lost, trait used.
void Encounter::getLastEncounter(int toReturn[3])
{
  toReturn[0] = previousEncounter[0];
  toReturn[1] = previousEncounter[1];
  toReturn[2] = previousEncounter[2];
}

//Unlocks the next zone unless you are in the maximum zone
bool Encounter::unlockNext()
{
  Message say;
  if (myZone < MAX_ZONES) {
    unlockedZones[myZone+1] = true;
    return 1;
  } else {
    say.setTopBox("There is no zone beyond zone " + say.int2str(MAX_ZONES + 1));
    return 0;
  }
}
