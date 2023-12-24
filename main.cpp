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
const int EnemyCategories = 4;

struct Chicken_Property{
    int max_hp;
    int gold_cost;
    float r;
    Chicken_Property(int hp, int cost, float r): max_hp(hp), gold_cost(cost), r(r){}
};

Chicken_Property GoldC(20, 5, 30.0);
Chicken_Property ElectricityC(10, 10, 30.0);
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

Enemy_Property E_prop[EnemyCategories] = {Enemy_Property(2, 20000, 1.0, 30.0), Enemy_Property(2, 20000, 0, 30.0)
, Enemy_Property(1, 10000, 4.0, 20.0), Enemy_Property(5, 20000, 0, 50.0)}; 

//=========================================these are fundamentals=============================================


int dir_x[9] =       {0,  0, -1, -1,  1,  1,  0,  1, -1};
int dir_y[9] =       {0, -1,  0, -1,  0, -1,  1,  1,  1};
int id[9] = {};
int chicken_cost[3];
bool isalive[9] =    {1,  0,  0,  0,  0,  0,  0,  0,  0};
GoldChicken GoldChickens[9];
ElectricityChicken ElectricityChickens[9];
BurningChicken BurningChickens[9];

bool Summon_Chicken(int _kind){
    int index = 1;
    if(Gold < chicken_cost[_kind]) return false;
    for(int i = 1; i <= 8; i++){
        if(isalive[i] == 0){
            index = i;
            isalive[i] = 1;
            break;
        } 
        if(i == 8) return false; // isfull 
    }
    
    Vector2D summon_pos(dir_x[index] * 60, dir_y[index] * 60);
    summon_pos += player.get_pos();

    switch(_kind){
        case 0: //GoldChicken
            GoldChickens[index] = GoldChicken(1, GoldC.max_hp, GoldC.gold_cost, summon_pos, GoldC.r);
            id[index] = 0;
            break;
        case 1: //ElectricityChicken
            ElectricityChickens[index] = ElectricityChicken(1, ElectricityC.max_hp, ElectricityC.gold_cost, summon_pos, ElectricityC.r);
            id[index] = 1;
            break;
        case 2: //BurningChicken
            BurningChickens[index] = BurningChicken(1, BurningC.max_hp, BurningC.gold_cost, summon_pos, BurningC.r);
            id[index] = 2;
            break;    
    }
    return true;
}
//========================================store part ended===========================================================

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
LTexture G_ChickenR[2], E_ChickenR[2], B_ChickenR[2];
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
	G_ChickenR[0].loadFromFile("img/GoldCR.png", renderer);
	G_ChickenR[1].loadFromFile("img/GoldC2R.png", renderer);
	E_ChickenR[0].loadFromFile("img/ElectricityCR.png", renderer);
	E_ChickenR[1].loadFromFile("img/ElectricityC2R.png", renderer);
	B_ChickenR[0].loadFromFile("img/BurningCR.png", renderer);
	B_ChickenR[1].loadFromFile("img/BurningC2R.png", renderer);
	Enemy[0].loadFromFile("img/Calculus.png", renderer);
	Enemy[1].loadFromFile("img/KFire.png", renderer);
	Enemy[2].loadFromFile("img/Bujo.png", renderer);
	Enemy[3].loadFromFile("img/Deadline.png", renderer);
	ScoreBoard.loadFromFile("img/ScoreBoard.png", renderer);
	//EggNumber.loadFromRenderedText("0", black, renderer, font32);
}
//=======================================Texture Setting part ended====================================================


Node *head = new Node, *tail = new Node;
bool turn = false;

