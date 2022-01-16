#pragma once 

class Draw{
public:
    void createBitmapGrass(ALLEGRO_DISPLAY *display, Screen screen);
    void loadBitmap(int bmpName, char* fileName);
    ALLEGRO_BITMAP* getBitmap(int bmpName);
    void drawNonStaticElements(Player player, Enemies enemies[]);
    void drawGrass();
    void createBitmap(int bmpName, Screen scr);
    void drawInventory(Player player, ALLEGRO_DISPLAY* display);
    void initInventory(Player player);
    void loadAllBitmaps(Screen scr);
    void drawStaticElements(Chests chests[]);
    void drawEquipedItems(Player player, ALLEGRO_DISPLAY* display);
    void initFonts();
    void drawExperienceBar(Player player, ALLEGRO_DISPLAY *display);
private:
    ALLEGRO_FONT* font_pixel24;
    ALLEGRO_BITMAP *grass;
    ALLEGRO_BITMAP *grassBlock1;
    ALLEGRO_BITMAP *grassBlock2;
    ALLEGRO_BITMAP *grassBlock3;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *inventorySlot;
    ALLEGRO_BITMAP *inventory;
    ALLEGRO_BITMAP *equipments;
    ALLEGRO_BITMAP *shurikenBitmap;
    ALLEGRO_BITMAP *thrKnifeBitmap;
    ALLEGRO_BITMAP *lightArmorBitmap;
    ALLEGRO_BITMAP *armorBitmap;
    ALLEGRO_BITMAP *heavyArmorBitmap;
    ALLEGRO_BITMAP *experienceBar;
    ALLEGRO_BITMAP *playerExperienceBar;
    ALLEGRO_BITMAP *coinsBitmap;

    ALLEGRO_BITMAP *items[15];
};