#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Player.h"
#include "LTexture.h"

using namespace std;

class Message
{
	public:
		//GLOBALS:
		const static int SCREEN_WIDTH = 960;
		const static int SCREEN_HEIGHT = 840;

		//SDL Window, Renderer, (and font)
		static SDL_Window* gWindow;
		static SDL_Renderer* gRenderer;
		static TTF_Font *gFont;
		//static TTF_Font* gLargeFont;
		//static TTF_Font* gRegFont;
		//static TTF_Font* gSmallFont;

		//Starts up SDL and creates window
		static bool init_SDL();

		//Loads media
		bool loadMedia();

		//Frees media and shuts down SDL
		void close();
		bool showTitleScreen();
		void showScreen(LTexture*);
		char getAttrChoice();
	  void intro(Player *);
	  void resetScreen(Player *, int whichScreen, string whichAlien = "");
	  void trainAttr(char);
	  void newEncounter(int, string);
	  int getTraitChoice();
	  bool decideGood(int, int);
	  void encResults(int, int, int, string);
	  void getMad(string);
	  void getHappy(string);
          void notEnoughTime();
          void setTopBox(string);
          string trait2str(int);
          string encounter2str(int);
	  void unlockMessage();
	  void finalUnlockMessage();
	  static bool checkVictory();
          void renderAlien(string name);
	  void renderButton(int whichButton);
		void convertToScreen(int* array, int x, int y, int wiRenderdth, int height, int h_original, int w_original);
		string int2str(int);
		void displayTrait(int trait, Player* captain, int x, int y, int width, int h_original, int w_original, SDL_Color textColor);
 private:
		
	  static bool myVictory;
		//TEXTURE:
		static LTexture mTrainingScreen;
		static LTexture mEncounterScreen;
		static LTexture mTitleScreen;
		static LTexture mAlien[5];
		static LTexture mMessage;

		static LTexture mWarpNextButton;
		static LTexture mWarpPrevButton;
		static LTexture mWarpTextButton;
		static string topBox;
		static string bottomBox;
		static string unlockBox;
};




#endif
