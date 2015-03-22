/* Lauren Kuta
   CSE 20212
   driver.cpp
   Contains a welcome function as well as a possible text-based ship we could use for upgrading attributes.
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Ship.h"

using namespace std;

int main () {
 
  char choice = 'z';
  Ship myShip;
  myShip.welcome();
  myShip.printShip();
  while(choice == 'z') {
   choice = myShip.movePlayer();
  }

  cout << "Choice: " << choice << endl;
  cout << "Hopefully will be inputted into UpgradeAtt() later on." << endl;
  
  

} 

  
  
 
 




  

