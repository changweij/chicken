#pragma once
#include "Enemy.h"

Enemy::Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, float r, int _id, Vector2D &s){
	pos = v;
	dmg = damage;
	deadtime = cur_time + lasting_time;
	radius = r;
	id = _id;
	speed = s;
}

Enemy::~Enemy(){
}

Vector2D Enemy::get_pos(){
	return pos;
}

bool Enemy::isDead(int cur_time){
	if(deadtime <= cur_time) return true;
	return false;	
}

int Enemy::get_dmg(){
	return dmg;
}

void Enemy::move(){
	pos += speed;
	//check border
	float border_x = 640, border_y = 480;
	if(pos.x - radius < 0){
		pos.x += (radius - pos.x) * 2; 
		speed.x *= -1;
	}
	else if(pos.x + radius > border_x){
		pos.x -= (radius - border_x + pos.x) * 2;
		speed.x *= -1;
	}
	if(pos.y - radius < 0){
		pos.y += (radius - pos.y) * 2; 
		speed.y *= -1;
	}
	else if(pos.y + radius > border_y){
		pos.y -= (radius - border_y + pos.y) * 2;
		speed.y *= -1;
	}
}

float Enemy::get_radius(){
	return radius;
}

Moving_Enemy::Moving_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s, float r, int _id): Enemy(v, damage, cur_time, lasting_time, r, _id, s){
}

Fixed_Enemy::Fixed_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s, float r, int _id): Enemy(v, damage, cur_time, lasting_time, r, _id, s){
}

Calculus::Calculus(Vector2D &v, int dmg, int cur_time, int lasting_time, Vector2D &s, float r, int _id): Moving_Enemy(v, dmg, cur_time, lasting_time, s, r, _id){
}

Fire::Fire(Vector2D &v, int dmg, int cur_time, int lasting_time, Vector2D &s, float r, int _id): Fixed_Enemy(v, dmg, cur_time, lasting_time, s, r, _id){
}

