#include "mainHeader.hpp"

void Player::movePlayer(){

    coord.y -= keyDown[UP] * moveSpeed;
    coord.y += keyDown[DOWN] * moveSpeed;
    coord.x -= keyDown[LEFT] * moveSpeed;
    coord.x += keyDown[RIGHT] * moveSpeed;

    setNewDirectionAfterMove();
    setHitBox();
}

void Player::setKeyDown(int key_, bool value_){
    keyDown[key_] = value_;
}

bool* Player::showKeyDown(){
    return keyDown;
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

void Player::initPlayer(){
    health = 600;
    fullHp = 600;
    moveSpeed = 3;
    stdSpeed = 3;
    keyDownInit();
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

void Player::drawHitbox(){
    Colors colors;
    al_draw_rectangle(hitBox.inf.x, hitBox.inf.y, hitBox.sup.x, hitBox.sup.y, colors.pastelBlue(), 1);
}

void Player::drawHealthBar(){
    al_draw_filled_rectangle(coord.x, coord.y - 5, coord.x + ((60*health)/fullHp), coord.y , al_map_rgb(0, 255, 0));
    al_draw_filled_rectangle(coord.x + ((60*health)/fullHp), coord.y -5, coord.x+60, coord.y, al_map_rgb(80, 80, 80));
}

void Player::setSpeed(int value_){
    moveSpeed = value_;
}

void Player::throwProjectile(){
    projectile.setThrowingStatus(true);
    for (int i = 0; i < 4; i ++)
        projectile.setProjDir(i, 0);
    projectile.setProjDir(directionView, 1);
    projectile.setCoord(coord.x + 10, coord.y + 10);
}

void Player::decrementHealth(int value_){
    health -= value_;
}

int Player::showHealth(){
    return health;
}


void Player::initTimer(int timer_, double value_){
    switch (timer_){
    case TIMER_SLOW:
        timerSlow = al_create_timer(value_);
        break;
    }
}

void Player::startTimer(int timer_){
    switch (timer_){
    case TIMER_SLOW:
        al_start_timer(timerSlow);
        break;
    }
}

void Player::stopTimer(int timer_){
    switch (timer_){
    case TIMER_SLOW:
        al_stop_timer(timerSlow);
        break;
    }
}

ALLEGRO_TIMER* Player::showTimer(int timer_){
    switch(timer_){
    case TIMER_SLOW:
        return timerSlow;
    }
}

void Player::setSlow(double value_){
    slowned = true;
    moveSpeed = moveSpeed * value_;
}

void Player::resetSpeed(){
    slowned = false;
    moveSpeed = stdSpeed;
}
