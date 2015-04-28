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
    Player();				// Initialize Traits and Attributes
    void printAttributes();
    void printTraits(); 	
    int getTrait(int);
    int getAttribute(int);
    void setTrait(int, int);
    void setAttribute(int, int);
    int upgradeAtt(); 			//asks the user to upgrade attributes 3-5 times.
    void updateStats(int, bool); 	// Change player stats after encounter
    void debug();			// Prints player info for debugging
    int highestTrait();

  private:
    vector <int> Traits;	
    vector <int> Attributes;
};

#endif
