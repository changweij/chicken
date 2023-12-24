#include "Enemy.h"
#include "cmath"

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

Moving_Enemy::Moving_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s, float r): Enemy(v, damage, cur_time, lasting_time){
	speed = s;
	radius = r;
}

void Moving_Enemy::move(){
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

Fixed_Enemy::Fixed_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time): Enemy(v, damage, cur_time, lasting_time){
}

Calculus::Calculus(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s, float r): Moving_Enemy(v, damage, cur_time, lasting_time, s, r){
}

Fire::Fire(Vector2D &v, int damage, int cur_time, int lasting_time): Fixed_Enemy(v, damage, cur_time, lasting_time){
}

