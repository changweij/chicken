#pragma once
#include "Vector2D.h"
#define Max_Level 5
#define Max_Radius 5

extern float border_x, border_y;
extern float default_infinity_time;
//================================================ Base Chicken ====================================================
class Chicken{
    protected:
        int max_hp, current_hp;
        int gold_cost;
        static float move_speed;
        Vector2D pos;
        Vector2D speed;
        float radius;

        bool is_alive;
        bool is_freeze;
        
		
        

    public:

        Chicken();
        Chicken(int _max_hp, int _current_hp, int _gold_cost, Vector2D &v, float r);

        void adjust_hp(int);
        void Moving_Chicken();
        void freeze_chicken();
        void modify_speed(int);
        Vector2D get_pos();
        

};

//================================================ Second level ====================================================
class GoldProduction: public Chicken{
    protected:
        int current_production[Max_Level + 1];
        double cooldown[Max_Level + 1];
        int production_level;  
        
    public:
        //GoldProduction();
        GoldProduction(int _level, int _max_hp, int _current_hp, int _gold_cost, Vector2D _pos, float _r); // setup level
        //GoldProduction(int [], double []);
        //GoldProduction(int, int [], double []);

        
};

class SpeedBoost: public Chicken{
    protected:
        double move_speed_boost[Max_Level + 1];
        int speed_level;
    public:
        //SpeedBoost();
        SpeedBoost(int _level, int _max_hp, int _current_hp, int _gold_cost, Vector2D _pos, float _r); // setup level
        //SpeedBoost(double []);
        //SpeedBoost(int, double []);
};

class Burning : public Chicken{
    protected:
        //int burning_boost[Max_Level][2 * Max_Radius - 1][2 * Max_Radius - 1];
        int burn_level;      
        int damage[Max_Level];
    public:
        //Burning();
        Burning(int _level, int _max_hp, int _current_hp, int _gold_cost, Vector2D _pos, float _r); //setup level
};

/*
class Shield : public Chicken{
    private:
        int shield_field[Max_Level][2 * Max_Radius - 1][2 * Max_Radius - 1];
        int shield_level;
    public:
        Shield();
};

class Potion : public Chicken{
    private:
        double cooldown[Max_Level + 1];
        int potion_level;
    public:
        Potion();
};

class Heal : public Chicken{
    private:
        double cooldown[Max_Level + 1];
        double heal_field[2 * Max_Radius - 1][2 * Max_Radius - 1];
        int heal_level;
    public:
};

*/
//================================================ Third level ====================================================
class GoldChicken : public GoldProduction{
    private:
        
    public:
        //GoldChicken();
        GoldChicken(int _level, Vector2D _pos);
        
};
/*
class SuperGoldChicken : public GoldProduction{
    private:

    public:
};
*/
class EletricityChicken : public SpeedBoost{
    private:
        
    public:
        //EletricityChicken();
        EletricityChicken(int _level, Vector2D _pos);
        
};

class BurningChicken : public Burning, public SpeedBoost{
    private:
        
    public:
        //BurningChicken();
        BurningChicken(int spd_level, int burn, Vector2D _pos);

};
/*
class SuperBurningChicken : public Burning, public GoldProduction, public SpeedBoost{
    private:
        
    public:
        SuperBurningChicken();
};
*/
/*
class HealerChicken : public Heal{
    private:

    public:
};

class HealPotionChicken : public Potion {
    private:
        double heal_level[Max_Level];
    public:

};

class InvisiblePotionChicken : public Potion{
    private:
        double invisivble_time[Max_Level];
    public:
};
*/
