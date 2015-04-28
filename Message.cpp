#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <math.h>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "LTexture.h"
#include "Message.h"
#include "Encounter.h"

using namespace std;

SDL_Window* Message::gWindow = NULL;
SDL_Renderer* Message::gRenderer = NULL;
TTF_Font* Message::gFont = NULL;

//TEXTURE:
LTexture Message::gTrainingScreen;
LTexture Message::gEncounterScreen;
LTexture Message::gTitleScreen;
LTexture Message::gMessage;

string Message::topBox = " ";
string Message::bottomBox = " ";
string Message::unlockBox = " ";

bool Message::myVictory = false;

bool Message::init_SDL()
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

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Message::loadMedia()
{
	//Loading success flag
	bool success = true;
	//Load main screen
	if( !gTrainingScreen.loadFromFile( "BGs/Training.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !gTitleScreen.loadFromFile( "Title_Screen.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if ( !gEncounterScreen.loadFromFile( "BGs/Encounter.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont( "OCRAEXT.TTF", 20 );
	//gMessage.initFont(gFont);
	if( gFont == NULL )
	{
		printf( "Failed to OCR Extended font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	return success;
}

void Message::close()
{
	//Free loaded images
	gTrainingScreen.free();
	gTitleScreen.free();
	gMessage.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//returns true if quit
bool Message::showTitleScreen()
{
	bool quit = false;
	//Current rendered texture
	LTexture* currentTexture = NULL;

	currentTexture = &gTitleScreen;
	bool showTitle = true;

	//Event handler
	SDL_Event e;

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
					quit = true;
				}
				const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				if( currentKeyStates[ SDL_SCANCODE_1 ] )
				{
					showTitle = false;
				}
				else if ( currentKeyStates[ SDL_SCANCODE_2 ] )
				{
					system("cat instructions.txt");
				}
				else if ( currentKeyStates[ SDL_SCANCODE_3 ] )
				{
					showTitle = false;
					quit = true;
				}
			}
		}
	return quit;
}

char Message::getAttrChoice()
{
	SDL_Event e;
	bool chosen = false;
	char toReturn;
	while (!chosen)
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				chosen = true;
				toReturn = 'Q';
			}
			const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
			if( currentKeyStates[ SDL_SCANCODE_1 ] )
			{
				chosen = true;
				toReturn = 'P';
			}
			else if ( currentKeyStates[ SDL_SCANCODE_2 ] )
			{
				chosen = true;
				toReturn = 'I';
			}
			else if ( currentKeyStates[ SDL_SCANCODE_3 ] )
			{
				chosen = true;
				toReturn = 'E';
			}
			else if ( currentKeyStates[ SDL_SCANCODE_4 ] )
			{
				chosen = true;
				toReturn = 'S';
			}
			else if ( currentKeyStates[ SDL_SCANCODE_MINUS ] )
			{
				chosen = true;
				toReturn = '0';
			}
			else if ( currentKeyStates[ SDL_SCANCODE_EQUALS ] )
			{
				chosen = true;
				toReturn = '1';
			}
		}
	}
	return toReturn;
}

void Message::showScreen(LTexture* toDisplay)
{
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Stretch to fit screen
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	toDisplay->renderScaled( &stretchRect );
}

void Message::intro(Player * captain)
{
  //int width = (log10(captain->highestTrait())) + 1; 
  //width of the traits; how much space padding to add.
                 //for example, 3 does: |  1|, | 42|, and |123| 
  system("clear");
cout << endl<<"Stellarim is the story of your quest to find freedom from the oppression of your past. You have stolen a starship and are fleeing through the galaxy. Your enemies are hunting you, but you might be able to get help from some of alien species in the universe. However, these species might become additional enemies just as easily, depending on how you deal with them."<<endl; 
cout<<"Your goal is to reach Stellarim, a section of the galaxy so far away from civilization that you will easily be able to avoid all those who seek to destroy you. In this galaxy, you must grow as strong as possible without making too many others afraid of you. You must move quickly through the zones while gathering resources and power. You must reach Stellarim alive."<< endl<<endl<<endl;
}

void Message::resetScreen(Player * captain, int whichScreen)
{
	int x, y, width, height;
	int h_original = 1050, w_original = 1200; //the size of the original file. We scale it down to SCREEN_WIDTH/HEIGHT
	int scaled[4]; //scaled x, y, width, height.
	SDL_Color textColor = { 0, 0, 0}; //black
	string toDisplay;

	if (whichScreen == 1) {
		showScreen(&gTrainingScreen);
		//top box
		convertToScreen(scaled, 45, 25, 1105, 560, h_original, w_original); 
		x = scaled[0]; y = scaled[1]; width = scaled[2];
		gMessage.displayText(topBox, textColor, x, y, width);
	} else if (whichScreen == 2) {
		showScreen(&gEncounterScreen);
		//top box
		convertToScreen(scaled, 600, 30, 550, 555, h_original, w_original); 
		x = scaled[0]; y = scaled[1]; width = scaled[2];
		gMessage.displayText(topBox, textColor, x, y, width);
	}
	
	//Unlock Zone box
	if (Encounter::getZone() == Encounter::MAX_ZONES)
	{
		finalUnlockMessage();
	}
	else
	{
		unlockMessage();
	}
	convertToScreen(scaled, 860, 630, 305, 75, h_original, w_original); 
	x = scaled[0]; y = scaled[1]; width = scaled[2];
	gMessage.displayText(unlockBox, textColor, x, y, width);

	//current Zone box
	convertToScreen(scaled, 420, 655, 80, 40, 1050, 1200); 
	x = scaled[0]; y = scaled[1]; width = scaled[2]; height = scaled[3];
	toDisplay = int2str(Encounter::getZone() + 1);
	gMessage.displayText(toDisplay, textColor, x + (width/2) , y + height/4, width);

	displayTrait(1, captain,  50, 865, 220, h_original, w_original, textColor); //Lasers
	displayTrait(2, captain,  50, 990, 220, h_original, w_original, textColor); //Shields
	displayTrait(3, captain, 630, 865, 220, h_original, w_original, textColor); //Trickery
	displayTrait(4, captain, 630, 990, 220, h_original, w_original, textColor); //Diplomacy
	displayTrait(5, captain, 325, 865, 220, h_original, w_original, textColor); //Speed
	displayTrait(6, captain, 325, 990, 220, h_original, w_original, textColor); //Navigation
	displayTrait(7, captain, 910, 865, 220, h_original, w_original, textColor); //Bravery
	displayTrait(8, captain, 910, 990, 220, h_original, w_original, textColor); //Caution
	
	SDL_RenderPresent( gRenderer ); 
}

// In Player.cpp
void Message::trainAttr(char attr)
{
  switch (toupper(attr)) {
    case 'S':
      topBox = "You decide to take a nap on your ratty cot to calm your nerves and improve your concentration.";
      break;
    case 'E':
      topBox = "You double check that your engines are in working condition.\nLooks like they'll last a little while longer.";
      break;
    case 'I':
      topBox = "You flip through the pages of some the old lore books stached in a nook of the ship.\n(you're too old fashioned to use the ship's databases).\nSome of this information could be helpful for the encounters ahead!";
      break;
    case 'P':
      topBox = "You fiddle with the power and shield systems aboard the ship.\nThese adjustments will definitely help in the long run.";
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
  topBox = "A " + alienName;
  switch (encType){
      case 0: //Attack
        topBox += " attacks you!";
        break;
      case 1: //Threaten
        topBox += " threatens you!";
        break;
      case 2: //Rob
        topBox += " is trying to rob you!";
        break;
      case 3: //Story
        topBox += " wants to tell you a story!";
        break;
      case 4: //Trade
        topBox += " wants to trade with you!";
        break;
      case 5: //Race
        topBox += " wants to race you!";
        break;
    }
}

//returns an integer. 1-8 is which trait was picked.
//9 is debugging display.
//10 is quit
int Message::getTraitChoice()
{
	SDL_Event e;
	bool chosen = false;
	char toReturn;
	while (!chosen)
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				chosen = true;
				toReturn = 10;
			}
			const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
			if( currentKeyStates[ SDL_SCANCODE_1 ] )
			{
				chosen = true;
				toReturn = 1;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_2 ] )
			{
				chosen = true;
				toReturn = 2;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_3 ] )
			{
				chosen = true;
				toReturn = 3;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_4 ] )
			{
				chosen = true;
				toReturn = 4;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_5 ] )
			{
				chosen = true;
				toReturn = 5;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_6 ] )
			{
				chosen = true;
				toReturn = 6;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_7 ] )
			{
				chosen = true;
				toReturn = 7;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_8 ] )
			{
				chosen = true;
				toReturn = 8;
			}
			else if ( currentKeyStates[ SDL_SCANCODE_9 ] ) //debugging
			{
				chosen = true;
				toReturn = 9;
			}
		}
	}
	return toReturn;
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
	topBox = "";
	if (!decideGood(trait, encType)) {
		topBox += "You shouldn't use " + trait2str(trait) + " during a " + encounter2str(encType) + ".\n";
	}
	if (win) {
		topBox += "You won the encounter!\n";
	} else {
		topBox += "You lost the encounter!\n";
	}    
}

