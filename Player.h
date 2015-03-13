/* Lauren Kuta
   CSE 20212
   Player.h
   Initializes the Player class, which contains data relevant to the human player
*/

#include <iostream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player {
  public:
    Player();
    void printAttributes();	//For testing purposes only
    void printTraits(); 	//For testing purposes only--as of right now
    int getTrait(int);
    int getAttribute(int);
    void setTrait(int, int);
    void setAttribute(int, int);
    void upgradeAtt(); //does nothing yet
    void updateStats(int input, bool win); //does nothing yet
    void upgradeSanity();
    void upgradeEngines();
    void upgradeIntel();
    void upgradeEnergy();

  private:
    vector <int> Traits;
    vector <int> Attributes;
};

#endif
