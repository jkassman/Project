#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <math.h>
#include "Message.h"
#include "Encounter.h"

using namespace std;

bool Message::myVictory = false;

void Message::intro(Player * captain)
{
  int width = (log10(captain->highestTrait())) + 1; 
  //width of the traits; how much space padding to add.
                 //for example, 3 does: |  1|, | 42|, and |123| 
  system("clear");
cout << endl<<"Stellarim is the story of your quest to find freedom from the oppression of your past. You have stolen a starship and are fleeing through the galaxy. Your enemies are hunting you, but you might be able to get help from some of alien species in the universe. However, these species might become additional enemies just as easily, depending on how you deal with them."<<endl; 
cout<<"Your goal is to reach Stellarim, a section of the galaxy so far away from civilization that you will easily be able to avoid all those who seek to destroy you. In this galaxy, you must grow as strong as possible without making too many others afraid of you. You must move quickly through the zones while gathering resources and power. You must reach Stellarim alive."<< endl<<endl<<endl;

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
  cout<< "You are currently in zone "<<Encounter::getZone()+1<<"."<<endl;

  cout << endl;
}

void Message::resetScreen(Player * captain)
{
  int width = (log10(captain->highestTrait())) + 1; 
  //width of the traits; how much space padding to add.
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
  cout<< "You are currently in zone "<<Encounter::getZone()+1 <<"."<<endl;
  if (Encounter::getZone() == Encounter::maxZone())  {
    finalUnlockMessage();
  } else {
    unlockMessage();
  }
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

// In Encounter line 181 in encounter::start ADDED
// Is alien::displayencounter
void Message::newEncounter(int encType, string alienName)
{

  cout<<"A "<<alienName;
  switch (encType){
      case 0: //Attack
        cout << " attacks you!" << endl;
        break;
      case 1: //Threaten
        cout << " threatens you!" << endl;
        break;
      case 2: //Rob
        cout << " is trying to rob you!" << endl;
        break;
      case 3: //Story
        cout << " wants to tell you a story!" << endl;
        break;
      case 4: //Trade
        cout << " wants to trade with you!" << endl;
        break;
      case 5: //Race
        cout << " wants to race you!" << endl;
        break;
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



void Message::encResults(int encType, int trait, int win, string alienName)
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
  cout << "The " << alienName << "s seem upset!" << endl;
}

void Message::getHappy(string alienName)
{
  cout << "The " << alienName << "s are pleased with your actions!" << endl;
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

void Message::unlockMessage() {
  //Encounter stats;
  int requiredStories = 2;
  int requiredTrades = 2;
  int story = Encounter::getWonInZone(3);
  int trade = Encounter::getWonInZone(4);
  int storiesLeft = requiredStories - story;
  int tradesLeft = requiredTrades -trade;
  if (storiesLeft < 0) storiesLeft = 0;
  if (tradesLeft < 0) tradesLeft = 0;
  if (!Encounter::checkNextUnlock()) { //if next zone is not unlocked.
    cout << "Unlock next zone: ";
    if (tradesLeft > 0 || storiesLeft > 0) {
      cout << "\t Stor" << ((storiesLeft > 1) ? "ies":"y") << ": " << storiesLeft;
      cout << "\t Trade" << ((tradesLeft > 1) ? "s":"") << ": " << tradesLeft;
    } else {
      int prev[3];
      Encounter::getLastEncounter(prev);
      if (!(prev[0] == 5 && prev[1] && prev[2] == 6)) { //if NOT (race and win and navigation
	cout << "Win a Race with Navigation to test your new equipment!";
      } else {
	if (Encounter::unlockNext()) {
	  cout << "Congratulations! Next Zone unlocked!";
	}
      }
    }
    cout << endl;
  }
}

void Message::finalUnlockMessage() 
{
  bool wonGame = true;
  //you must win one of every type of encounter except fight.
  cout << "Encounters left:\t";
  for (int i = 1; i <= 5; i++) {
    if (!Encounter::getWonInZone(i)) {
      cout << encounter2str(i) << "\t";
      wonGame = false;
    }
  }
  if (wonGame) {
    myVictory = true;
  }
  cout << endl;
}

//return true if the game is won, false otherwise.
bool Message::checkVictory() 
{
  return myVictory;
}