void move(){
	//move chicken
	player.Moving_Chicken();

    for(int i = 1; i <= 8; i++){
        if(isalive[i] == 1){
            switch(id[i]){
                case 0:
                    GoldChickens[i].Moving_Chicken();
                    break;
                case 1:
                    ElectricityChickens[i].Moving_Chicken();
                    break;
                case 2:
                    BurningChickens[i].Moving_Chicken();
                    break;
            }
        }
    }
	//move Enemy 
	Node *now = head->next, *temp;
	bool check;
    int check_index, check_id;
	while(now != tail){
		now->val.move();
		check = false;
        check_index = -1; check_id = -1;
        // Collide Chickens
		if(now->val.get_id() == 3){
            check = isCollided2(player, now->val, Enemy[3].getWidth() * (E_prop[3].r / Enemy[3].getHeight()));	
            if(check) check_index = 0;
            for(int i = 1; i <= 8; i++){
                if(isalive[i] == 0) continue;
                switch(id[i]){
                    case 0:
                        check = isCollided2(GoldChickens[i], now->val, w);	
                        if(check && check_index != 0){
                            check_index = i;
                            check_id = 0;
                        }  
                        break; 
                    case 1:
                        check = isCollided2(ElectricityChickens[i], now->val, w);	
                        if(check && check_index != 0){
                            check_index = i;
                            check_id = 1;
                        }  
                        break;
                    case 2:
                        check = isCollided2(BurningChickens[i], now->val, w);	
                        if(check && check_index != 0){
                            check_index = i; 
                            check_id = 2;
                            
                        } 
                        break;
                }
            }
        } 
        else{
            check = isCollided(player, now->val);
            if(check) check_index = 0;
            for(int i = 1; i <= 8; i++){
                switch(id[i]){
                    case 0:
                        check = isCollided(GoldChickens[i], now->val);
                        if(check && check_index != 0){
                            check_index = i;
                            check_id = 0;
                        } 
                        break; 
                    case 1:
                        check = isCollided(ElectricityChickens[i], now->val);
                        if(check && check_index != 0){
                            check_index = i;
                            check_id = 1;
                        } 
                        break;
                    case 2:
                        check = isCollided(BurningChickens[i], now->val);
                        if(check && check_index != 0){
                            check_index = i; 
                            check_id = 2;
                            
                        } 
                        break;
                }
            }
        } 

		if(check){
            if(check_index == 0){
                if(!player.adjust_hp(-now->val.get_dmg())){
				    gameRunning = false;
				    return;
			    }
            }
            else{
                switch(check_id){
                    case 0:
                        if(!GoldChickens[check_index].adjust_hp(-now->val.get_dmg())){
				            isalive[check_index] = 0;
			            }
                        break; 
                    case 1:
                        if(!ElectricityChickens[check_index].adjust_hp(-now->val.get_dmg())){
				            isalive[check_index] = 0;
			            }
                        break;
                    case 2:
                        if(!BurningChickens[check_index].adjust_hp(-now->val.get_dmg())){
				            isalive[check_index] = 0;
			            }
                        break;
                }

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
		else if(kind == 2) nd = new Node(Bujo(pos, E_prop[kind].dmg, SDL_GetTicks(), E_prop[kind].lasting_time, v, E_prop[kind].r, 2));
		else if(kind == 3) nd = new Node(Deadline(pos, E_prop[kind].dmg, SDL_GetTicks(), E_prop[kind].lasting_time, v, E_prop[kind].r, 3));
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
    for(int i = 1; i <= 8; i++){
        if(isalive[i] == 1){
            switch(id[i]){
                case 0:
                    render_pos = GoldChickens[i].get_pos();
                    G_Chicken[walk / 40].render(render_pos.x -  GoldC.r, render_pos.y - GoldC.r, GoldC.r * 2, GoldC.r * 2, renderer);
                    break;
                case 1:
                    render_pos = ElectricityChickens[i].get_pos();
                    E_Chicken[walk / 40].render(render_pos.x -  ElectricityC.r, render_pos.y - ElectricityC.r, ElectricityC.r * 2, ElectricityC.r * 2, renderer);
                    break;
                case 2:
                    render_pos = BurningChickens[i].get_pos();
                    B_Chicken[walk / 40].render(render_pos.x -  BurningC.r, render_pos.y - BurningC.r, BurningC.r * 2, BurningC.r * 2, renderer);
                    break;          
            }
        }
    }
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
    bool buy_valid = 0;
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
						turn = false;
					}
					else if(event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN){
						player.modify_speed(2);
					}
					else if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT){
						player.modify_speed(3);
						turn = true;
					}
					else continue;
                //TODO : Set store position
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.x <= ????? && event.button.x >= ????? && event.button.y <= ????? && event.button.y >= ?????){
                        buy_valid = Summon_Chicken(0);
                    }
                    else if(event.button.x <= ????? && event.button.x >= ????? && event.button.y <= ????? && event.button.y >= ?????){
                        buy_valid = Summon_Chicken(1);
                    }
                    else if(event.button.x <= ????? && event.button.x >= ????? && event.button.y <= ????? && event.button.y >= ?????){
                        buy_valid = Summon_Chicken(2);
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