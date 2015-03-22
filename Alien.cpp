#include <iostream>
#include <iomanip>
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
	    trait[0]--;
	  }
          break;
        case 2: //Shield
	  if (win){
	    trait[2]++;
	    trait[0]--;
	  }
          break;
        case 6: //Navigation
	  if (win){
	    trait[6]++;
	    trait[0]--;
	  }
          break;
      }
    case 1: //Threaten
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    trait[0]--;
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
	    trait[0]--;
	  }
          break;
        case 3: //Trickery
	  if (win){
	    trait[3]++;
	    trait[0]++;
	  }
	  else{
	    trait[0]++;
	  }
          break;
      }
    case 2: //Rob
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    trait[0]--;
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
	    trait[0]++;
	  }
          break;
        case 8: //Caution
	  if (win){
	    trait[8]++;
	  }
	  else{
	    trait[0]++;
	  }
          break;
      }
    case 3: //Story
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    trait[0]++;
	  }
	  else{
	    trait[0]++;
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
	    trait[0]--;
	  }
	  else{
	    trait[0]++;
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
	    trait[0]++;
	  }
	  else{
	    trait[0]++;
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
	    trait[0]--;
	  }
          break;
        case 3: //Trick
	  if (win){
	    trait[3]++;
	    trait[0]++;
	  }
	  else{
	    trait[0]++;
	  }
          break;
      }
    case 5: //Race
      switch (whichTrait){
        case 1: //Laser
	  if (win){
	    trait[1]++;
	    trait[0]++;
	  }
	  else{
	    trait[0]++;
	  }
          break;
        case 5: //Speed
	  if (win){
	    trait[5]++;
	    trait[0]--;
	  }
          break;
        case 6: //Navigation
	  if (win){
	    trait[6]++;
	    trait[0]--;
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
  if (trait[0] > 6){ //if the alien is hostile
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
  int width = 3; //width of the traits; how much space padding to add.
                 //for example, 3 does: |  1|, | 42|, and |123| 
	cout<<"DEBUGGING "<<name<<" Traits"<<endl;
  cout << "POWER            Lasers |"
       << setw(width) << trait[1] << "|"
       << setw(width) << trait[2]
       << "| Shields"<< endl;
  cout << "INTELLIGENCE   Trickery |"
       << setw(width) << trait[3] <<"|"
       << setw(width) << trait[4]
       <<"| Diplomacy"<<endl;
  cout << "ENGINES           Speed |"
       << setw(width) << trait[5] <<"|"
       << setw(width) << trait[6]
       <<"| Navigation"<<endl;
  cout << "SANITY          Bravery |"
       << setw(width) << trait[7] <<"|"
       << setw(width) << trait[8] 
       <<"| Caution"<<endl;
  cout <<"Hostility: " << trait[0] << endl;
  cout << endl;
}

void Alien::incrTrait() {
	int upd=rand()%8+1;
	cout<<"Trait: "<<upd<<endl;
	trait[upd]=trait[upd]+rand() % 4 + 1;;
	displayTraits();
}

