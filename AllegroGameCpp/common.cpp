#include "mainHeader.hpp"

bool pointInsideBox(Coordinates point_, HitBoxRange box_){
    if (point_.x >= box_.inf.x && point_.x <= box_.sup.x && point_.y >= box_.inf.y && point_.y <= box_.sup.y)
        return true;
    else
        return false;
}

bool isProjectileIn(Player player, Projectile projectile){
    Coordinates aux1, aux2;

    aux1.x = projectile.showHitBox().inf.x;
    aux1.y = projectile.showHitBox().sup.y;

    aux2.x = projectile.showHitBox().sup.x;
    aux2.y = projectile.showHitBox().inf.y;

    if (pointInsideBox(aux1, player.showHitBox()) ||
        pointInsideBox(aux2, player.showHitBox()) ||
        pointInsideBox(projectile.showHitBox().inf, player.showHitBox()) ||
        pointInsideBox(projectile.showHitBox().sup, player.showHitBox()))
        return true;
    return false;
}

bool isProjectileIn(HitBoxRange HB, Projectile projectile){
    Coordinates aux1, aux2;

    aux1.x = projectile.showHitBox().inf.x;
    aux1.y = projectile.showHitBox().sup.y;

    aux2.x = projectile.showHitBox().sup.x;
    aux2.y = projectile.showHitBox().inf.y;

    if (pointInsideBox(aux1, HB) ||
        pointInsideBox(aux2, HB) ||
        pointInsideBox(projectile.showHitBox().inf, HB) ||
        pointInsideBox(projectile.showHitBox().sup, HB))
        return true;
    return false;
}

bool isHitboxIn(HitBoxRange HB1, HitBoxRange HB2){
    Coordinates aux1, aux2;

    aux1.x = HB2.inf.x;
    aux1.y = HB2.sup.y;

    aux2.x = HB2.sup.x;
    aux2.y = HB2.inf.y;

    if (pointInsideBox(aux1, HB1) || pointInsideBox(aux2, HB1) ||
            pointInsideBox(HB2.inf, HB1) || pointInsideBox(HB2.sup, HB1))
        return true;
    return false;
}



bool isEnemyIn(Player player, Enemies enemy){
    Coordinates aux1, aux2;

    aux1.x = enemy.showHitBox().inf.x;
    aux1.y = enemy.showHitBox().sup.y;

    aux2.x = enemy.showHitBox().sup.x;
    aux2.y = enemy.showHitBox().inf.y;

    if (pointInsideBox(aux1, player.showHitBox()) ||
        pointInsideBox(aux2, player.showHitBox()) ||
        pointInsideBox(enemy.showHitBox().inf, player.showHitBox()) ||
        pointInsideBox(enemy.showHitBox().sup, player.showHitBox()))
        return true;
    return false;
}



void createObstacles(Obstacles obstacles[], Screen screen) {
    for (int i = 0; i < 34; i ++){
        obstacles[i].setCoord(i * 40, 0);
        obstacles[i].setHitBox();
    }
    for (int i = 34; i < 68; i ++){
        obstacles[i].setCoord((i-34) * 40, screen.height - 40);
        obstacles[i].setHitBox();
    }
    for (int i = 68; i < 85; i ++){
        obstacles[i].setCoord(0, 40*(i-67));
        obstacles[i].setHitBox();
    }
    for (int i = 85; i < 102; i ++){
        obstacles[i].setCoord(screen.width-40, 40*(i-84));
        obstacles[i].setHitBox();
    }
    for (int i = 102; i < 112; i ++){
        obstacles[i].setCoord(screen.width-(40*5), 40*(i-101));
        obstacles[i].setHitBox();
    }
    for (int i = 112; i < 127; i ++){
        obstacles[i].setCoord(screen.width-(40*(i-111+5)), 40*10);
        obstacles[i].setHitBox();
    }
    for (int i = 127; i < 140; i ++){
        obstacles[i].setCoord(40*5, 40*(i-126));
        obstacles[i].setHitBox();
    }
    for (int i = 140; i < 155; i ++){
        obstacles[i].setCoord(40*(i-139+5), 40*5);
        obstacles[i].setHitBox();
    }
    for (int i = 155; i < 170; i ++){
        obstacles[i].setCoord(40*(i-154+10), screen.height -(40*6));
        obstacles[i].setHitBox();
    }
}

double distanceBetween(Coordinates a, Coordinates b){
    double distance;
    distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    return distance;
}