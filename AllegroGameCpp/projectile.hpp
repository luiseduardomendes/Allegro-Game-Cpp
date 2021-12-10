#pragma once

class Projectile{
public:
    void moveProj();
    void setProjDir(int dir_, int value_);
    void setCoord(int x_, int y_);
    void setHitBox();
    Coordinates projectileCoord();
    HitBoxRange showHitBox();
    void loadBitmap(char fileName[]);
    void drawBitmap();
private:
    Coordinates coord;
    HitBoxRange hitBox;
    int damage;
    int speed;
    int moveDir[4];
    ALLEGRO_BITMAP *bitmap;

};
