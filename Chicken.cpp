#pragma once
#include "Chicken.h"
#include "Vector2D.h"
#include "fundamental.h"
//================================================ Base Chicken ====================================================

//Chicken
float Chicken::Move_speed = 1.0;
int Chicken::Gold = 0;

// Constructor
Chicken::Chicken(){
    max_hp = 0;
    current_hp = 0;
    
    is_alive = 0;
    is_freeze = 0;

}
Chicken::Chicken(int _max_hp, int _current_hp, int _gold_cost, Vector2D &v, float r){
    max_hp = _max_hp;
    current_hp = _current_hp;
    gold_cost = _gold_cost;
    pos = v;
    radius = r;
    is_alive = 1;
    is_freeze = 0;
}

// Functions
void Chicken::adjust_hp(int _adjustment){
    if(current_hp + _adjustment >= max_hp) current_hp = max_hp;
    else if(current_hp + _adjustment <= 0){
        current_hp = 0;
        is_alive = 0;
        is_freeze = 0;
    }
    else{
        current_hp += _adjustment;
    }
}
void Chicken::Moving_Chicken(){
	pos += speed;
	
	//check border
	if(pos.x - radius < 0){
		pos.x += (radius - pos.x) * 2; 
	}
	else if(pos.x + radius > border_x){
		pos.x -= (radius - border_x + pos.x) * 2;
	}
	if(pos.y - radius < 0){
		pos.y += (radius - pos.y) * 2; 
	}
	else if(pos.y + radius > border_y){
		pos.y -= (radius - border_y + pos.x) * 2;
	}
}
void Chicken::modify_speed(int _dir){
    switch(_dir){
        case 0: // up
            speed.x = 0;
            speed.y = -Move_speed; 
            break;
        case 1: // left
            speed.x = -Move_speed;
            speed.y = 0;
            break;
        case 2: //down
            speed.x = 0;   
            speed.y = Move_speed;
            break;
        case 3: //right
            speed.x = Move_speed;
            speed.y = 0;
            break;
    }
}

Vector2D Chicken::get_pos(){
    return pos;
}

void Chicken::freeze_chicken(){
    is_freeze = 1;
}


//================================================ Second level ====================================================


//GoldProduction

GoldProduction::GoldProduction(int _level, int _max_hp, int _current_hp, int _gold_cost, Vector2D _pos, float _r):
    Chicken(_max_hp, _current_hp, _gold_cost, _pos, _r)
{

    production_level = _level;
    
    current_production[0] = 0;
    current_production[1] = 1;
    current_production[2] = 2;
    current_production[3] = 3;
    current_production[4] = 5;
    current_production[5] = 8;

    cooldown[0] = default_infinity_time;
    cooldown[1] = 20.0;
    cooldown[2] = 15.0;
    cooldown[3] = 10.0;
    cooldown[4] = 8.0;
    cooldown[5] = 5.0;

}

SpeedBoost::SpeedBoost(int _level, int _max_hp, int _current_hp, int _gold_cost, Vector2D _pos, float _r):
    Chicken(_max_hp, _current_hp, _gold_cost, _pos, _r)
{

    
    speed_level = _level;
    move_speed_boost[0] = 0;
    move_speed_boost[1] = 0.1;
    move_speed_boost[2] = 0.2;
    move_speed_boost[3] = 0.35;
    move_speed_boost[4] = 0.6;
    move_speed_boost[5] = 1.0;

}


Burning::Burning(int _level, int _max_hp, int _current_hp, int _gold_cost, Vector2D _pos, float _r):
    Chicken(_max_hp, _current_hp, _gold_cost, _pos, _r)
{

    
    burn_level = _level;
    damage[0] = 0;
    damage[1] = 1;
    damage[2] = 2;
    damage[3] = 3;
    damage[4] = 4;
    damage[5] = 5;
}


//================================================ Third level ====================================================

//GoldChicken


GoldChicken::GoldChicken(int _level, Vector2D _pos):
    GoldProduction(_level, GoldC.max_hp, GoldC.max_hp, GoldC.gold_cost, _pos, GoldC.radius)
{
     // max_hp/current_hp : 20     gold_cost : 5  radius = 10;
}


//EletricityChicken


EletricityChicken::EletricityChicken(int _level, Vector2D _pos):
    SpeedBoost(_level, EletricityC.max_hp, EletricityC.max_hp, EletricityC.gold_cost, _pos, EletricityC.radius)
{

}

//BurningChicken

BurningChicken::BurningChicken(int spd_level, int burn_level, Vector2D _pos):
    SpeedBoost(spd_level, BurningC.max_hp, BurningC.max_hp, BurningC.gold_cost, _pos, BurningC.radius), 
    Burning(burn_level, BurningC.max_hp, BurningC.max_hp, BurningC.gold_cost, _pos, BurningC.radius)
{
    
}
    