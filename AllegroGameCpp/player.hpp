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
    void setSpeed(int);
    void throwProjectile();
    void drawHitbox();
    void drawHealthBar();
    int showHealth();
    void decrementHealth(int value_);
    Coordinates showCoord();
    HitBoxRange showHitBox();
    Projectile projectile;
    bool playerProjectileHit(HitBoxRange HB);

    void loadAllBitmaps();

    void setSlow(double value_);
    void resetSpeed();
    void initTimer(int timer_, double value_);
    void startTimer(int timer_);
    void stopTimer(int timer_);
    ALLEGRO_TIMER* showTimer(int timer_);

    void insertItem(int itemId);
    void deleteItem(int itemId);
    bool isItemInInventory(int itemId);
    void initInventory();
    int showMaxStorage();
    bool* showKeyDown();
    int showItemInSlot(int slot_);

private:
    Coordinates coord;
    HitBoxRange hitBox;
    int directionView;
    int health;
    int fullHp;
    double stdSpeed;
    int level;
    int experience;
    int coins;
    int armorEquiped;
    int weaponEquiped;
    float moveSpeed;
    bool slowned;
    bool keyDown[4];
    bool endOfGame;

    int maxStorage;
    int inventory[5];
    int numItems;

    ALLEGRO_TIMER *timerSlow;
    ALLEGRO_TIMER *timerIncreaseSpeed;

    ALLEGRO_BITMAP *bitmapUp;
    ALLEGRO_BITMAP *bitmapDown;
    ALLEGRO_BITMAP *bitmapLeft;
    ALLEGRO_BITMAP *bitmapRight;

};
