#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include "Alien.h"
#include "Player.h"

using namespace std;

Alien::Alien() {
}

//updates the alien's stats based on the result of the encounter.
//if the alien lost (win is true), alien gains a point in the corresponding trait. 
//Also, hostility is changed (NOTE: Should this be separate function?)
void Alien::updateStats(int encounterType, int whichTrait, bool win) {
  if(!whichTrait) cout<<"Why are you fighting with hostility? A wild bug appeared!"<<endl;
  if(win) trait[whichTrait]+=rand()%2+4;	// Make alien stronger if it lost
  if(win && !encounterType) trait[whichTrait]+=(rand()%2+4); // Make alien much stronger if it lost a fight
cout<<"*************Hostility: "<<trait[0]<<endl;
  switch (encounterType){
    case 0: //Fight
      switch (whichTrait){
        case 5: //Speed
	  if (!win) trait[0]--;
          break;
        case 2: //Shield
	  trait[0]--;
          break;
        case 6: //Navigation
	  if (win) trait[0]--;
          break;
      }
      break;
    case 1: //Threaten
      switch (whichTrait){
        case 1: //Laser
	  if (!win) trait[0]++;
          break;
        case 5: //Speed
	  if (!win) trait[0]++;
          break;
        case 7: //Bravery
	  if (win) trait[0]--;
          break;
        case 3: //Trickery
	  if (win) trait[0]--;
          break;
      }
      break;
    case 2: //Rob
      switch (whichTrait){
        case 1: //Laser
	  if (!win) trait[0]++;
          break;
        case 2: //Shield
	  if (win) trait[0]--;
          break;
        case 5: //Speed
	  if (!win) trait[0]++;
          break;
        case 8: //Caution
	  if (win) trait[0]--;
          break;
      }
      break;
    case 3: //Story
      switch (whichTrait){
        case 1: //Laser
	  trait[0]++;
          break;
        case 5: //Speed
	  if (win) trait[0]++;
          break;
        case 4: //Diplomacy
	  if (win) trait[0]--;
          break;
        case 8: //Caution
	  if (win) trait[0]--;
          break;
      }
      break;
    case 4: //Trade
      switch (whichTrait){
        case 1: //Laser
	  if(win) trait[0]++;
          break;
        case 4: //Diplomacy
	  if(win) trait[0]--;
          break;
        case 3: //Trick
	  if(win) trait[0]--;
	  else trait[0]++;
          break;
      }
      break;
    case 5: //Race
      switch (whichTrait){
        case 1: //Laser
	  if (win) trait[0]++;
          break;
        case 5: //Speed
	  if (win) trait[0]--;
          break;
        case 6: //Navigation
	  if (win) trait[0]--;
          break;
        case 7: //Bravery
	  if (!win) trait[0]++;
          break;
      }
      break;
    default:
	cout<<"A wild bug appeared! That's not an encounter!"<<endl;
	break;
  }
cout<<"*************Hostility: "<<trait[0]<<endl;
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
	int sel;
	int sum;
	int numruns=(rand()%7+5);

	for(int j=0;j<numruns;j++)
	{
	  sum=0;
	  sel=rand()%50;
	  // Choose a random trait to upgrade. More likely to upgrade traits with higher base trait
	  for(int i=1;i<9;i++)
	  {
if(!i) cout<<"Why are you raising hostility here? A wild bug appeared!"<<endl;
	    if(sel>=sum && sel<sum+baseTrait[i])
	      trait[i]++;
	    sum=sum+baseTrait[i];
	  }
	}
}