void Message::getMad(string alienName)
{
  topBox += "The " + alienName + "s seem upset!";
}

void Message::getHappy(string alienName)
{
  topBox += "The " + alienName + "s are pleased with your actions!";
}

void Message::notEnoughTime()
{
	topBox = "You don't have enough time left to spin up your warp drive.";
}

void Message::setTopBox(string toDisplay)
{
	topBox = toDisplay;
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
    unlockBox = "Unlock next zone: ";
    if (tradesLeft > 0 || storiesLeft > 0) {
      unlockBox += " Stories: " + int2str(storiesLeft);
      unlockBox += " Trades: " + int2str(tradesLeft);
    } else {
      int prev[3];
      Encounter::getLastEncounter(prev);
      if (!(prev[0] == 5 && prev[1] && prev[2] == 6)) { //if NOT (race and win and navigation
				unlockBox =  "Win a Race with Navigation to test your new equipment!";
      } else {
	if (Encounter::unlockNext()) {
	  unlockBox = "Congratulations! Next Zone unlocked!";
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
  unlockBox = "Encounters left:\t";
  for (int i = 1; i <= 5; i++) {
    if (!Encounter::getWonInZone(i)) {
      unlockBox += encounter2str(i) + "\t";
      wonGame = false;
    }
  }
  if (wonGame) {
    myVictory = true;
  }
}

//return true if the game is won, false otherwise.
bool Message::checkVictory() 
{
  return myVictory;
}

void Message::convertToScreen(int toReturn[4], int x, int y, int width, int height, int h_original, int w_original)
{
	toReturn[0] = x * ( 1. * SCREEN_WIDTH/w_original);
	toReturn[1] = y * (1. * SCREEN_HEIGHT/h_original);
	toReturn[2] = width * (1.* SCREEN_WIDTH/w_original);
	toReturn[3] = height * (1. * SCREEN_HEIGHT/h_original);
}

string Message::int2str(int toConvert)
{
	stringstream intToStream;
	intToStream << toConvert; //convert integer to string stream
	return intToStream.str();
}

void Message::displayTrait(int trait, Player* captain, int x, int y, int width, int h_original, int w_original, SDL_Color textColor)
{
	int scaled[3];
	string toDisplay;
	convertToScreen(scaled, x, y, width, 0, h_original, w_original); //we won't be using height, set it as zero 
	x = scaled[0]; y = scaled[1]; width = scaled[2];
	toDisplay = int2str(captain->getTrait(trait) + captain-> getAttribute((trait-1)/2));
	gMessage.displayText(toDisplay, textColor, x + (width/2), y, width);
}
