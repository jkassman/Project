#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "Player.h"

using namespace std;

class Message
{
	public:
	  void intro(Player *);
	  void resetScreen(Player *);
	  void trainAttr(char);
	  void newEncounter(int, string);
	  void askTrait(char);
	  bool decideGood(int, int);
	  void encResults(int, int, int, string);
	  void getMad(string);
	  void getHappy(string);
          string trait2str(int);
          string encounter2str(int);
	  void unlockMessage();
};




#endif
