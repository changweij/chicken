#include "Enemy.h"
#include "constant.h"

Enemy::Enemy(Vector2D &v, int damage, int cur_time, int lasting_time){
	pos = v;
	dmg = damage;
	deadtime = cur_time + lasting_time;
}

Enemy::~Enemy(){
}

Vector2D Enemy::get_pos(){
	return pos;
}

int Enemy::get_dmg(){
	return dmg;
}

Moving_Enemy::Moving_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s): Enemy(v, damage, cur_time, lasting_time){
	speed = s;	
}

void Moving_Enemy::move(){
	pos += speed;
}

Fixed_Enemy::Fixed_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, int perc): Enemy(v, damage, cur_time, lasting_time){
	percentage = perc;	
}

Calculus::Calculus(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s): Moving_Enemy(v, damage, cur_time, lasting_time, s){
}

Fire::Fire(Vector2D &v, int damage, int cur_time, int lasting_time, int perc): Fixed_Enemy(v, damage, cur_time, lasting_time, perc){
}



