#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "LTexture.h"
#include "Message.h"


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWindow = Message::gWindow;
	mRenderer = Message::gRenderer;
	mFont = Message::gFont;

	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	mWindow = Message::gWindow;
	mRenderer = Message::gRenderer;
	mFont = Message::gFont;
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( mRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, int width )
{
	mWindow = Message::gWindow;
	mRenderer = Message::gRenderer;
	mFont = Message::gFont;
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( mFont, textureText.c_str(), textColor, width );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( mRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}

//load, display to square
//int x, y specifies top left corner
//obsolete backup
/*void LTexture::displayText2(std::string toDisplay, SDL_Color textColor, int x, int y, int width, int h_original, int w_original)
{
	Message msg;
	mWindow = Message::gWindow;
	mRenderer = Message::gRenderer;
	mFont = Message::gFont;
	int scaled[3]; //the scaled x, y, and width
	msg.convertToScreen(scaled, x, y, width, h_original, w_original);
	x = scaled[0];
	y = scaled[1];
	width = scaled[2];
	printf("x: %i", x);

	if (!loadFromRenderedText( toDisplay.c_str(), textColor, width )) //probably takes time.
	{
		printf( "Failed to render text texture!\n" );
	}
	SDL_Rect viewport;
	viewport.x = x;
	viewport.y = y;
	viewport.w = mWidth;
	viewport.h = mHeight;
	SDL_RenderSetViewport( mRenderer, &viewport );
	
	SDL_RenderCopy( mRenderer, mTexture, NULL, NULL);
}*/

//load, display to square
//int x, y specifies top left corner
void LTexture::displayText(std::string toDisplay, SDL_Color textColor, int x, int y, int width)
{
	mWindow = Message::gWindow;
	mRenderer = Message::gRenderer;

	if (!loadFromRenderedText( toDisplay, textColor, width )) //probably takes time.
	{
		printf( "Failed to render text texture!\n" );
	}
	SDL_Rect viewport;
	viewport.x = x;
	viewport.y = y;
	viewport.w = mWidth;
	viewport.h = mHeight;
	SDL_RenderSetViewport( mRenderer, &viewport );
	
	SDL_RenderCopy( mRenderer, mTexture, NULL, NULL);
}

#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	mWindow = Message::gWindow;
	mRenderer = Message::gRenderer;
	mFont = Message::gFont;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( mRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

/*
void LTexture::initRenderer(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

void LTexture::initFont(TTF_Font* font)
{
	mFont = font;
} */

void LTexture::renderScaled(SDL_Rect* stretch)
{
	mWindow = Message::gWindow;
	mRenderer = Message::gRenderer;
	mFont = Message::gFont;
	SDL_RenderSetViewport( mRenderer, stretch );
	
	//Render texture to screen
	SDL_RenderCopy( mRenderer, mTexture, NULL, NULL);
}
