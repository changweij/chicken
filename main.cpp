#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "LTexture.h"
#include "Enemy.h"
#include "Chicken.h"
#include "fundamental.h"
#include "DoublyLinkedList.h"
using namespace std;

bool init(){
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		cout << "SDL_Error: " << SDL_GetError() << '\n';
	}
	//Initialize SDL_ttf
	if(TTF_Init() == -1){
		cout << "SDL_ttf Error: " << TTF_GetError() << '\n';
	}
	//Initialize SDL_image
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF;
	if(!(IMG_Init(imgFlags) & imgFlags)){
		cout << "SDL_image Error: " <<  IMG_GetError() << '\n';
	}
	
	//Initialize SDL_mixer
	int mixFlags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID | MIX_INIT_OPUS;
	if(!(Mix_Init(mixFlags) & mixFlags)){
		cout << "SDL_mixer Error: " <<  Mix_GetError() << '\n';
	}
	//open audio devices
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
	    cout << "SDL_mixer Error: " << Mix_GetError() << '\n';
	}
}

bool SDL_init = init();
SDL_Window* window;
SDL_Renderer* renderer;

//========================================initializing part ended==================================================
Node *head = new Node, *tail = new Node;

void move(){
	//move Enemy 
	Node *now = head->next;
	while(now != tail){
		Enemy &e = now->val;
		e.move();
		now = now->next;
	}
	
}

//===========================================moving part ended====================================================

void generateEnemy(){
	
}

//=========================================Enemy generating part ended=============================================

void render_all(){
	
}

//==============================================rendering part ended===============================================

bool gameRunning = true;
Uint32 ticks = SDL_GetTicks();
/*
int state = 0; //0 = title screen, 1 = game, 2 = end screen
*/
void game(){
	head->next = tail;
	tail->prev = head;
	int counter = 0;
	while (gameRunning) {
		Uint64 start = SDL_GetPerformanceCounter();
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		// Do event loop
		SDL_Event event;
		while(SDL_PollEvent(&event)){
	        switch(event.type){
	            case SDL_QUIT:
	                gameRunning = false;
	                break;
	            case SDL_KEYDOWN:	
	                if(event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP){
						//set chicken v
						cout << "detected\n";
					}
					else if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT){
						//set chicken v
						cout << "detected\n";
					}
					else if(event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN){
						//set chicken v
						cout << "detected\n";
					}
					else if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT){
						//set chicken v
						cout << "detected\n";
					}
					else continue;
	            default:
	                continue;
	        }
	    }
		// move all items
		move();
		// Do rendering loop
		render_all();
		//generate Enemies
		counter++;
		if(counter == 60){
			counter = 0;
			generateEnemy(); 
		}
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		// Cap to 60 FPS
		
		SDL_Delay(floor(16.666f - elapsedMS));
		SDL_RenderPresent(renderer);
	}
}

//=========================================game running part ended=====================================================
int main(int argc, char *argv[]){
    window = SDL_CreateWindow("Your Program's Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
	if(window == NULL){
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
	}
	else{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(renderer == NULL){
			cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
		}else{
			game();
		}
		SDL_DestroyRenderer(renderer);
	}
	SDL_DestroyWindow(window);
    return 0;
}
