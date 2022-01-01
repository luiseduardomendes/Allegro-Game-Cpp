#pragma once

class Projectile{
public:
    void initProjectile();
    void moveProj();
    void setProjDir(int dir_, float value_);
    void setCoord(int x_, int y_);
    void setHitBox();
    Coordinates projectileCoord();
    HitBoxRange showHitBox();
    void loadBitmap(char fileName[]);
    void drawBitmap();
    void setThrowingStatus(int value_);
    void setSpeed(int value_);
    bool isThrowing();
    void drawHitbox();
    int showDamage();
    void setSpeed();
private:
    Coordinates coord;
    HitBoxRange hitBox;
    int damage;
    int speed;
    float moveDir[4];
    bool throwing;
    ALLEGRO_BITMAP *bitmap;

};
