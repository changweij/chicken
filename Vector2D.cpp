#include "Vector2D.h"

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
