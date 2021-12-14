#include "mainHeader.hpp"

void Obstacles::setDamage(int value_){
    damage = value_;
}

void Obstacles::setCoord(int x, int y){
    coord.x = x;
    coord.y = y;
}

Coordinates Obstacles::showCoord(){
    return coord;
}

int Obstacles::showDamage(){
    return damage;
}

int Obstacles::showStructure(){
    return structure;
}

void Obstacles::setHitBox(){
    hitBox.inf.x = coord.x;
    hitBox.inf.y = coord.y;
    hitBox.sup.x = coord.x + 40;
    hitBox.sup.y = coord.y + 40;
}

HitBoxRange Obstacles::showHitBox(){
    return hitBox;
}

void Obstacles::drawHitBox(){
    Colors colors;
    al_draw_rectangle(hitBox.inf.x, hitBox.inf.y, hitBox.sup.x, hitBox.sup.y, colors.pastelBlue(), 1);
}
