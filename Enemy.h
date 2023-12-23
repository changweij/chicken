#include "Vector2D.h"

class Enemy{
	public:
		Enemy(Vector2D &v, int damage, int cur_time, int lasting_time);
		~Enemy(); 
		Vector2D get_pos();
		int get_dmg();
		bool isDead(int cur_time);
	protected:
		Vector2D pos;
		int dmg, deadtime;
};

class Moving_Enemy: public Enemy{
	public:
		Moving_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s);
		void move();
	protected:
		Vector2D speed;
};

class Fixed_Enemy: public Enemy{
	public:
		Fixed_Enemy(Vector2D &v, int damage, int cur_time, int lasting_time, int perc);
	protected:
		int percentage;
};

// ==========================================Moving items=========================================================
class Calculus: public Moving_Enemy{
	public:
		Calculus(Vector2D &v, int damage, int cur_time, int lasting_time, Vector2D &s);
};

// ===========================================Fixed Items==========================================================
class Fire: public Fixed_Enemy{
	public:
		Fire(Vector2D &v, int damage, int cur_time, int lasting_time, int perc);
};

