#pragma once 

class Draw{
public:
    void createBitmapGrass(ALLEGRO_DISPLAY *display, Screen screen);
    void loadBitmap(int bmpName, char* fileName);
    ALLEGRO_BITMAP* getBitmap(int bmpName);
    void drawNonStaticElements(Player player, Enemies enemies[]);
    void createBitmap(int bmpName, Screen scr);
private:
    ALLEGRO_BITMAP *grass;
    ALLEGRO_BITMAP *grassBlock1;
    ALLEGRO_BITMAP *grassBlock2;
    ALLEGRO_BITMAP *grassBlock3;
    ALLEGRO_BITMAP *background;
};