#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class LTexture{
	public:
		LTexture();
		~LTexture();
		//Deallocates texture
		void free();
		//Loads image at the specified path
		bool loadFromFile(string path , SDL_Renderer*);
		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		//Set blending
		void setBlendMode( SDL_BlendMode blending );
		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		//Renders texture at the given point
		void render(float x, float y, SDL_Renderer*);
		void render(float x, float y, float w, float h, SDL_Renderer*);
		//Load Texture from text
		bool loadFromRenderedText(string text, SDL_Color, SDL_Renderer*, TTF_Font*);
		//Render center-aligned text
		void renderCenter(float x, float y, SDL_Renderer*);
		void renderRight(float x, float y, SDL_Renderer*);
		//Gets image dimensions
		float getWidth();
		float getHeight();
		//set mHeight and mWidth
		void setdim(float w, float h);
		
	protected:
		//The actual hardware texture
		SDL_Texture* mTexture;
		//Image dimensions
		float mWidth;
		float mHeight;
};
