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
#include "Dragon.h"
#include "Golem.h"
#include "StarRunner.h"
#include "Scribe.h"
#include "Smuggler.h"
#include "Message.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//GLOBALS:
//900, 787
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 840;


//SDL Window, Renderer, (and font)
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//TTF_Font *font = NULL

//TEXTURE:
LTexture gGameScreen(gWindow, gRenderer);
LTexture gTitleScreen(gWindow, gRenderer);

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Stellarim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			gGameScreen.updateRenderer(gRenderer);
			gTitleScreen.updateRenderer(gRenderer);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load main screen
	if( !gGameScreen.loadFromFile( "Game_Screen.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !gTitleScreen.loadFromFile( "Title_Screen.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gGameScreen.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main() {
  bool hasQuit=0;
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
  
  //Start up SDL and create window
  if( !init() ) {
	 	printf( "Failed to initialize!\n" );
	} 
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
	 	else 
		{
			//Event handler
			SDL_Event e;

			//Current rendered texture
			LTexture* currentTexture = NULL;

			msgs.intro(&captain);
			//msgs.resetScreen(&captain);
			currentTexture = &gTitleScreen;
			bool showTitle = true;
			while (!hasQuit && !Message::checkVictory()) {
				//BEGIN SDL STUFF
				//Handle events on queue
				if (showTitle)
				{
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );

					//Top left corner viewport
					SDL_Rect stretchRect;
					stretchRect.x = 0;
					stretchRect.y = 0;
					stretchRect.w = SCREEN_WIDTH;
					stretchRect.h = SCREEN_HEIGHT;
					currentTexture->renderScaled( &stretchRect );

					//Update screen
					SDL_RenderPresent( gRenderer );
				}
		
				while (showTitle) 
				{
					while( SDL_PollEvent( &e ) != 0 )
					{
						//User requests quit
						if( e.type == SDL_QUIT )
						{
							showTitle = false;
							hasQuit = true;
						}
						const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
						if( currentKeyStates[ SDL_SCANCODE_1 ] )
						{
							showTitle = false;
							currentTexture = &gGameScreen;
						}
						else if ( currentKeyStates[ SDL_SCANCODE_2 ] )
						{
							system("cat instructions.txt");
						}
						else if ( currentKeyStates[ SDL_SCANCODE_3 ] )
						{
							showTitle = false;
							hasQuit = true;
						}
					}
				}
				if (!hasQuit)
				{
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );

					//Top left corner viewport
					SDL_Rect stretchRect;
					stretchRect.x = 0;
					stretchRect.y = 0;
					stretchRect.w = SCREEN_WIDTH;
					stretchRect.h = SCREEN_HEIGHT;
					currentTexture->renderScaled( &stretchRect );

					//Render current texture
					//currentTexture->render( 0, 0 );

					//Update screen
					SDL_RenderPresent( gRenderer );

					//END SDL STUFF
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
						switch (rand()% (min(4,Encounter::getZone() +2))) { //random number between 0 and myZone+1. 
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
				myAlien=&myGolem;
				break;
						case 4:
				myAlien=&myDragon;
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
			if (Message::checkVictory()) {
				cout << "CONGRATULATIONS! You have reached Stellarim and impressed all the natives!" << endl;
			} else {
				cout<<"GAME OVER"<<endl;
			}
			cout<<"Total number of encounter wins: "<<Encounter::getWonTotal()<<endl;
			cout<<"Total number of encounter losses: "<<Encounter::getLostTotal()<<endl;
			myEncounter.printAll(); //rough debugging
			if(Encounter::getLostTotal()==0)
				cout<<"Perfect game! You get a pie!"<<endl;
			else
				cout<<"Win/Loss Ratio: "<<(Encounter::getWonTotal()*1.)/Encounter::getLostTotal()<<endl;
				}
			}

	close();
	return 0;
}


