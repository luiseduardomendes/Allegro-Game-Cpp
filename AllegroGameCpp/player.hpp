#pragma once

class Player{
public:
    void loadBitmap(char [], int Dir_);
    void initPlayer();
    void movePlayer();
    void drawPlayer();
    void setPosition(int x_, int y_);
    void setNewDirectionAfterMove();
    void setDirection(int dir_);
    void keyDownInit();
    void setKeyDown(int key_, bool value_);
    void setHitBox();
    void throwProjectile();
    void drawHitbox();
    void drawHealthBar();
    int showHealth();
    void decrementHealth(int value_);
    Coordinates showCoord();
    HitBoxRange showHitBox();
    Projectile projectile;

private:
    Coordinates coord;
    HitBoxRange hitBox;
    int directionView;
    int health;
    int fullHp;
    int level;
    int experience;
    int coins;
    int armorEquiped;
    int weaponEquiped;
    float moveSpeed;
    bool keyDown[4];
    bool endOfGame;

    ALLEGRO_BITMAP *bitmapUp;
    ALLEGRO_BITMAP *bitmapDown;
    ALLEGRO_BITMAP *bitmapLeft;
    ALLEGRO_BITMAP *bitmapRight;

};
