#pragma once

class Vector2D{
	public:
		float x, y;
		
		Vector2D();
		Vector2D(float xx, float yy);
		
		friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
		friend float operator-(const Vector2D &v1, const Vector2D &v2);
		Vector2D &operator+=(const Vector2D &v);
};

Vector2D get_mag_of(float x);
