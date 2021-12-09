#pragma once

class Player{
public:
    void loadBitmap(char [], int Dir_);
    void movePlayer(ALLEGRO_EVENT);
    void drawPlayer();
    void setPosition(int x_, int y_);
    void setDirection(int dir_);
    void switchMovement(ALLEGRO_EVENT);
    void stopMovement(ALLEGRO_EVENT);
    void keyDownInit();

private:
    int x, y;
    int directionView;
    int health;
    int level;
    int experience;
    int coins;
    int armorEquiped;
    int weaponEquiped;
    float moveSpeed;
    bool keyDown[4];
    ALLEGRO_BITMAP* bitmapUp;
    ALLEGRO_BITMAP* bitmapDown;
    ALLEGRO_BITMAP* bitmapLeft;
    ALLEGRO_BITMAP* bitmapRight;

};
