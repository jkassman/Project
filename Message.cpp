/* Message.cpp

   The class is a display class, the only place SDL is dealt with.
   The renderer, window, and font are public static.

*/

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <math.h>
#include <sstream>
#include <fstream>

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
LTexture Message::mTrainingScreen;
LTexture Message::mEncounterScreen;
LTexture Message::mTitleScreen;
LTexture Message::mInstructionScreen;
LTexture Message::mAlien[5];

LTexture Message::mMessage;

LTexture Message::mWarpNextButton;
LTexture Message::mWarpPrevButton;
LTexture Message::mWarpTextButton;

string Message::topBox = " ";
string Message::bottomBox = " ";
string Message::unlockBox = " ";

bool Message::myVictory = false;

//mostly from SDL Tutorials
//Sets up SDL, creating a renderer and window
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

//Template from SDL Tutorials
//Loads many differnt media files to static private LTextures
bool Message::loadMedia()
{
  //Loading success flag
  bool success = true;
  //Load main screen
  if( !mTrainingScreen.loadFromFile( "BGs/Training.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }

  if( !mTitleScreen.loadFromFile( "BGs/SplashScrn.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }

  if ( !mEncounterScreen.loadFromFile( "BGs/Encounter.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }

  if( !mInstructionScreen.loadFromFile( "BGs/instrMain.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }

  if (!mAlien[0].loadFromFile( "alien_imgs/skyrunnerscrn.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  if (!mAlien[1].loadFromFile( "alien_imgs/scribescrn.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  if (!mAlien[2].loadFromFile( "alien_imgs/smugglerscrn.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  if (!mAlien[3].loadFromFile( "alien_imgs/dragonscrn.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  if (!mAlien[4].loadFromFile( "alien_imgs/golemscrn.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  if (!mWarpNextButton.loadFromFile( "BGs/warpnext.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  if (!mWarpPrevButton.loadFromFile( "BGs/warpprev.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  if (!mWarpTextButton.loadFromFile( "BGs/unlockbox.png" ) )
    {
      printf( "Failed to load press texture!\n" );
      success = false;
    }
  //Global Font initialization
  gFont = TTF_OpenFont( "OCRAEXT.TTF", 20 );
  if( gFont == NULL )
    {
      printf( "Failed to load small OCR Extended font! SDL_ttf Error: %s\n", TTF_GetError() );
      success = false;
    }
  return success;
}

//
void Message::close()
{
  //Free loaded images
  mTrainingScreen.free();
  mTitleScreen.free();
  mEncounterScreen.free();
  mInstructionScreen.free();
  
  for (int i = 0; i < 5; i++)
    {
      mAlien[i].free();		
    }
  mMessage.free();

  //Destroy window	
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

//returns 0: play game. 1: Instructions. 2:exi
int Message::showTitleScreen()
{
  //Current rendered texture
  LTexture* currentTexture = NULL;

  currentTexture = &mTitleScreen;

  //Event handler
  SDL_Event e;

  //BEGIN SDL STUFF
  //Handle events on queue
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

  while (1) 
    while( SDL_PollEvent( &e ) != 0 )
      {
	//User requests quit
	if( e.type == SDL_QUIT )
	  return 2;
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	if( currentKeyStates[ SDL_SCANCODE_1 ] )
	  return 0;
	else if ( currentKeyStates[ SDL_SCANCODE_2 ] )
	  return 1;
	else if ( currentKeyStates[ SDL_SCANCODE_3 ] )
	  return 2;
      }
}

//Displays the introduction and instructions for the game
//returns true if hit x, false if you want to go back to the main menu
int Message::showInstructions()
{
  SDL_Color textColor = { 0, 0, 0}; //black
  //Current rendered texture
  LTexture* currentTexture = NULL;

  int x, y, width;
  int h_original = 1050, w_original = 1200; //the size of the original file. We scale it down to SCREEN_WIDTH/HEIGHT
  int scaled[4]; //scaled x, y, width, height.

  int page=1, changepage=0;
  bool pagechanged=false;
  string line,instructions[5];
  for(int i=1;i<5;i++)
    {
      instructions[i]=" ";
      string filename = "txtfiles/instrP" + int2str(i) + ".txt";
      ifstream instrfile (filename.c_str());
      if (instrfile.is_open())
	{
	  while (getline (instrfile,line))
	    {
	      instructions[i] = instructions[i] + line + "\n";
	    }
	  instrfile.close();
	}else cout<<"Unable to find instruction file "<<i<<"!"<<endl;
    }
  currentTexture = &mInstructionScreen;

  //Event handler
  SDL_Event e;

  while(1)
    {
      //BEGIN SDL STUFF
      //Handle events on queue
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
      SDL_RenderClear( gRenderer );

      //Top left corner viewport
      SDL_Rect stretchRect;
      stretchRect.x = 0;
      stretchRect.y = 0;
      stretchRect.w = SCREEN_WIDTH;
      stretchRect.h = SCREEN_HEIGHT;
      currentTexture->renderScaled( &stretchRect );

      convertToScreen(scaled, 50, 40, 1090, 875, h_original, w_original); 
      x = scaled[0]; y = scaled[1]; width = scaled[2];
      mMessage.displayText(instructions[page], textColor, x, y, width);

      //Update screen
      SDL_RenderPresent( gRenderer );
      changepage=0;
      pagechanged=false;
      while (!pagechanged)
	{
	  while( SDL_PollEvent( &e ) != 0 )
	    {
	      //User requests quit
	      if( e.type == SDL_QUIT ) return true;
	      const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	      if( currentKeyStates[ SDL_SCANCODE_0 ] ) return false;
	      if( currentKeyStates[ SDL_SCANCODE_MINUS ] && page>1) 
		{
		  changepage = -1;
		  pagechanged=true;
		}
	      if( currentKeyStates[ SDL_SCANCODE_EQUALS ] && page<4)  
		{
		  changepage = 1;
		  pagechanged=true;
		}
	    }
	}
      page+=changepage;
    }
}

//returns which attribute the user chose
//could be Q to Quit. 0 and 1 are used to attempt to warp through the zones.
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
	  if( currentKeyStates[ SDL_SCANCODE_P ] )
	    {
	      chosen = true;
	      toReturn = 'P';
	    }
	  else if ( currentKeyStates[ SDL_SCANCODE_I ] )
	    {
	      chosen = true;
	      toReturn = 'I';
	    }
	  else if ( currentKeyStates[ SDL_SCANCODE_E ] )
	    {
	      chosen = true;
	      toReturn = 'E';
	    }
	  else if ( currentKeyStates[ SDL_SCANCODE_S ] )
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

//Renders the given screen (does not renderPresent)
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

//Message displayed at the beginning of the game
void Message::intro(Player * captain)
{
  topBox = "Stellarim is the story of your quest to find freedom from the oppression of your past. You have stolen a starship and are fleeing through the galaxy. Your enemies are hunting you, but you might be able to get help from some of the alien species in the universe. However, these species might become additional enemies just as easily, depending on how you deal with them.\n\nYour goal is to reach Stellarim, a section of the galaxy so far away from civilization that you will easily be able to avoid all those who seek to destroy you. In this galaxy, you must grow as strong as possible without making too many others afraid of you. You must move quickly through the zones while gathering resources and power. You must reach Stellarim alive.";
}

//whichAlien doesn't matter if whichScreen is 1, because the aliens are not displayed during that screen.
//This is the only place where renderPresent (like gfx_flush) should happen.
//resets the screen and redraws all the text.
void Message::resetScreen(Player * captain, int whichScreen, string alienName)
{
  int x, y, width, height;
  int h_original = 1050, w_original = 1200; //the size of the original file. We scale it down to SCREEN_WIDTH/HEIGHT
  int scaled[4]; //scaled x, y, width, height.
  SDL_Color textColor = { 0, 0, 0}; //black
  string toDisplay;

  if (whichScreen == 1) //Training mode
    { 
      showScreen(&mTrainingScreen);
      topBox += "\n\nChoose which Attibute you want to train: \n";
      //top box
      convertToScreen(scaled, 45, 25, 1105, 560, h_original, w_original); 
      x = scaled[0]; y = scaled[1]; width = scaled[2];
      //gFont = gLargeFont;
      mMessage.displayText(topBox, textColor, x, y, width);
      //Warp buttons:
      //Default texture reloaded every resetScreen has no warp buttons.
      if (Encounter::getZone() != Encounter::MAX_ZONES) //if we are in the max zone, display no next button
	{
	  if (Encounter::checkNextUnlock())
	    {
	      //show next button
	      renderButton(2);
	    }
	  else
	    {
	      //show empty text box
	      renderButton(3);
	    }
	}
      else //in max zone
	{
	  //show empty text box
	  renderButton(3);
	}
      if (Encounter::getZone() == 0)
	{
	  //don't show previous button
	}
      else
	{
	  //show previous button
	  renderButton(1);
	}

    } 
  else if (whichScreen == 2) //Encounter Mode
    { 
      showScreen(&mEncounterScreen);
      renderAlien(alienName);
      //topBox += "\nWhich trait do you want to use in this encounter?\n";
      //gFont = gRegFont;
      //Unlock Zone box
      if (Encounter::getZone() == Encounter::MAX_ZONES)
	{
	  finalUnlockMessage();
	}
      else
	{
	  unlockMessage();
	}

      //top box
      convertToScreen(scaled, 600, 30, 550, 555, h_original, w_original); 
      x = scaled[0]; y = scaled[1]; width = scaled[2];
      mMessage.displayText(topBox, textColor, x, y, width);
    }
	
  //unlock next Zone box
  convertToScreen(scaled, 860, 630, 305, 75, h_original, w_original); 
  x = scaled[0]; y = scaled[1]; width = scaled[2];
  mMessage.displayText(unlockBox, textColor, x, y, width);

  //current Zone box
  convertToScreen(scaled, 420, 655, 80, 40, 1050, 1200); 
  x = scaled[0]; y = scaled[1]; width = scaled[2]; height = scaled[3];
  toDisplay = int2str(Encounter::getZone() + 1);
  mMessage.displayText(toDisplay, textColor, x + (width/2) , y + height/4, width);

  displayTrait(1, captain,  50, 865, 220, h_original, w_original, textColor); //Lasers
  displayTrait(2, captain,  50, 990, 220, h_original, w_original, textColor); //Shields
  displayTrait(3, captain, 325, 865, 220, h_original, w_original, textColor); //Trickery
  displayTrait(4, captain, 325, 990, 220, h_original, w_original, textColor); //Diplomacy
  displayTrait(5, captain, 630, 865, 220, h_original, w_original, textColor); //Speed
  displayTrait(6, captain, 630, 990, 220, h_original, w_original, textColor); //Navigation
  displayTrait(7, captain, 910, 865, 220, h_original, w_original, textColor); //Bravery
  displayTrait(8, captain, 910, 990, 220, h_original, w_original, textColor); //Caution

  //force screen to update
  SDL_RenderPresent( gRenderer ); 
}

// Called from Player.cpp.
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
    topBox += " attacks you!\n";
    break;
  case 1: //Threaten
    topBox += " threatens you!\n";
    break;
  case 2: //Rob
    topBox += " is trying to rob you!\n";
    break;
  case 3: //Story
    topBox += " wants to tell you a story!\n";
    break;
  case 4: //Trade
    topBox += " wants to trade with you!\n";
    break;
  case 5: //Race
    topBox += " wants to race you!\n";
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

//returns true if the input was proper for that encounter
//for example, using diplomacy in a fight encounter doesn't work, as the aliens
//are already mad at you beyomd the power of your reasoning
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

//Display the results of the encounter
void Message::encResults(int encType, int trait, int win, string alienName)
{
  if (!decideGood(trait, encType)) {
    topBox += "You shouldn't use " + trait2str(trait) + " during a " + encounter2str(encType) + ".\n";
  }
  if (win) {
    topBox += "You won the encounter!\n";
  } else {
    topBox += "You lost the encounter!\n";
  }    
}

//should be caled whenever an alien's hostility increases
void Message::getMad(string alienName)
{
  topBox += "The " + alienName + "s seem upset!";
}

//should be called whenever an alien's hostility decreases
void Message::getHappy(string alienName)
{
  topBox += "The " + alienName + "s are pleased with your actions!";
}

//Should be called whenever a player tries to warp after training an attribute
void Message::notEnoughTime()
{
  topBox = "You don't have enough time left to spin up your warp drive.";
}

//resets the topBox to display whatever toDisplay is
void Message::setTopBox(string toDisplay)
{
  topBox = toDisplay;
}

//simple function to convert a trait to a string
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

//simple function to convert an encounter to a string
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

//displays what you need to unlock the next zone
void Message::unlockMessage() {
  int requiredStories = 2;
  int requiredTrades = 2; //how many stories and trades you need to unlock the next zone
  int story = Encounter::getWonInZone(3);
  int trade = Encounter::getWonInZone(4); //how many trades and stories you have won
  int storiesLeft = requiredStories - story;
  int tradesLeft = requiredTrades -trade;
  if (storiesLeft < 0) storiesLeft = 0;
  if (tradesLeft < 0) tradesLeft = 0; //don't let negative numbers happen
  if (!Encounter::checkNextUnlock()) { //if next zone is not unlocked.
    unlockBox = "Unlock next zone: ";
    if (tradesLeft > 0 || storiesLeft > 0) {
      unlockBox += " Stories: " + int2str(storiesLeft);
      unlockBox += " Trades: " + int2str(tradesLeft);
    } else {
      int prev[3];
      Encounter::getLastEncounter(prev);
      if (!(prev[0] == 5 && prev[1] && prev[2] == 6)) { //if NOT (race and win and navigation
	unlockBox =  "Win a Race with Navigation!";// to test your new equipment!";
      } else {
	if (Encounter::unlockNext()) {
	  topBox += "\nCongratulations! Next Zone unlocked!\n";
	  unlockBox = " ";
	}
      }
    }
  }
  else 
    {
      unlockBox = " "; //clear unlock message
    }
}

//displays what you need to know to win the game
void Message::finalUnlockMessage() 
{
  bool wonGame = true;
  //you must win one of every type of encounter except fight.
  unlockBox = "Encounters left:\t";
  for (int i = 1; i <= 5; i++) {
    if (!Encounter::getWonInZone(i)) {
      unlockBox += encounter2str(i) + " ";
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

//Our original file is too big, so we scale it down. But all the coordinates of
//the boxes are in the specs of the original file, so this function scales them
//down properly. 
//Now we can set SCREEN_WIDTH and SCREEN_HEIGHT to just about any value and
//the text will still render to the proper place.
void Message::convertToScreen(int toReturn[4], int x, int y, int width, int height, int h_original, int w_original)
{
  toReturn[0] = x * ( 1. * SCREEN_WIDTH/w_original);
  toReturn[1] = y * (1. * SCREEN_HEIGHT/h_original);
  toReturn[2] = width * (1.* SCREEN_WIDTH/w_original);
  toReturn[3] = height * (1. * SCREEN_HEIGHT/h_original);
}

//a very usefull function that does as its name would suggest.
string Message::int2str(int toConvert)
{
  stringstream intToStream;
  intToStream << toConvert; //convert integer to string stream
  return intToStream.str();
}

//displays the specified trait in the correct position on the screen
void Message::displayTrait(int trait, Player* captain, int x, int y, int width, int h_original, int w_original, SDL_Color textColor)
{
  int scaled[3];
  string toDisplay;
  convertToScreen(scaled, x, y, width, 0, h_original, w_original); //we won't be using height, set it as zero 
  x = scaled[0]; y = scaled[1]; width = scaled[2];
  toDisplay = int2str(captain->getTrait(trait) + captain-> getAttribute((trait-1)/2));
  mMessage.displayText(toDisplay, textColor, x + (width/2), y, width);
}

//render (but don't renderPresent) the given alien.
void Message::renderAlien(string name)
{
  //Stretch to fit screen
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = SCREEN_WIDTH;
  stretchRect.h = SCREEN_HEIGHT;
  if (name == "Sky Runner")
    mAlien[0].renderScaled( &stretchRect );
  else if (name == "Scribe")
    mAlien[1].renderScaled( &stretchRect );		
  else if (name == "Smuggler")
    mAlien[2].renderScaled( &stretchRect );
  else if (name == "Dragon")
    mAlien[3].renderScaled( &stretchRect );
  else if (name == "Golem")
    mAlien[4].renderScaled( &stretchRect );		
  else
    cout << "ERROR: Could not read alien name properly. Load aborted." << endl;
}

//1 is previous, 2 is next, 3 is text.
void Message::renderButton(int whichButton)
{
  SDL_Rect stretchRect;
  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = SCREEN_WIDTH;
  stretchRect.h = SCREEN_HEIGHT;
  switch (whichButton)
    {
    case 1:
      mWarpPrevButton.renderScaled(&stretchRect);
      break;
    case 2:
      mWarpNextButton.renderScaled(&stretchRect);
      break;
    case 3:
      mWarpTextButton.renderScaled(&stretchRect);
      break;
    default:
      cout << "ERROR: Could not load button. Invalid select provided." << endl;
      break;
    }
}
