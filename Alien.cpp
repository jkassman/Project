#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>

#include "Encounter.h"
#include "Alien.h"
#include "Player.h"
#include "Message.h"

using namespace std;
Alien::Alien() {
}
//updates the alien's stats based on the result of the encounter.
//if the alien lost (win is true), alien gains points in the corresponding trait.
//Also, hostility is changed
void Alien::updateStats(int encounterType, int whichTrait, bool win) {
  int incr=5;	// Value to increase trait by per loss. Note is later multiplied by zone multiplier
  Message say;

  if(!whichTrait) cout<<"Why are you fighting with hostility? A wild bug appeared!"<<endl;
  if(win) trait[whichTrait]+=incr; // Make alien stronger if it lost
  // Do the same thing again if the encounter was a fight:
  if(win && !encounterType) trait[whichTrait]+=incr;

  // Hostility cases: Increase hostility(getMad) or decrease(getHappy) depending on what 
  // type of encounter it was and what trait was used in the encounter
  switch (encounterType){ 
  case 0: //Fight
    switch (whichTrait){ 
    case 5: //Speed
      if (!win) 
      {
	 trait[0]--;
	 say.getHappy(name);
      }
      break;
    case 2: //Shield
      trait[0]--;
      say.getHappy(name);
      break;
    case 6: //Navigation
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    }
    break;
  case 1: //Threaten
    switch (whichTrait){
    case 1: //Laser
      if (!win) 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    case 5: //Speed
      if (!win) 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    case 7: //Bravery
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    case 3: //Trickery
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    }
    break;
  case 2: //Rob
    switch (whichTrait){
    case 1: //Laser
      if (!win) 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    case 2: //Shield
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    case 5: //Speed
      if (!win) 
      {
         trait[0]++;
	say.getMad(name);
      }
      break;
    case 8: //Caution
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    }
    break;
  case 3: //Story
    switch (whichTrait){
    case 1: //Laser
      if (win)
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    case 5: //Speed
      if (win) 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    case 4: //Diplomacy
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    case 8: //Caution
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    }
    break;
  case 4: //Trade
    switch (whichTrait){
    case 1: //Laser
      if(win) 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    case 4: //Diplomacy
      if(win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    case 3: //Trick
      if(win) 
      {
	trait[0]--;
	say.getHappy(name);
      }
      else 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    }
    break;
  case 5: //Race
    switch (whichTrait){
    case 1: //Laser
      if (win) 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    case 5: //Speed
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    case 6: //Navigation
      if (win) 
      {
        trait[0]--;
	say.getHappy(name);
      }
      break;
    case 7: //Bravery
      if (!win) 
      {
        trait[0]++;
	say.getMad(name);
      }
      break;
    }
    break;
  default:
    cout<<"A wild bug appeared! That's not an encounter!"<<endl;
    break;
  }
  if(trait[0]<-5) trait[0]=-5;
  if(trait[0]>15) trait[0]=15;
}

//Decides if the alien will attack. True = attack.
bool Alien::hostilityRole() {
  if (trait[0] >5) { //if the alien is mad enough
    //Decide if it will fight
    // Probability=hostility*10%
    if ((rand() % 100) < trait[0] * 10) { 
      return true;
    }
  }
  return false;
}

// Returns the encounter that the alien will have
//select should be between 0 and 1. Returns one of two encounters.
int Alien::getEncounter(int select) {
  if (select >= 0 && select <= 1) {
    return encounter[select];
  } else {
    cout << "Error, invalid encounter selection in Alien.cpp" << endl;
    return -1;
  }
}

// Returns the value of given trait
int Alien::getTrait(int select) {
  return trait[select]; //Add input (select) checking!
}

// Display's aliens traits for debugging purposes
void Alien::displayTraits() {
  int width = 3; //width of the traits; how much space padding to add.
  //for example, 3 does: | 1|, | 42|, and |123|
  int displayTrait[9];
  for (int i = 1; i <= 8; i++) {
    displayTrait[i] = Encounter::getMultiplier() * trait[i];
  }
  cout<<"DEBUGGING "<<name<<" Traits"<<endl;
  cout << "POWER            Lasers |"
       << setw(width) << displayTrait[1] << "|"
       << setw(width) << displayTrait[2]
       << "| Shields"<< endl;
  cout << "INTELLIGENCE   Trickery |"
       << setw(width) << displayTrait[3] <<"|"
       << setw(width) << displayTrait[4]
       <<"| Diplomacy"<<endl;
  cout << "ENGINES           Speed |"
       << setw(width) << displayTrait[5] <<"|"
       << setw(width) << displayTrait[6]
       <<"| Navigation"<<endl;
  cout << "SANITY          Bravery |"
       << setw(width) << displayTrait[7] <<"|"
       << setw(width) << displayTrait[8]
       <<"| Caution"<<endl;
  cout <<"Hostility: " << trait[0] << endl;
  cout << endl;
}

// Increase the alien's various traits
void Alien::incrTrait() {
  int sel;
  int sum;
  int numruns=(rand()%5+6); //6-10
  for(int j=0;j<numruns;j++)
    {
      sum=0;
      sel=rand()%50;
      // Choose a random trait to upgrade. More likely to upgrade traits with higher base trait
      for(int i=1;i<9;i++)
	{
	  if(!i) cout<<"Why are you raising hostility here? A wild bug appeared!"<<endl;
	  if(sel>=sum && sel<(sum+baseTrait[i]))
	    trait[i]++;
	  sum=sum+baseTrait[i];
	}
    }
}

string Alien::getName()
{	return name;}
