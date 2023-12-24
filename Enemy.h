#pragma once
#include "Vector2D.h"

extern float border_x;
extern float border_y;

class Enemy{
	public:
		Enemy(){}
		Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, float r, int _id);
		~Enemy(); 
		Vector2D get_pos();
		int get_dmg();
		bool isDead(int cur_time);
		virtual void move(){}
	protected:
		Vector2D pos;
		float radius;
		int dmg, deadtime, id;
};

class Moving_Enemy: public Enemy{
	public:
		Moving_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s, float r, int _id);
		void move();
	protected:
		Vector2D speed;
};

class Fixed_Enemy: public Enemy{
	public:
		Fixed_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, float r, int _id);
};

// ==========================================Moving items=========================================================
class Calculus: public Moving_Enemy{
	public:
		Calculus(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s, float r, int _id);
};

// ===========================================Fixed Items==========================================================
class Fire: public Fixed_Enemy{
	public:
		Fire(Vector2D &v, int damage, int cur_time, int lasting_time, float r, int _id);
};

