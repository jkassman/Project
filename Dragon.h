#ifndef DRAGON_H
#define DRAGON_H

#include<vector>
#include "Alien.h"
using namespace std;

class Dragon : public Alien
{
	public:
	  Dragon();
	  int startencounter();
	  void displaystats();
	  virtual void displayEncounter(int encounter);
	  //virtual void displayTraits();
	private: 
	 // vector <int> trait;	// Temporary. Will be in base class
};

#endif
