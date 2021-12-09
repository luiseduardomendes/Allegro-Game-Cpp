#include "mainHeader.hpp"

void Player::movePlayer(){

    y -= keyDown[UP] * 5;
    y += keyDown[DOWN] * 5;
    x -= keyDown[LEFT] * 5;
    x += keyDown[RIGHT] * 5;

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
        al_draw_bitmap(bitmapUp, x, y, 0);
        break;
    case DOWN:
        al_draw_bitmap(bitmapDown, x, y, 0);
        break;
    case LEFT:
        al_draw_bitmap(bitmapLeft, x, y, 0);
        break;
    case RIGHT:
        al_draw_bitmap(bitmapRight, x, y, 0);
        break;
    }
}

void Player::setPosition(int x_, int y_){
    x = x_;
    y = y_;
}

void Player::keyDownInit(){
    for (int i = 0; i < 4; i ++)
        keyDown[i] = false;
}




