#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <sstream>    // header file for stringstream

#include "Vector2D.h"
#include "Collision.h"
#include "LTexture.h"
#include "Enemy.h"
#include "Chicken.h"
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

float border_x = 1200;
float border_y = 640;

float window_x = 1200;
float window_y = 640;

float default_infinity_time = 10000.0; 
const int EnemyCategories = 2;

struct Chicken_Property{
    int max_hp;
    int gold_cost;
    float r;
    Chicken_Property(int hp, int cost, float r): max_hp(hp), gold_cost(cost), r(r){}
};

Chicken_Property GoldC(20, 5, 30.0);
Chicken_Property EletricityC(10, 10, 30.0);
Chicken_Property BurningC(20, 20, 30.0);

int Gold = 0;
string Get_Gold_String(){
	stringstream stream;
	stream << Gold;
	string Gstr;
    stream >> Gstr;
    return Gstr;
}

struct Enemy_Property{
	int dmg, lasting_time;
	float v;
	float r;
	Enemy_Property(int dmg, int lasting_time, float v, float r): dmg(dmg), lasting_time(lasting_time), v(v), r(r){}
};

Enemy_Property E_prop[EnemyCategories] = {Enemy_Property(2, 50000, 1.0, 30.0), Enemy_Property(2, 50000, 0, 30.0)}; 

//=========================================these are fundamentals=============================================
bool SDL_init = init();
bool gameRunning = true;
SDL_Window* window;
SDL_Renderer* renderer;

TTF_Font* font32 = TTF_OpenFont("font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("font/font.ttf", 24);

SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };

LTexture G_Chicken[2], E_Chicken[2], B_Chicken[2];
LTexture Enemy[EnemyCategories];
LTexture ScoreBoard;
LTexture EggNumber;
LTexture Background;
GoldChicken player = GoldChicken(1, GoldC.max_hp, GoldC.gold_cost, Vector2D(border_x / 2, border_y / 2), GoldC.r);
//========================================initializing part ended==================================================
void setTexture(){
	Background.loadFromFile("img/GrassBackground.jpg", renderer);
	G_Chicken[0].loadFromFile("img/GoldC.png", renderer);
	G_Chicken[1].loadFromFile("img/GoldC2.png", renderer);
	E_Chicken[0].loadFromFile("img/ElectricityC.png", renderer);
	E_Chicken[1].loadFromFile("img/ElectricityC2.png", renderer);
	B_Chicken[0].loadFromFile("img/BurningC.png", renderer);
	B_Chicken[1].loadFromFile("img/BurningC2.png", renderer);
	Enemy[0].loadFromFile("img/Calculus.png", renderer);
	Enemy[1].loadFromFile("img/KFire.png", renderer);
	ScoreBoard.loadFromFile("img/ScoreBoard.png", renderer);
	//EggNumber.loadFromRenderedText("0", black, renderer, font32);
}
//=======================================Texture Setting part ended====================================================
Node *head = new Node, *tail = new Node;

void move(){
	//move chicken
	player.Moving_Chicken();
	//move Enemy 
	Node *now = head->next, *temp;
	while(now != tail){
		now->val.move();
		if(isCollided(player, now->val)){
			if(!player.adjust_hp(-now->val.get_dmg())){
				gameRunning = false;
				return;
			}
			temp = now->prev;
			del(now);
			now = temp;
		}
		else if(now->val.isDead(SDL_GetTicks())){
			temp = now->prev;
			del(now);
			now = temp;
		}
		now = now->next;
	}
}

//===========================================moving part ended====================================================
const int generateSpeed = 2;

void generateEnemy(){
	srand(time(NULL));
	int kind;
	for(int i = 0; i < generateSpeed; i++){
		bool flag = false;
		float px, py;
//		while(!flag){
			px = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/border_x));
			py = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/border_y));
//			if(fabs(px - curX) >= window_x / 2 && fabs(py - curY) >= window_y / 2) flag = true;
//		}
		// generate different kinds of enemy, using enum, calling constructers
		kind = rand() % EnemyCategories;
		Vector2D pos(px, py), v;
		Node *nd;
		if(E_prop[kind].v != 0) v = get_mag_of(E_prop[kind].v);
		if(kind == 0) nd = new Node(Calculus(pos, E_prop[kind].dmg, SDL_GetTicks(), E_prop[kind].lasting_time, v, E_prop[kind].r, 0));
		else if(kind == 1) nd = new Node(Fire(pos, E_prop[kind].dmg, SDL_GetTicks(), E_prop[kind].lasting_time, v, E_prop[kind].r, 1));
		insert(tail, nd);
	}
}

//=========================================Enemy generating part ended=============================================
int walk;

void render_all(){
	Background.render(0.0, 0.0, renderer);
	Vector2D render_pos;
	int kind;
	float sz;
    Node *now = head->next;
	while(now != tail){
		class Enemy e = now->val;
        render_pos = e.get_pos();
        kind = e.get_id();
        sz = E_prop[kind].r;
		Enemy[kind].render(render_pos.x - sz, render_pos.y - sz, sz * 2, sz * 2, renderer);
		now = now->next;
	}
    render_pos = player.get_pos();
    walk++;
    if(walk == 80) walk = 0;
    G_Chicken[walk / 40].render(render_pos.x -  GoldC.r, render_pos.y - GoldC.r, GoldC.r * 2, GoldC.r * 2, renderer);
    ScoreBoard.render(950, 0, 250, 80, renderer);
    
    
    EggNumber.loadFromRenderedText(Get_Gold_String(), black, renderer, font32);
    EggNumber.render(1070, 18, renderer);
}

//==============================================rendering part ended===============================================

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
						player.modify_speed(0);
					}
					else if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT){
						player.modify_speed(1);
					}
					else if(event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN){
						player.modify_speed(2);
					}
					else if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT){
						player.modify_speed(3);
					}
					else continue;
	            default:
	                continue;
	        }
	    }
	    if(!gameRunning) break;
		// move all items
		move();
		if(!gameRunning) break;
		// Do rendering loop
		render_all();
		//generate Enemies
		counter++;
		if(counter % 60 == 0){
			generateEnemy(); 
		}
		if(counter % (player.get_Produce_speed() * 60) == 0){
            Gold += player.get_Production();
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
    window = SDL_CreateWindow("Your Program's Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_x, window_y, SDL_WINDOW_SHOWN );
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
