#pragma once

class Obstacles{
public:
    void setDamage(int value_);
    void setCoord(int x, int y);
    Coordinates showCoord();
    HitBoxRange showHitBox();
    void drawHitBox();
    void setHitBox();
    int showDamage();
    int showStructure();
private:
    HitBoxRange hitBox;
    int structure;
    int damage;
    Coordinates coord;
};
