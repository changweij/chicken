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

        static float Move_speed;
        static int Produce_speed;
        static int Production;

        Vector2D pos;
        Vector2D speed;
        float radius;

        bool is_alive;
        bool is_freeze;

    public:

        Chicken();
        Chicken(int _max_hp, int _gold_cost, Vector2D &v, float r);

        bool adjust_hp(int);
        void Moving_Chicken();
        void freeze_chicken();
        void modify_speed(int);
        Vector2D get_pos();
        float get_radius();
        
		int get_Produce_speed();
        int get_Production();
        void adjust_Produce_speed();
        void adjust_Production();
};

//================================================ Second level ====================================================
class GoldProduction: public Chicken{
    protected:
        int current_production[Max_Level + 1];
        double cooldown[Max_Level + 1];
        int production_level;  
        
    public:
        //GoldProduction();
        GoldProduction(int _level, int _max_hp, int _gold_cost, Vector2D _pos, float _r); // setup level
        //GoldProduction(int [], double []);
        //GoldProduction(int, int [], double []);

        
};

class SpeedBoost: public Chicken{
    protected:
        double move_speed_boost[Max_Level + 1];
        int speed_level;
    public:
        //SpeedBoost();
        SpeedBoost(int _level, int _max_hp, int _gold_cost, Vector2D _pos, float _r); // setup level
        //SpeedBoost(double []);
        //SpeedBoost(int, double []);
};

class Burning : public Chicken{
    protected:
        //int burning_boost[Max_Level][2 * Max_Radius - 1][2 * Max_Radius - 1];
        int burn_level;      
        int damage[Max_Level + 1];
    public:
        //Burning();
        Burning(int _level, int _max_hp, int _gold_cost, Vector2D _pos, float _r); //setup level
};
//================================================ Third level ====================================================
class GoldChicken : public GoldProduction{
    private:
        
    public:
        //GoldChicken();
        GoldChicken(int _level, int _max_hp, int _gold_cost, Vector2D _pos, float _r);
        
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
        EletricityChicken(int _level, int _max_hp, int _gold_cost, Vector2D _pos, float _r);
        
};

class BurningChicken : public Burning, public SpeedBoost{
    private:
        
    public:
        //BurningChicken();
        BurningChicken(int _level, int _max_hp, int _gold_cost, Vector2D _pos, float _r);

};
