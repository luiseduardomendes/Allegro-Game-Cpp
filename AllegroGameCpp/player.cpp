#include "mainHeader.hpp"

void Player::movePlayer(ALLEGRO_EVENT event){

    if (event.type == ALLEGRO_EVENT_KEY_DOWN){
        switchMovement(event);
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        stopMovement(event);
    }

    y -= keyDown[UP] * 5;
    y += keyDown[DOWN] * 5;
    x -= keyDown[LEFT] * 5;
    x += keyDown[RIGHT] * 5;

    if(keyDown[UP] + keyDown[DOWN] == 0){
        switch(keyDown[RIGHT] + keyDown[LEFT]){
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
            switch(keyDown[UP] + keyDown[DOWN]){
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
    }
}

void Player::drawPlayer(){
    al_draw_bitmap(bitmapUp, x, y, 0);
}

void Player::setPosition(int x_, int y_){
    x = x_;
    y = y_;
}

void Player::keyDownInit(){
    for (int i = 0; i < 4; i ++)
        keyDown[i] = false;
}

void Player::switchMovement(ALLEGRO_EVENT event){

    switch (event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
            keyDown[UP] = true;
            break;
        case ALLEGRO_KEY_DOWN:
            keyDown[DOWN] = true;
            break;
        case ALLEGRO_KEY_LEFT:
            keyDown[LEFT] = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            keyDown[RIGHT] = true;
            break;
    }
}

void Player::stopMovement(ALLEGRO_EVENT event){
    switch (event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
            keyDown[UP] = false;
            break;
        case ALLEGRO_KEY_DOWN:
            keyDown[DOWN] = false;
            break;
        case ALLEGRO_KEY_LEFT:
            keyDown[LEFT] = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            keyDown[RIGHT] = false;
            break;
    }
}
