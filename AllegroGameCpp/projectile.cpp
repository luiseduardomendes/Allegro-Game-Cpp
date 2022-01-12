#include "mainHeader.hpp"

void Projectile::initProjectile(){
    throwing = false;
    damage = 100;
    speed = 8;
    for (int i = 0; i < 4; i ++)
        moveDir[i] = 0;
}

void Projectile::moveProj(){
    coord.y -= moveDir[UP]*(float)speed;
    coord.y += moveDir[DOWN]*(float)speed;
    coord.x -= moveDir[LEFT]*(float)speed;
    coord.x += moveDir[RIGHT]*(float)speed;

    setHitBox();
}

void Projectile::setCoord(int x_, int y_){
    coord.x = x_;
    coord.y = y_;
}

void Projectile::setSpeed(int value_){
    speed = value_;
}

void Projectile::setProjDir(int dir_, float value_){
    moveDir[dir_] = value_;
}

void Projectile::setHitBox(){
    hitBox.inf.x = coord.x;
    hitBox.inf.y = coord.y;
    hitBox.sup.x = coord.x + 40;
    hitBox.sup.y = coord.y + 40;
}

void Projectile::loadBitmap(char fileName[]){
    bitmap = al_load_bitmap(fileName);
}

Coordinates Projectile::projectileCoord(){
    return coord;
}

HitBoxRange Projectile::showHitBox(){
    return hitBox;
}

void Projectile::drawBitmap(){
    al_draw_scaled_bitmap(bitmap, 0, 0, 40, 40, coord.x, coord.y, 40, 40, 0);
}

void Projectile::setThrowingStatus(int value_){
    throwing = value_;
}

bool Projectile::isThrowing(){
    return throwing;
}

void Projectile::drawHitbox(){
    Colors colors;
    al_draw_rectangle(hitBox.inf.x, hitBox.inf.y, hitBox.sup.x, hitBox.sup.y, colors.pastelBlue(), 1);
}

int Projectile::showDamage(){
    return damage;
}
