const double dt = 0.01;
const int default_infinity_time = 10000;
const float border_x = 1000;
const float border_y = 1000;

struct Chicken_Property{
    int max_hp;
    int gold_cost;
    float radius;
};

Chicken_Property GoldC;
GoldC.max_hp = 20;
GoldC.gold_cost = 5;
GoldC.radius = 10.0;



Chicken_Property EletricityC;
EletricityC.max_hp = 10;
EletricityC.gold_cost = 10;
EletricityC.radius = 10.0;



Chicken_Property BurningC;
BurningC.max_hp = 20;
BurningC.gold_cost = 20;
BurningC.radius = 10.0;




struct Enemy_Property{


};

