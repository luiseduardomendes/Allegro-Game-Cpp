#pragma once

class Enemies{
public:
    void loadBitmap(char [], int Dir_);
    void initEnemy();
    void moveEnemy();
    void drawBitmap();
    void setPosition(int x_, int y_);
    void setDirectionPlayer(Player player);
    void setNewDirectionAfterMove();
    void setDirection(int dir_);
    void keyDownInit();
    void setKeyDown(int key_, bool value_);
    void setHitBox();
    void setSpeed(int);
    void throwProjectile(Player player);
    void drawHitbox();
    void drawHealthBar();
    int showHealth();
    void decrementHealth(int value_);
    Coordinates showCoord();
    HitBoxRange showHitBox();
    Projectile projectile;
    void setDirectionProj(Player);
    void loadAllBitmaps();

    void initTimer(int timer_, double value_);
    void startTimer(int timer_);
    void stopTimer(int timer_);
    ALLEGRO_TIMER* showTimer(int timer_);

    bool checkPlayerDistance(Player player);
    void setRangeView(int);
    int showRangeView();

    void setHitPlayer(bool value_);
    bool isHitPlayerOn();

    void setAliveStatus(bool value_);
    bool isAlive();
    bool* showKeyDown();
private:
    int idEnemy;
    double moveSpeed;
    double stdSpeed;
    int health;
    int fullHp;
    int directionView;
    int coins;
    bool alive;
    int armorEquiped;
    int weaponEquiped;
    bool keyDown[4];
    int rangeView;
    bool hitPlayer;

    int priorityDirection;

    ALLEGRO_TIMER *timerMove;
    ALLEGRO_TIMER *timerDamage;
    ALLEGRO_TIMER *timerThrowing;

    Coordinates coord;
    HitBoxRange hitBox;



    ALLEGRO_BITMAP *bitmapUp;
    ALLEGRO_BITMAP *bitmapDown;
    ALLEGRO_BITMAP *bitmapLeft;
    ALLEGRO_BITMAP *bitmapRight;
};
