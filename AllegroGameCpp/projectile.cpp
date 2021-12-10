#include "mainHeader.hpp"

void Projectile::moveProj(){
    coord.y += moveDir[UP];
    coord.y -= moveDir[DOWN];
    coord.x += moveDir[LEFT];
    coord.x -= moveDir[RIGHT];
}

void Projectile::setCoord(int x_, int y_){
    coord.x = x_;
    coord.y = y_;
}

void Projectile::setProjDir(int dir_, int value_){
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

void Projectile::drawBitmap(){
    al_draw_bitmap(bitmap, coord.x, coord.y, 0);
}
