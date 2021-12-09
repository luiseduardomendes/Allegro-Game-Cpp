#pragma once

class Player{
public:
    void loadBitmap(char [], int Dir_);
    void movePlayer();
    void drawPlayer();
    void setPosition(int x_, int y_);
    void setNewDirectionAfterMove();
    void setDirection(int dir_);
    void keyDownInit();
    void setKeyDown(int key_, bool value_);


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
    bool endOfGame;
    ALLEGRO_BITMAP* bitmapUp;
    ALLEGRO_BITMAP* bitmapDown;
    ALLEGRO_BITMAP* bitmapLeft;
    ALLEGRO_BITMAP* bitmapRight;

};
