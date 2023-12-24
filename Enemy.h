#pragma once
#include "Vector2D.h"

class Enemy{
	public:
		Enemy(){}
		Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, float r, int _id, Vector2D &s);
		~Enemy(); 
		Vector2D get_pos();
		int get_dmg();
		bool isDead(int cur_time);
		void move();
		float get_radius();
	protected:
		Vector2D pos, speed;
		float radius;
		int dmg, deadtime, id;
};

class Moving_Enemy: public Enemy{
	public:
		Moving_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s, float r, int _id);
};

class Fixed_Enemy: public Enemy{
	public:
		Fixed_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D& s, float r, int _id);
};

// ==========================================Moving items=========================================================
class Calculus: public Moving_Enemy{
	public:
		Calculus(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D& s, float r, int _id);
};

// ===========================================Fixed Items==========================================================
class Fire: public Fixed_Enemy{
	public:
		Fire(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D& s, float r, int _id);
};

