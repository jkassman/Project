#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "Player.h"

using namespace std;

class Message
{
	public:
	  void intro();
	  void resetscreen(Player *);
	  void trainAttr(char);
	  void newEncounter(int, string);
	  void askTrait(char);
	  bool decideGood(int, int);
	  void encResults(int, int, bool, string);
	  void getMad(string);
          string trait2str(int);
          string encounter2str(int);
	  void warpMessage(int zone);
};




#endif
