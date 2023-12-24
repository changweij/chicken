#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#include "Vector2D.h"
#include "LTexture.h"
#include "Enemy.h"
#include "Chicken.h"
#include "fundamental.h"
#include "DoublyLinkedList.h"
using namespace std;

extern const int EnemyCategories;
extern Chicken_Property GoldC;
extern Chicken_Property EletricityC;
extern Chicken_Property BurningC;
extern Enemy_Property Cal;

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
Vector2D cur(border_x / 2, border_y / 2);

TTF_Font* font32 = TTF_OpenFont("font/consola.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("font/consola.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("font/consola.ttf", 24);


LTexture G_Chicken[2], E_Chicken[2], B_Chicken[2];
LTexture Enemy[EnemyCategories];
LTexture ScoreBoard;

GoldChicken player = GoldChicken(1, cur);
//========================================initializing part ended==================================================
void setTexture(){
	G_Chicken[0].loadFromFile("img/GoldC.png", renderer);
	G_Chicken[1].loadFromFile("img/GoldC2.png", renderer);
	E_Chicken[0].loadFromFile("img/ElectricityC.png", renderer);
	E_Chicken[1].loadFromFile("img/ElectricityC2.png", renderer);
	B_Chicken[0].loadFromFile("img/BurningC.png", renderer);
	B_Chicken[1].loadFromFile("img/BurningC2.png", renderer);
	Enemy[0].loadFromFile("img/Calculus.png", renderer);
	Enemy[1].loadFromFile("img/KFire.png", renderer);
    ScoreBoard.loadFromFile("img/ScoreBoard.png", renderer);
}
//=======================================Texture Setting part ended====================================================
Node *head = new Node, *tail = new Node;

void move(){
	//move Enemy 
	Node *now = head->next;
	while(now != tail){
		now->val.move();
		now = now->next;
	}
	//move chicken
	player.Moving_Chicken();


}

//===========================================moving part ended====================================================
const int generateSpeed = 2;

void generateEnemy(){
	srand(time(NULL));
	int kind;
	for(int i = 0; i < generateSpeed; i++){
		bool flag = flag;
		float px, py;
//		while(!flag){
		px = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/border_x));
		py = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/border_y));
			
//			if(fabs(px - curX) >= window_x / 2 && fabs(py - curY) >= window_y) flag = true;
//		}
//		cout << px << ' ' << py << '\n';
		// generate different kinds of enemy, using enum, calling constructers
//		kind = rand() % EnemyCategories;
		Vector2D pos(px, py), v = get_mag_of(Cal.v);
		Node *nd = new Node(Calculus(pos, Cal.dmg, SDL_GetTicks(), Cal.lasting_time, v, Cal.r, 0));
		insert(tail, nd);
	}
}


//=========================================Enemy generating part ended=============================================

void render_all(){
	Vector2D render_pos;

    Node *now = head->next;
	while(now != tail){
		class Enemy e = now->val;
        render_pos = e.get_pos();
		Enemy[0].render(render_pos.x - Cal.size_radius / 2, render_pos.y - Cal.size_radius / 2, Cal.size_radius, Cal.size_radius, renderer);

		now = now->next;
	}
    render_pos = player.get_pos();
    G_Chicken[0].render(render_pos.x - GoldC.size_radius / 2, render_pos.y - GoldC.size_radius / 2, GoldC.size_radius, GoldC.size_radius, renderer);

    ScoreBoard.render(0, 0, 200, 80, renderer);
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
    //Modified-------------------------------------------------
    int Gold = 0;
    //Modified-------------------------------------------------
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
						player.modify_speed(0);
						cout << "UP\n";
					}
					else if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT){
						player.modify_speed(1);
						cout << "LEFT\n";
					}
					else if(event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN){
						player.modify_speed(2);
						cout << "DOWN\n";
					}
					else if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT){
						player.modify_speed(3);
						cout << "RIGHT\n";
					}
					else continue;
	            default:
	                continue;
	        }
	    }
	    if(!gameRunning) break;
		// move all items
		move();
        // Modified : produce egg--------------
        if(counter % (player.Produce_speed * 60) == 0){
            Gold += player.Production;
        }
        //-------------------------------------

		// Do rendering loop
		render_all();
		//generate Enemies
		counter++;
        
		if(counter % 60 == 0){
			
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
			setTexture();
			game();
		}
		SDL_DestroyRenderer(renderer);
	}
	SDL_DestroyWindow(window);
    return 0;
}