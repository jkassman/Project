#ifndef DRAGON_H
#define DRAGON_H

#include <vector>
#include "Alien.h"
using namespace std;

class Dragon : public Alien
{
	public:
	  Dragon();
	  void displayEncounter(int);
	private: 
};

#endif
