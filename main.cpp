#include <iostream>
#include <time.h>
#include <cstdlib>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "LTexture.h"
#include "Player.h"
#include "Encounter.h"
#include "species/Dragon.h"
#include "species/Golem.h"
#include "species/StarRunner.h"
#include "species/Scribe.h"
#include "species/Smuggler.h"
#include "Message.h"


int main() {
  bool hasQuit = false;
  Message msgs;
  srand(time(NULL));
  Dragon myDragon;
  Golem myGolem;
  StarRunner myStarRunner;
  Scribe myScribe;
  Smuggler mySmuggler;
  Alien * myAlien = &myDragon;
  Player captain;
  Encounter myEncounter;
  
  if( !Message::init_SDL() ) { //needs to be called first thing
	 	printf( "Failed to initialize!\n" );
	} 
	else
	{
		//Load media
		if( !msgs.loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
	 	else 
		{
			msgs.intro(&captain);
			bool firstTime = true;
			while (!hasQuit && !Message::checkVictory()) {
					//Start up SDL and create window
					if (firstTime)
					{
						if (msgs.showTitleScreen()) //if title screen was quit
						{
							break;
						}
					}
					firstTime = false;
					// Training Phase
					myDragon.incrTrait(); //NOTE: These are only called once now. They used to
					myGolem.incrTrait(); //be called 2-5 times. The player gets +10-15 atts.
					myStarRunner.incrTrait(); //in this same space
					myScribe.incrTrait();
					mySmuggler.incrTrait();
					switch(captain.upgradeAtt()) {
					case 1: //go to encounter
						break;
					case 2: //quit case
						hasQuit=1;
						break;
					}
					if(!hasQuit) {
						// Encounter Phase
						switch (rand()% (min(5,Encounter::getZone() +2))) { //random number between 0 and myZone+1. 
						case 0:
							myAlien=&myStarRunner;
							break;
						case 1:
							myAlien=&myScribe;
							break;
						case 2:
							myAlien=&mySmuggler;
							break;
						case 3:
							myAlien=&myDragon;
							break;
						case 4:
							myAlien=&myGolem;
							break;
						default:
							cout << "Not coded, come back later!" << endl;
						}
						if (myEncounter.start( myAlien, &captain) == 2) {
							hasQuit = 1;
						}
					}
				}
			}
			if(Encounter::getLostTotal() != 0 || Encounter::getWonTotal() != 0){ 
				if (Message::checkVictory()) {
					cout << "CONGRATULATIONS! You have reached Stellarim and impressed all the natives!" << endl;
				} else {
					cout<<"GAME OVER"<<endl;
				}
				cout<<"Total number of encounter wins: "<<Encounter::getWonTotal()<<endl;
				cout<<"Total number of encounter losses: "<<Encounter::getLostTotal()<<endl;
				//myEncounter.printAll(); //rough debugging
				if(Encounter::getLostTotal()==0)
					cout<<"Perfect game! You get a pie!"<<endl;
				else
					cout<<"Win/Loss Ratio: "<<(Encounter::getWonTotal()*1.)/Encounter::getLostTotal()<<endl;
				}
			}
	msgs.close();
	return 0;
}


