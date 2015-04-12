#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include "Message.h"
using namespace std;


void Message::intro()
{

}

void Message::resetscreen(int * captain)
{
  int width = 3; //width of the traits; how much space padding to add.
                 //for example, 3 does: |  1|, | 42|, and |123| 
  system("clear");
  cout << "POWER            Lasers |"
       << setw(width) << captain[1]+captain[0] << "|"
       << setw(width) << captain[2]+captain[0]
       << "| Shields"<< endl;
  cout << "INTELLIGENCE   Trickery |"
       << setw(width) << captain[3] + captain[1] <<"|"
       << setw(width) << captain[4] + captain[1] 
       <<"| Diplomacy"<<endl;
  cout << "ENGINES           Speed |"
       << setw(width) << captain[5] + captain[2] <<"|"
       << setw(width) << captain[6] + captain[2] 
       <<"| Navigation"<<endl;
  cout << "SANITY          Bravery |"
       << setw(width) << captain[7] + captain[3] <<"|"
       << setw(width) << captain[8] + captain[3] 
       <<"| Caution"<<endl;

  cout << endl;
}

void Message::trainAttr(char attr)
{
  switch (toupper(attr)) {
    case 'S':
      cout << "You decide to take a nap on your ratty cot to calm your nerves and improve your concentration." << endl << endl;
      break;
    case 'E':
      cout << "You double check that your engines are in working condition.  Looks like they'll last a little while longer." << endl << endl;
      break;
    case 'I':
      cout << "You flip through the pages of some the old lore books stached in a nook of the ship." << endl;
      cout << "(you're too old fashioned to use the ship's databases)." << endl; 
      cout << "Some of this information could be helpful for the encounters ahead!" << endl << endl;
      break;
    case 'P':
      cout << "You fiddle with the power and shield systems aboard the ship." << endl;
      cout << "These adjustments will definitely help in the long run." << endl << endl;
      break;
    default:
      cout << "This should never happen." << endl;
      break;
  } 
}

void Message::newEncounter(int encType, string alienName)
{
  
}

void Message::askTrait(int encType)
{
}

void Message::encResults(int encType, int trait, bool win, string alienName)
{
}

void Message::getMad(string alienName)
{
}

