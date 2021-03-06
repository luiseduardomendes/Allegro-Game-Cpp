#pragma once

class Enemies{
public:
    void loadBitmap(char [], int Dir_);
    void initEnemy();
    void moveEnemy(Player player);
    void drawBitmap();
    void setPosition(int x_, int y_);
    void setNewDirectionAfterMove();
    void setDirection(int dir_);
    void keyDownInit();
    void setKeyDown(int key_, bool value_);
    void setHitBox();
    void setSpeed(int);
    void throwProjectile();
    void drawHitbox();
    void drawHealthBar();
    int showHealth();
    void decrementHealth(int value_);
    Coordinates showCoord();
    HitBoxRange showHitBox();
    Projectile projectile;

    void initTimer(int timer_, double value_);
    void startTimer(int timer_);
    void stopTimer(int timer_);
    ALLEGRO_TIMER* showTimer(int timer_);

    bool checkPlayerDistance(Player player);
    void setRangeView();
    int showRangeView();
private:
    int idEnemy;
    double moveSpeed;
    int health;
    int fullHp;
    int directionView;
    int coins;
    int armorEquiped;
    int weaponEquiped;
    bool keyDown[4];
    int rangeView;

    ALLEGRO_TIMER *timerMove;

    Coordinates coord;
    HitBoxRange hitBox;



    ALLEGRO_BITMAP *bitmapUp;
    ALLEGRO_BITMAP *bitmapDown;
    ALLEGRO_BITMAP *bitmapLeft;
    ALLEGRO_BITMAP *bitmapRight;
};
