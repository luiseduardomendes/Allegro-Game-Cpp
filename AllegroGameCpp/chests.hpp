#pragma once

class Chests{
public:
    void setCoord(int x_, int y_);
    Coordinates returnCoord();
    HitBoxRange returnHitbox();
    void setItem(int item_);
    void setOpenStatus(bool status_);
    bool isOpen();
    int returnItem();
    void drawBitmap();
    void loadBitmapOpen(char* fileName);
    void loadBitmapClosed(char* fileName);
    void setHitbox();
private:
    int item;
    bool open;
    Coordinates coord;
    ALLEGRO_BITMAP* bitmapOpen;
    ALLEGRO_BITMAP* bitmapClosed;
    HitBoxRange hitbox;
};
