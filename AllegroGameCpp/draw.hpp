#pragma once 

class Draw{
public:
    void createBitmapGrass(ALLEGRO_DISPLAY *display, Screen screen);
    void loadBitmap(int bmpName, char* fileName);
    ALLEGRO_BITMAP* getBitmap(int bmpName);
    void drawNonStaticElements(Player player, Enemies enemies[]);
    void createBitmap(int bmpName, Screen scr);
    void drawInventory(Player player, ALLEGRO_DISPLAY* display);
    void initInventory(Player player);
private:
    ALLEGRO_BITMAP *grass;
    ALLEGRO_BITMAP *grassBlock1;
    ALLEGRO_BITMAP *grassBlock2;
    ALLEGRO_BITMAP *grassBlock3;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *inventorySlot;
    ALLEGRO_BITMAP *throwingKnife;
    ALLEGRO_BITMAP *shuriken;
    ALLEGRO_BITMAP *armor;
    ALLEGRO_BITMAP *inventory;

    ALLEGRO_BITMAP *items[];
};