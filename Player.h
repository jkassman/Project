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
    int upgradeAtt();
    void updateStats(int, bool); 
    void upgradeSanity();
    void upgradeEngines();
    void upgradeIntel();
    void upgradePower();
    void debug();		// Used for coder to see stat values. Remove from final version

  private:
    vector <int> Traits;
    vector <int> Attributes;
};

#endif
