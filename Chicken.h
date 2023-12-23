#define Max_Level 5
#define Max_Radius 5



//================================================ Base Chicken ====================================================
class Chicken{
    private:
        int max_hp, current_hp;
        int gold_cost;
        static double move_speed;
        double pos_x, pos_y;
        bool is_alive;
        bool is_freeze;
        

    public:

        Chicken();
        Chicken(int, int, int, double, double);

        void adjust_hp(int);
        void move(int);
        void freeze_chicken();
        double GetPos_x();
        double GetPos_y();

};

//================================================ Second level ====================================================
class GoldProduction: public Chicken{
    protected:
        int current_production[Max_Level + 1];
        double cooldown[Max_Level + 1];
        int production_level;  
        
    public:
        //GoldProduction();
        GoldProduction(int, int, int, int, double, double); // setup level
        //GoldProduction(int [], double []);
        //GoldProduction(int, int [], double []);

        
};

class SpeedBoost: public Chicken{
    protected:
        double move_speed_boost[Max_Level + 1];
        int speed_level;
    public:
        //SpeedBoost();
        SpeedBoost(int, int, int, int, double, double); // setup level
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
        Burning(int, int, int, int, double, double); //setup level
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
        GoldChicken(int, double, double);
        
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
        EletricityChicken(int, double, double);
        
};

class BurningChicken : public Burning, public SpeedBoost{
    private:
        
    public:
        //BurningChicken();
        BurningChicken(int spd_level, int burn, double, double);

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

