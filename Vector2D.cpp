#pragma once
#include "Vector2D.h"
#include <cstdlib>
#include <cmath>

Vector2D::Vector2D(){
	x = y = 0.0f;
}

Vector2D::Vector2D(float xx, float yy){
	x = xx;
	y = yy;
}

Vector2D& Vector2D::operator+=(const Vector2D &v){
	x += v.x;
	y += v.y;
}

Vector2D operator+(const Vector2D &v1, const Vector2D &v2){
	return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

float operator-(const Vector2D &v1, const Vector2D &v2){
	return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

Vector2D get_mag_of(float x){
	double vx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/x)), vy = sqrt(x * x - vx * vx);
	int k1 = rand() % 2;
	if(k1) vx *= -1;
	k1 = rand() % 2;
	if(k1) vy *= -1;
	return Vector2D(vx, vy);
}
