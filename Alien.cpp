#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Alien.h"
#include "Player.h"

using namespace std;

Alien::Alien() {
  srand(time(NULL)); //Not sure why this is needed?
}

//updates the alien's stats based on the result of the encounter.
//if the alien lost (win is true), alien gains a point in the corresponding trait. 
//Also, hostility is changed (NOTE: Should this be separate function?)
void Alien::updateStats(int encounterType, int whichTrait, bool win) {
  switch (encounterType){
    case 0: //Fight
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	  }
          break;
        case 5: //Speed
	  if (win){
	    trait[5]++;
	  }
	  else{
	    hostility--;
	  }
          break;
        case 2: //Shield
	  if (win){
	    trait[2]++;
	    hostility--;
	  }
          break;
        case 6: //Navigation
	  if (win){
	    trait[6]++;
	    hostility--;
	  }
          break;
      }
    case 1: //Threaten
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    hostility--;
	  }
          break;
        case 5: //Speed
	  if (win){
	    trait[5]++;
	  }
          break;
        case 7: //Bravery
	  if (win){
	    trait[7]++;
	    hostility--;
	  }
          break;
        case 3: //Trickery
	  if (win){
	    trait[3]++;
	    hostility++;
	  }
	  else{
	    hostility++;
	  }
          break;
      }
    case 2: //Rob
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    hostility--;
	  }
          break;
        case 5: //Speed
	  if (win){
	    trait[5]++;
	  }
          break;
        case 2: //Shield
	  if (win){
	    trait[2]++;
	  }
	  else{
	    hostility++;
	  }
          break;
        case 8: //Caution
	  if (win){
	    trait[8]++;
	  }
	  else{
	    hostility++;
	  }
          break;
      }
    case 3: //Story
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    hostility++;
	  }
	  else{
	    hostility++;
	  }
          break;
        case 5: //Speed
	  if (win){
	    trait[5]++;
	  }
          break;
        case 4: //Diplomacy
	  if (win){
	    trait[4]++;
	    hostility--;
	  }
	  else{
	    hostility++;
	  }
          break;
        case 8: //Caution
	  if (win){
	    trait[8]++;
	  }
          break;
      }
    case 4: //Trade
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    hostility++;
	  }
	  else{
	    hostility++;
	  }
          break;
        case 5: //Speed
	  if (win){
	    trait[5]++;
	  }
          break;
        case 4: //Diplomacy
	  if (win){
	    trait[4]++;
	    hostility--;
	  }
          break;
        case 3: //Trick
	  if (win){
	    trait[3]++;
	    hostility++;
	  }
	  else{
	    hostility++;
	  }
          break;
      }
    case 5: //Race
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    hostility++;
	  }
	  else{
	    hostility++;
	  }
          break;
        case 5: //Speed
	  if (win){
	    trait[5]++;
	    hostility--;
	  }
          break;
        case 6: //Navigation
	  if (win){
	    trait[6]++;
	    hostility--;
	  }
          break;
        case 7: //Bravery
	  if (win){
	    trait[7]++;
	  }
          break;
      }
  }
}

//virtual function; each alien class will override it with their own fancy
//encounter text.
//void Alien::displayEncounter(int encounter) {
  //nothing ever.
//}

//Decides if the alien will attack. True = attack.
bool Alien::hostilityRole() {
  if (hostility > 6){ //if the alien is hostile
    if (rand()%10 < 9){ //it will attack you 9 times out of 10
    return true;
    }
  }
  return false;
}

//select shouldb be between 0 and 1. Returns one of two encounters.
int Alien::getEncounter(int select) {
  if (select >= 0 && select <= 1) {
    return encounter[select];
  } else {
    cout << "Error, invalid encounter selection in Alien.cpp" << endl;
    return -1;
  }
}

int Alien::getTrait(int select) {
  return trait[select]; //Add input (select) checking!
}

void Alien::displayTraits() {
	cout<<"DEBUGGING Alien Traits"<<endl;
  int m;
  for (m = 0; m < (int) trait.size(); m++) {
    cout << trait[m] << " ";
  }
	cout<<endl;	
}

