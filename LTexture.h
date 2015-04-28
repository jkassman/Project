#ifndef LTEXTURE_H
#define LTEXTURE_H
class LTexture
{
	public:

		//void initRenderer(SDL_Renderer*);
		//void initFont(TTF_Font*);		

		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, int width );

		//h_original and w_original are the size of the screen x, y, and width were originally from.
		void displayText(std::string toDisplay, SDL_Color textColor, int x, int y, int width);
		//void displayText2(std::string toDisplay, SDL_Color textColor, int x, int y, int width, int h_original, int w_original);
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		void renderScaled(SDL_Rect* stretch);

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		
		//The window we'll be rendering to
		SDL_Window* mWindow;

		//The window renderer
		SDL_Renderer* mRenderer;

		//local font
		TTF_Font* mFont;

		int mWidth;
		int mHeight;
};

#endif
