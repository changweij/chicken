#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "LTexture.h"
using namespace std;

LTexture::LTexture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

void LTexture::free(){
    if( mTexture != NULL){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
LTexture::~LTexture(){
	free();
}

bool LTexture::loadFromFile(string path, SDL_Renderer* renderer){
	//Get rid of preexisting texture
	free();
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at the specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL){
		cout << "Unable to load image: " << path.c_str() << " SDL_image Error: " << IMG_GetError() << '\n';
	}
	else
	{
		/*
		//Color key image: Optional
		//Further explanation in Unit ?
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		*/

		//Create texture from surface pixels
   		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if(newTexture == NULL){
			cout << "Unable to create texture from" << path.c_str() << " SDL Error: " << SDL_GetError() << '\n';
		}
		else{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Return success
	mTexture = newTexture;
	this->setBlendMode( SDL_BLENDMODE_BLEND );
	return mTexture != NULL;
}

void LTexture::render(float x, float y, SDL_Renderer* renderer){
	//Set rendering space and render to screen
	SDL_FRect target = {x, y, mWidth, mHeight};
	//Render to screen
	SDL_RenderCopyF(renderer, mTexture, NULL, &target);
}
void LTexture::render(float x, float y, float w, float h, SDL_Renderer* renderer){
	//Set rendering space and render to screen
	SDL_FRect target = {x, y, w, h};
	//Render to screen
	SDL_RenderCopyF( renderer, mTexture, NULL, &target);
}

void LTexture::setAlpha(Uint8 alpha){
	//Modulate texture alpha
	//0~255(absolute transparent)
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::setBlendMode(SDL_BlendMode blending){
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}