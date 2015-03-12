#include "Player.h"

Player::Player() {
  for (int i = 0; i < 8; i++) {
    trait[i] = 1;
    if (i < 4) {
      attribute[i] = 1;
    }
  }
}

//Based on which input was used and whether you won, update traits/attributes.
//If you win: +1 trait, -1 opposite trait
//if you lose: -randomish number in that attribute
void Player::updateStats(int input, bool win) {
  //nothing yet
}

//The waiting stage in between encounters.
void Player::upgradeAtt() {
  //nothing yet
}

//Return the chosen trait
int Player::getTrait(int select) {
  return trait[select]; //add range protection! (trait[1000] never happens)
}
