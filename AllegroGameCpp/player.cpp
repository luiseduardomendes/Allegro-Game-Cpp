#include "mainHeader.hpp"

void Player::movePlayer(){

    coord.y -= keyDown[UP] * 5;
    coord.y += keyDown[DOWN] * 5;
    coord.x -= keyDown[LEFT] * 5;
    coord.x += keyDown[RIGHT] * 5;

    setNewDirectionAfterMove();
}

void Player::setKeyDown(int key_, bool value_){
    keyDown[key_] = value_;
}

void Player::setNewDirectionAfterMove(){
    if(keyDown[UP] + keyDown[DOWN] != 1){
        switch(keyDown[RIGHT] - keyDown[LEFT]){
        case -1:
            setDirection(LEFT);
            break;
        case 1:
            setDirection(RIGHT);
            break;
        }
    }
    else {
        if (keyDown[RIGHT] + keyDown[LEFT] == 0){
            switch(keyDown[DOWN] - keyDown[UP]){
            case -1:
                setDirection(UP);
                break;
            case 1:
                setDirection(DOWN);
                break;
            }
        }
    }
}

void Player::setDirection(int dir_){
    directionView = dir_;
}

void Player::loadBitmap(char nameFile[], int dir_){
    switch (dir_){
    case UP:
        bitmapUp = al_load_bitmap(nameFile);
        break;
    case DOWN:
        bitmapDown = al_load_bitmap(nameFile);
        break;
    case LEFT:
        bitmapLeft = al_load_bitmap(nameFile);
        break;
    case RIGHT:
        bitmapRight = al_load_bitmap(nameFile);
        break;
    }
}

void Player::drawPlayer(){
    switch(directionView){
    case UP:
        al_draw_scaled_bitmap(bitmapUp, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    case DOWN:
        al_draw_scaled_bitmap(bitmapDown, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    case LEFT:
        al_draw_scaled_bitmap(bitmapLeft, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    case RIGHT:
        al_draw_scaled_bitmap(bitmapRight, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    }
}

void Player::setPosition(int x_, int y_){
    coord.x = x_;
    coord.y = y_;
}

void Player::setHitBox(){
    hitBox.inf.x = coord.x;
    hitBox.inf.y = coord.y;
    hitBox.sup.x = coord.x + 60;
    hitBox.sup.y = coord.y + 60;
}

void Player::keyDownInit(){
    for (int i = 0; i < 4; i ++)
        keyDown[i] = false;
}

Coordinates Player::showCoord(){
    return coord;
}

HitBoxRange Player::showHitBox(){
    return hitBox;
}


void Player::throwProjectile(){
    projectile.setThrowingStatus(true);
    for (int i = 0; i < 4; i ++)
        projectile.setProjDir(i, 0);
    projectile.setProjDir(directionView, -10);
    projectile.setCoord(coord.x, coord.y);
}
