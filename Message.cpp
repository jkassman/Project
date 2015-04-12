#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include "Message.h"

using namespace std;

//Goes in main.cpp only:
void Message::intro()
{

cout << "Welcome to Stellarim. You're a wandering traveler, a mutineer recently \" freed \" from the hold of your terrible employers." << endl;
cout << "In a universe where societies had been driven apart by diesease for countless years, you are the sole member of a ship destined to encounter these foreign races." << endl;
cout << "Prepare yourself! For you are about to make universal history as you make contact with various alien species during your quest to reunite the galaxy." << endl;
}

/* Goes the in the following places:
  -End of Encounter start
  -In each case in Player::upgradeAtt()
  
*/

void Message::resetscreen(Player * captain)
{
  int width = 3; //width of the traits; how much space padding to add.
                 //for example, 3 does: |  1|, | 42|, and |123| 
  system("clear");
  cout << "POWER            Lasers |"
       << setw(width) << captain->getTrait(1)+captain->getAttribute(0) << "|"
       << setw(width) << captain->getTrait(2)+captain->getAttribute(0)
       << "| Shields"<< endl;
  cout << "INTELLIGENCE   Trickery |"
       << setw(width) << captain->getTrait(3) + captain->getAttribute(1) <<"|"
       << setw(width) << captain->getTrait(4) + captain->getAttribute(1) 
       <<"| Diplomacy"<<endl;
  cout << "ENGINES           Speed |"
       << setw(width) << captain->getTrait(5) + captain->getAttribute(2) <<"|"
       << setw(width) << captain->getTrait(6) + captain->getAttribute(2) 
       <<"| Navigation"<<endl;
  cout << "SANITY          Bravery |"
       << setw(width) << captain->getTrait(7) + captain->getAttribute(3) <<"|"
       << setw(width) << captain->getTrait(8) + captain->getAttribute(3) 
       <<"| Caution"<<endl;

  cout << endl;
}

// In Player.cpp
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

// In Encounter line 181 in encounter::start
void Message::newEncounter(int encType, string alienName)
{
  if(alienName == "Dragon") {
    switch (encType) {
      case 0: //Attack
        cout << "A Dragon attacks you!" << endl;
        break;
      case 1: //Threaten
        cout << "A Dragon threatens you!" << endl;
        break;
      case 5: //Race
        cout << "A Dragon wants to race you!" << endl;
        break;
    }
  }

  if(alienName == "Scribe") {
    switch (encType) {
      case 0: //Attack
        cout << "A Scribe attacks you!" << endl;
        break;
      case 3: //Story
        cout << "A Scribe wants to tell you a story!" << endl;
        break;
      case 4: //Trade
        cout << "A Scribe wants to trade with you!" << endl;
        break;
    }
  }

  if(alienName == "Smuggler") {
    switch (encType) {
      case 0: //Attack
        cout << "A Smuggler attacks you!" << endl;
        break;
      case 2: //Rob
        cout << "A Smuggler is trying to rob you!" << endl;
        break;
      case 4: //Trade
        cout << "A Smuggler wants to trade with you!" << endl;
        break;
    }
  }

  if(alienName == "Star Runner") {
    switch (encType) {
      case 0: //Attack
        cout << "A Star Runner attacks you!" << endl;
        break;
      case 3: //Story
        cout << "A Star Runner wants to tell you a story!" << endl;
        break;
      case 5: //Race
        cout << "A Star Runner wants to race you!" << endl;
        break;
    }
  }

  if(alienName == "Golem") {
    switch (encType) {
      case 0: //Attack
        cout << "A Golem attacks you!" << endl;
        break;
      case 1: //Threaten
        cout << "A Golem threatens you!" << endl;
        break;
     case 2: //Rob
        cout << "A Golem is trying to rob you!" << endl;
        break;
    }
  }  
}

//Goes in the beginning of the getTraitImput() in Encounter.cpp
void Message::askTrait(char encType)
{
  cout << "Do you want to use Lasers, Shields, Diplomacy, Trickery, " <<endl;
  cout << "Speed, Navigation, Bravery, or Caution? ";
}

bool Message::decideGood(int input, int encounter) {
  if (input >= 1 && input <= 8 && encounter >= 0 && encounter <= 5) {
		//nothing, good.
	} else {
		cout << "This shouldn't happen, but invalid input was passed to decideGood" << endl;
	}
	switch (encounter) {
		case 0: //Fight
			// power shields navigation speed
			if (input == 1 || input == 2 || input == 6 || (input == 5)) {
				return true;
			} else {
				break;
			}
		case 1: //Threaten
			// power bravery trickery speed
			if (input == 1 || input == 7 || input == 3 || (input == 5)) {
				return true;
			} else {
				break;
			}
		case 2: //Rob
			// power shields caution speed
			if (input == 1 || input == 2 || input == 8 || input == 5) {
				return true;
			} else {
				break;
			}
		case 3: //Story
			// power diplomacy caution speed
			if (input == 1 || input == 4 || input == 8 || input == 5) {
				return true;
			} else {
				break;
			}
		case 4: //Trade
			// power diplomacy trickery speed
			if (input == 1 || input == 4 || input == 3 || input == 5) {
				return true;
			} else {
				break;
			}
		case 5: //Race
			// power navigation bravery speed
			if (input == 1 || input == 6 || input == 7 || input == 5) {
				return true;
			} else {
				break;
		}
	}
	//it only gets here if it doesn't return true, so the person chose wrong.
	return false;
}



void Message::encResults(int encType, int trait, bool win, string alienName)
{
	if (!decideGood(trait, encType)) {
		cout << "You shouldn't use " << trait2str(trait) << " during a " << encounter2str(encType) << '.' << endl;
	}
	if (win) {
		cout << "You won the encounter!" << endl;
	} else {
		cout << "You lost the encounter!" << endl;
	}    
}

void Message::getMad(string alienName)
{
  cout << "The " << alienName << "s are mad at you!" << endl;
}

string Message::trait2str(int trait)
{
	switch (trait) {
		case 1:
			return "Lasers";
		case 2:
			return "Shields";
		case 3:
			return "Trickery";
		case 4:
			return "Diplomacy";
		case 5:
			return "Speed";
		case 6:
			return "Navigation";
		case 7:
			return "Bravery";
		case 8:
		return "Caution";
		default:
			return "ERROR: unknown trait";
	}
}

string Message::encounter2str(int encounter)
{
	switch (encounter) {
		case 0:
			return "Fight";
		case 1:
			return "Threaten";
		case 2:
			return "Rob";
		case 3:
			return "Story";
		case 4:
			return "Trade";
		case 5:
			return "Race";
		default:
			return "ERROR: Unkown encounter";
	}
}


