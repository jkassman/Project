#include <iostream>
#include <vector>
#ifndef SHIP_H
#define SHIP_H

using namespace std;

class Ship {
  public:
    Ship();
    void welcome();
    void printShip();
    char movePlayer();
  private:
    char ship[22][22];
};

#endif

