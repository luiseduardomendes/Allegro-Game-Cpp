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
    void loadBitmap(char fileName[], char* fileName2);
    void drawBitmap(int item_id);
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
    ALLEGRO_BITMAP *bitmapShuriken;
    ALLEGRO_BITMAP *bitmapThrKnife;

};
