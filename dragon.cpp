#include<iostream>
#include "dragon.h"
#include <time.h>
#include <cstdlib>
#include<vector>
using namespace std;

Dragon::Dragon()
{
	srand(time(NULL));
	trait.push_back(0); 	// Store dummy in 0

	trait.push_back(8+rand()%5-2);	// Laser
	trait.push_back(10+rand()%5-2);	// Shield
	trait.push_back(4+rand()%5-2);	// Trick
	trait.push_back(6+rand()%5-2);	// Diplomacy
	trait.push_back(9+rand()%5-2);	// Speed
	trait.push_back(6+rand()%5-2);	// Navigation
	trait.push_back(8+rand()%5-2);	// Bravery
	trait.push_back(4+rand()%5-2);	// Caution
}

int Dragon::startencounter()
{

}

void Dragon::displaystats()
{
	cout<<"Laser: \t\t"<<trait[1]<<endl;
	cout<<"Shield: \t"<<trait[2]<<endl;
	cout<<"Trick: \t\t"<<trait[3]<<endl;
	cout<<"Diplomacy: \t"<<trait[4]<<endl;
	cout<<"Speed: \t\t"<<trait[5]<<endl;
	cout<<"Navigation: \t"<<trait[6]<<endl;
	cout<<"Bravery: \t"<<trait[7]<<endl;
	cout<<"Caution: \t"<<trait[8]<<endl;
}
