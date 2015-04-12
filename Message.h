#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
using namespace std;

class Message
{
	public:
	  void intro();
	  void resetscreen(int *);
	  void trainAttr(char);
	  void newEncounter(int, string);
	  void askTrait(int);
	  void encResults(int, int, bool, string);
	  void getMad(string);
};




#endif
