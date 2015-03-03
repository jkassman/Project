#ifndef DRAGON_H
#define DRAGON_H

#include<vector>
using namespace std;

class Dragon //: public Alien
{
	public:
	  Dragon();
	  int startencounter();
	  void displaystats();
	private: 
	  vector <int> trait;	// Temporary. Will be in base class
};

#endif
