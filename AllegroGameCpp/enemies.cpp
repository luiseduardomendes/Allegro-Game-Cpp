#include "mainHeader.hpp"

void Enemies::initEnemy(){
    health = 600;
    fullHp = 600;
    moveSpeed = 5;
    stdSpeed = 2;
    rangeView = 100;
    keyDownInit();
}

void Enemies::moveEnemy(){

    coord.y -= keyDown[UP] * moveSpeed;
    coord.y += keyDown[DOWN] * moveSpeed;
    coord.x -= keyDown[LEFT] * moveSpeed;
    coord.x += keyDown[RIGHT] * moveSpeed;

    setNewDirectionAfterMove();
    setHitBox();

}

void Enemies::setDirectionPlayer(Player player){
    int flagMove;
    Coordinates plCoord = player.showCoord();

    if (checkPlayerDistance(player)){
        if (plCoord.x > coord.x){
            keyDown[UP] = 1;
            keyDown[DOWN] = 0;
        }
        else if (plCoord.x < coord.x){
            keyDown[DOWN] = 0;
            keyDown[UP] = 1;
        }
        if (plCoord.y > coord.y){
            keyDown[LEFT] = 0;
            keyDown[RIGHT] = 1;
        }
        else if (plCoord.y < coord.y){
            keyDown[LEFT] = 1;
            keyDown[RIGHT] = 0;
        }
    }
    else{
        flagMove = rand() % 4;
        keyDownInit();
        switch (flagMove){
        case 0:
            keyDown[UP] = 1;
            break;
        case 1:
            keyDown[DOWN] = 1;
            break;
        case 2:
            keyDown[LEFT] = 1;
            break;
        case 3:
            keyDown[RIGHT] = 1;
            break;
        }

    }
    setNewDirectionAfterMove();
    setHitBox();
}

bool Enemies::checkPlayerDistance(Player player){
    Coordinates PlCoord;
    PlCoord = player.showCoord();
    if (sqrt(pow(PlCoord.x - coord.x, 2) + pow(PlCoord.y - coord.y, 2)) <= rangeView)
        return true;
    else
        return false;
}

void Enemies::keyDownInit(){
    for (int i = 0; i < 4; i ++)
        keyDown[i] = false;
}


void Enemies::setRangeView(int range_){
    rangeView = range_;
}

int  Enemies::showRangeView(){
    return rangeView;
}

void Enemies::setKeyDown(int key_, bool value_){
    keyDown[key_] = value_;
}

void Enemies::setNewDirectionAfterMove(){
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

void Enemies::setDirection(int dir_){
    directionView = dir_;
}

void Enemies::loadBitmap(char nameFile[], int dir_){
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

void Enemies::drawBitmap(){
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

void Enemies::setPosition(int x_, int y_){
    coord.x = x_;
    coord.y = y_;
}

void Enemies::setHitBox(){
    hitBox.inf.x = coord.x;
    hitBox.inf.y = coord.y;
    hitBox.sup.x = coord.x + 60;
    hitBox.sup.y = coord.y + 60;
}

void Enemies::drawHitbox(){
    Colors colors;
    al_draw_rectangle(hitBox.inf.x, hitBox.inf.y, hitBox.sup.x, hitBox.sup.y, colors.pastelBlue(), 1);
}

void Enemies::initTimer(int timer_, double value_){
    switch (timer_){
    case TIMER_MOVE:
        timerMove = al_create_timer(value_);
        break;
    }
}

void Enemies::startTimer(int timer_){
    switch (timer_){
    case TIMER_MOVE:
        al_start_timer(timerMove);
        break;
    }
}

void Enemies::stopTimer(int timer_){
    switch (timer_){
    case TIMER_MOVE:
        al_stop_timer(timerMove);
        break;
    }
}

ALLEGRO_TIMER* Enemies::showTimer(int timer_){
    switch(timer_){
    case TIMER_MOVE:
        return timerMove;
    }
}
