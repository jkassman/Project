#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Ship.h"

using namespace std;

Ship::Ship() {
  for(int i = 0; i <= 21; i++) {
    for(int j = 0; j <= 21; j++) {
      ship[i][j] = ' ';
      ship[0][j] = '-';  //Boarders of the ship
      ship[21][j] = '-';
      ship[i][0] = '-';
      ship[i][21] = '-';

      ship[0][0] = 'o';
      ship[0][21] = 'o';  //More pretty boarders of the ship
      ship[21][0] = 'o';
      ship[21][21] = 'o';

      ship[1][11] = 'S';
      ship[11][1] = 'G';  //Attributes to be upgraded
      ship[11][20] = 'I';
      ship[20][11] = 'E';
     
     ship[11][11] = 'P'; //Player starting position
    }
  }
}

//A simple welcome function. We probably should have more instructions in the readme. Feel free to change if needed.

void Ship::welcome() {
    cout << "Welcome to [insert name of game here].  You're a wandering traveler, a mutineer recently \" freed \" from the the iron hold of the III (Intergalatic Infection Isolators)." << endl;
  cout << "In a universe where societies had been driven apart by diesease for countless years, you are the sole member of a ship doomed to encounter these foreign races."  << endl;
  cout << "Prepare yourself!  For you are about to make universal history as you make contact with various alien species during your quest to reunite the galaxy." << endl;
}

void Ship::printShip() {
  for(int m = 0; m <= 21; m++) {
    for(int n = 0; n <= 21; n++) { //Print entire ship array
      cout << ship[m][n];
    }
    cout << endl;
  }
}

char Ship::movePlayer() {

cout << "In here" << endl;
  char movement;
  char returns;
  int PosX, PosY;
 
while(movement != 'q') {
for(int i = 0; i < 22; i++) {
    for(int j = 0; j < 22; j++) {
      if(ship[i][j] == 'P') {
        PosX = i; 
        PosY = j;
      }
    }
  }
    cout << "Press a, w, s, d to move." << endl;
    cin >> movement;
    switch(movement) {
      case 'a':
        if(ship[PosX][PosY-1] == '-') {
          cout << "You can't move there! You'd fall off the ship!" << endl;
        }else if(ship[PosX][PosY-1] == 'S') {
	   cout << "Would you like to update your Sanity?" << endl;
           returns = 'S';
           movement = 'q';
        }else if(ship[PosX][PosY-1] == 'G') {
	   cout << "Would you like to update your Engines?" << endl; 
           returns = 'G';
           movement = 'q';
        }else if(ship[PosX][PosY-1] == 'I') {
	   cout << "Would you like to update your Intelligence?" << endl; 
           returns = 'I';
           movement = 'q';
        }else if(ship[PosX][PosY-1] == 'E') {
	   cout << "Would you like to update your Energy?" << endl; 
           returns = 'E';
           movement = 'q';
        }else{
           ship[PosX][PosY-1] = 'P';
           ship[PosX][PosY] = ' ';
           printShip();
        }
        break;
      case 'd':
        if(ship[PosX][PosY+1] == '-') {
          cout << "You can't move there! You'd fall off the ship!" << endl;
        }else if(ship[PosX][PosY+1] == 'S') {
	   cout << "Would you like to update your Sanity?" << endl;
           returns = 'S';
           movement = 'q';
        }else if(ship[PosX][PosY+1] == 'G') {
	   cout << "Would you like to update your Engines?" << endl; 
           returns = 'G';
           movement = 'q';
        }else if(ship[PosX][PosY+1] == 'I') {
	   cout << "Would you like to update your Intelligence?" << endl; 
           returns = 'I';
           movement = 'q';
        }else if(ship[PosX][PosY+1] == 'E') {
	   cout << "Would you like to update your Energy?" << endl; 
           returns = 'E';
           movement = 'q';
        }else{
           ship[PosX][PosY+1] = 'P';
           ship[PosX][PosY] = ' ';
           printShip();
        }
        break;
      case 's':
        if(ship[PosX+1][PosY] == '-') {
          cout << "You can't move there! You'd fall off the ship!" << endl;
        }else if(ship[PosX+1][PosY] == 'S') {
	   cout << "Would you like to update your Sanity?" << endl;
           returns = 'S';
           movement = 'q';
        }else if(ship[PosX+1][PosY] == 'G') {
	   cout << "Would you like to update your Engines?" << endl; 
           returns = 'G';
           movement = 'q';
        }else if(ship[PosX+1][PosY] == 'I') {
	   cout << "Would you like to update your Intelligence?" << endl; 
           returns = 'I';
           movement = 'q';
        }else if(ship[PosX+1][PosY] == 'E') {
	   cout << "Would you like to update your Energy?" << endl; 
           returns = 'E';
           movement = 'q';
        }else{
           ship[PosX+1][PosY] = 'P';
           ship[PosX][PosY] = ' ';
           printShip();
        }
        break;
      case 'w':
        if(ship[PosX-1][PosY] == '-') {
          cout << "You can't move there! You'd fall off the ship!" << endl;
        }else if(ship[PosX-1][PosY] == 'S') {
	   cout << "Would you like to update your Sanity?" << endl;
           returns = 'S';
           movement = 'q';
        }else if(ship[PosX-1][PosY] == 'G') {
	   cout << "Would you like to update your Engines?" << endl; 
           returns = 'G';
           movement = 'q';
        }else if(ship[PosX-1][PosY] == 'I') {
	   cout << "Would you like to update your Intelligence?" << endl; 
           returns = 'I';
           movement = 'q';
        }else if(ship[PosX-1][PosY] == 'E') {
	   cout << "Would you like to update your Energy?" << endl; 
           returns = 'E';
           movement = 'q';
        }else{
           ship[PosX-1][PosY] = 'P';
           ship[PosX][PosY] = ' ';
           printShip();
        }
        break; 
     case 'q':
       movement = 'q';
       break;
     default:
       cout << "Enter another key, please." << endl;
       break;
    }
  }
  return returns;
}
