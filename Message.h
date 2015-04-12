#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
class Message
{
	public:
	  void intro();
	  void resetscreen(int *);
	  void trainAttr(int);
	  void newEncounter(int, string);
	  void askTrait(int);
	  void encResults(int, int, bool, string);
	  void getMad(string);
}




#endif
