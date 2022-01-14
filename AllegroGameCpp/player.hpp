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

    void insertItemInventory(Item item_);
    void deleteItemInventory(int itemId);
    bool isItemInInventory(int itemId);
    void initInventory();
    int showMaxStorage();
    bool* showKeyDown();
    Item showItemInSlot(int slot_);
    int returnSlotOfItem(int itemId);

    void equipHelmet(int slot_);
    void equipArmor(int slot_);
    void equipLegs(int slot_);
    void equipBoots(int slot_);
    void equipWeapon(int slot_);
    void equipShield(int slot_);

    Item returnHelmetEquiped();
    Item returnArmorEquiped();
    Item returnLegsEquiped();
    Item returnBootsEquiped();
    Item returnWeaponEquiped();
    Item returnShieldEquiped();

    void removeItemStack(int slot_);
    void initEquips();
    
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
    float moveSpeed;
    bool slowned;
    bool keyDown[4];
    bool endOfGame;

    int maxStorage;
    Item inventory[10];
    int numItems;

    Item helmetEquiped;
    Item armorEquiped;
    Item legsEquiped;
    Item bootsEquiped;
    Item weaponEquiped;
    Item shieldEquiped;

    ALLEGRO_TIMER *timerSlow;
    ALLEGRO_TIMER *timerIncreaseSpeed;

    ALLEGRO_BITMAP *bitmapUp;
    ALLEGRO_BITMAP *bitmapDown;
    ALLEGRO_BITMAP *bitmapLeft;
    ALLEGRO_BITMAP *bitmapRight;

};
