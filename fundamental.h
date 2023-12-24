#pragma once
float border_x = 640;
float border_y = 480;

float window_x = 640;
float window_y = 480;

float default_infinity_time = 10000.0; 
const int EnemyCategories = 2;

struct Chicken_Property{
    int max_hp;
    int gold_cost;
    float radius;
    float size_radius;
    Chicken_Property(int hp, int cost, float r, float size): max_hp(hp), gold_cost(cost), radius(r), size_radius(size){}
};

Chicken_Property GoldC(20, 5, 10.0, 60);
Chicken_Property EletricityC(10, 10, 10.0, 60);
Chicken_Property BurningC(20, 20, 10.0, 60);

struct Enemy_Property{
	int dmg, lasting_time;
	float v;
	float r;
    float size_radius;
	Enemy_Property(int dmg, int lasting_time, float v, float r, float size): dmg(dmg), lasting_time(lasting_time), v(v), r(r), size_radius(size){}
};

Enemy_Property Cal(2, 10, 1.0, 10.0, 50);

