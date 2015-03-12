#ifndef PLAYER_H
#define PLAYER_H

class Player {
 public:
  Player();
  void updateStats(int input, bool win);
  void updateAtt();
  int getTrait(int select);
 private:
  int trait[8];
  int attribute[4];
};

#endif
