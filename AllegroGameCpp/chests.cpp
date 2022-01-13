#include "mainHeader.hpp"

void Chests::setItem(Item item_){
    item = item_;
}

void Chests::setOpenStatus(bool status_){
    open = status_;
}

bool Chests::isOpen(){
    return open;
}

Item Chests::returnItem(){
    return item;
}

Coordinates Chests::returnCoord(){
    return coord;
}

HitBoxRange Chests::returnHitbox(){
    return hitbox;
}

void Chests::setCoord(int x_, int y_){
    coord.x = x_;
    coord.y = y_;
    setHitbox();
}

void Chests::loadBitmapOpen(char* fileName){
    bitmapOpen = al_load_bitmap(fileName);
}

void Chests::loadBitmapClosed(char* fileName){
    bitmapClosed = al_load_bitmap(fileName);
}

void Chests::drawBitmap(){
    if (open)
        al_draw_bitmap(bitmapOpen, coord.x, coord.y, 0);
    else
        al_draw_bitmap(bitmapClosed, coord.x, coord.y, 0);
}

void Chests::setHitbox(){
    hitbox.inf.x = coord.x;
    hitbox.inf.y = coord.y;
    hitbox.sup.x = coord.x + 40;
    hitbox.sup.y = coord.y + 40;
}
