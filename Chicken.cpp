#include "Chicken.h"
#include "fundamental.h"


extern const double dt;
extern const int default_infinity_time;
//================================================ Base Chicken ====================================================


//Chicken

// Constructor

double Chicken::move_speed = 0.0;
Chicken::Chicken(){
    max_hp = 0;
    current_hp = 0;
    pos_x = 0; pos_y = 0;
    is_alive = 0;
    is_freeze = 0;
}
Chicken::Chicken(int _max_hp, int _current_hp, int _gold_cost, double _pos_x, double _pos_y){
    max_hp = _max_hp;
    current_hp = _current_hp;
    gold_cost = _gold_cost;
    pos_x = _pos_x; pos_y = _pos_y;
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



void Chicken::move(int _direction){
    //TODO enum direction
    switch(_direction){
        case 1:
            pos_x += move_speed * dt;
            break;
        case 2:
            pos_y += move_speed * dt;
            break;
        case 3:
            pos_x -= move_speed * dt;
            break;
        case 4:
            pos_y -= move_speed * dt;
            break;
    }
}
double Chicken::GetPos_x(){
    return pos_x;
}
double Chicken::GetPos_y(){
    return pos_y;
}

void Chicken::freeze_chicken(){
    is_freeze = 1;
}





//================================================ Second level ====================================================


//GoldProduction

//Constructor
/*
GoldProduction::GoldProduction(){
    //init gold / cooldown / level = 0
    production_level = 0;
    for(int i = 0; i <= Max_Level; i++){
        current_production[i] = 0;
        cooldown[i] = 0;
    }

}
*/
GoldProduction::GoldProduction(int _level, int _max_hp, int _current_hp, int _gold_cost, double _pos_x, double _pos_y){
    //init gold / cooldown / level = 0
    Chicken(_max_hp, _current_hp, _gold_cost, _pos_x, _pos_y);
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
/*
GoldProduction::GoldProduction(int _current_production[], double _cooldown[]){
    //setup gold / cooldown
    production_level = 0;
    for(int i = 0; i <= Max_Level; i++){
        current_production[i] = _current_production[i];
        cooldown[i] = _cooldown[i];
    }

}

GoldProduction::GoldProduction(int _level, int _current_production[], double _cooldown[]){
    //setup gold / cooldown / level
    production_level = _level;

    for(int i = 0; i <= Max_Level; i++){
        current_production[i] = _current_production[i];
        cooldown[i] = _cooldown[i];
    }
    
}
*/


//SpeedBoost
/*
SpeedBoost::SpeedBoost(){
    speed_level = 0;
    for(int i = 0; i <= Max_Level; i++){
        move_speed_boost[i] = 0;
    }
}
*/
SpeedBoost::SpeedBoost(int _level, int _max_hp, int _current_hp, int _gold_cost, double _pos_x, double _pos_y){

    Chicken(_max_hp, _current_hp, _gold_cost, _pos_x, _pos_y);
    speed_level = _level;
    move_speed_boost[0] = 0;
    move_speed_boost[1] = 0.1;
    move_speed_boost[2] = 0.2;
    move_speed_boost[3] = 0.35;
    move_speed_boost[4] = 0.6;
    move_speed_boost[5] = 1.0;

}

/*
SpeedBoost::SpeedBoost(double _move_speed_boost[]){
    speed_level = 0;
    for(int i = 0; i <= Max_Level; i++){
        move_speed_boost[i] = _move_speed_boost[i];
    }
    
}

SpeedBoost::SpeedBoost(int _level, double _move_speed_boost[]){
    speed_level = _level;
    for(int i = 0; i <= Max_Level; i++){
        move_speed_boost[i] = _move_speed_boost[i];
    }
    
}
*/
//Burning

Burning::Burning(int _level, int _max_hp, int _current_hp, int _gold_cost, double _pos_x, double _pos_y){

    Chicken(_max_hp, _current_hp, _gold_cost, _pos_x, _pos_y);
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
/*
GoldChicken::GoldChicken() : GoldProduction(0){

    
    
    //TODO Set current_production[] : golden eggs / cooldown => can use enum
    current_production[0] = 0;
    current_production[1] = 1;
    current_production[2] = 2;
    current_production[3] = 3;
    current_production[4] = 5;
    current_production[5] = 8;

    //TODO Set cooldown[] : cooldown => can use enum
    cooldown[0] = default_infinity_time;
    cooldown[1] = 20.0;
    cooldown[2] = 15.0;
    cooldown[3] = 10.0;
    cooldown[4] = 8.0;
    cooldown[5] = 5.0;

    production_level = 0;
    

}
*/

GoldChicken::GoldChicken(int _level, double x, double y){
    GoldProduction(_level, 10, 10, 5, x, y); // max_hp/current_hp : 10     gold_cost : 5
}


//EletricityChicken


EletricityChicken::EletricityChicken(int _level, double x, double y){
    SpeedBoost(_level, 10, 10, 10, x, y);
    //TODO : setup speed boost
    /*
    move_speed_boost[0] = 0;
    move_speed_boost[1] = 0.1;
    move_speed_boost[2] = 0.2;
    move_speed_boost[3] = 0.35;
    move_speed_boost[4] = 0.6;
    move_speed_boost[4] = 1.0;

    speed_level = _level;
    */
}

//BurningChicken

BurningChicken::BurningChicken(int spd_level, int burn_level, double x, double y){
    SpeedBoost(spd_level, 20, 20, 20, x, y);
    Burning(burn_level, 20, 20, 20, x, y);

    //TODO : setup speed boost
}
    