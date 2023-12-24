#include "Chicken.h"
#include "Enemy.h"
#include "Vector2D.h"
#include <cmath>

bool IsCollided(Chicken &_chicken, Enemy &_enemy){
    Vector2D ch_pos, e_pos;

    ch_pos = _chicken.get_pos();
    e_pos = _enemy.get_pos();

    float distance = ch_pos - e_pos;

    if(distance < _chicken.get_radius() + _enemy.get_radius()) return true;
    return false;

}
