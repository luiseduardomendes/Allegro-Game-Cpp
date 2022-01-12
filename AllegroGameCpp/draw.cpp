#include "mainHeader.hpp"

void Draw::loadBitmap(int bmpName, char* fileName){
    switch (bmpName)
    {
    case GRASSBLOCK1:
        grassBlock1 = al_load_bitmap(fileName);
        break;
    case GRASSBLOCK2:
        grassBlock2 = al_load_bitmap(fileName);
        break;
    case GRASSBLOCK3:
        grassBlock3 = al_load_bitmap(fileName);
        break;
    case GRASS:
        grass = al_load_bitmap(fileName);
        break;
    case BACKGROUND:
        background = al_load_bitmap(fileName);
        break;
    case INV_SLOT_BMP:
        inventorySlot = al_load_bitmap(fileName);
        break;
    case THR_KNIFE_BMP:
        items[THROWING_KNIFE] = al_load_bitmap(fileName);
        break;
    case SHURIKEN_BMP:
        items[SHURIKEN] = al_load_bitmap(fileName);
        break;
    case ARMOR_BMP:
        items[ARMOR] = al_load_bitmap(fileName);
        break;
    }
}

ALLEGRO_BITMAP* Draw::getBitmap(int bmpName){
    switch (bmpName)
    {
    case GRASSBLOCK1:
        return grassBlock1;
    case GRASSBLOCK2:
        return grassBlock2;
    case GRASSBLOCK3:
        return grassBlock3;
    case GRASS:
        return grass;
    case BACKGROUND:
        return background;
    case INV_SLOT_BMP:
        return inventorySlot;
    case THR_KNIFE_BMP:
        return items[THROWING_KNIFE];
    case SHURIKEN_BMP:
        return items[SHURIKEN];
    case ARMOR_BMP:
        return items[ARMOR];
    }

}

void Draw::createBitmapGrass(ALLEGRO_DISPLAY *display, Screen screen){
    int flagGrass;
    al_set_target_bitmap(grass);

    for(int i = 0; i < screen.bgWidth; i += 40){
        for (int j = 0; j < screen.bgHeight; j += 40){
            flagGrass = rand() % 20;
            if (flagGrass == 0)
                al_draw_bitmap(grassBlock2, i, j, 0);
            else if (flagGrass == 1)
                al_draw_bitmap(grassBlock3, i, j, 0);
            else
                al_draw_bitmap(grassBlock1, i, j, 0);

        }
    }
    //al_set_target_bitmap(al_get_backbuffer(display));   
}

void Draw::drawNonStaticElements(Player player, Enemies enemies[]){    
    al_draw_bitmap(grass, 0, 0, 0);

    player.drawHitbox();
    player.drawPlayer();

    for (int i = 0; i < NUM_ENEMIES; i ++){
        if (enemies[i].isAlive()){
            enemies[i].drawBitmap();
            enemies[i].drawHitbox();
            enemies[i].drawHealthBar();
        }
    }

    if (player.projectile.isThrowing()){
        player.projectile.drawHitbox();
        player.projectile.drawBitmap();
    }
    for (int i = 0; i < NUM_ENEMIES; i ++){
        if (enemies[i].projectile.isThrowing()){
            enemies[i].projectile.drawHitbox();
            enemies[i].projectile.drawBitmap();
        }
    }
}

void Draw::createBitmap(int bmpName, Screen scr){
    switch (bmpName)
    {
    case BACKGROUND:
        background = al_create_bitmap(scr.bgWidth, scr.bgHeight);
        break;
    case GRASS:
        grass = al_create_bitmap(scr.bgWidth, scr.bgHeight);
        break;
    }
    
}

void Draw::initInventory(Player player){
    inventory = al_create_bitmap(player.showMaxStorage() * 40, 40);
}

void Draw::drawInventory(Player player, ALLEGRO_DISPLAY* display){
    al_set_target_bitmap(inventory);
    for (int i = 0; i < player.showMaxStorage(); i ++){
        al_draw_bitmap(inventorySlot, i*40, 0, 0);
    }
    for (int i = 0; i < player.showMaxStorage(); i ++){
        al_draw_bitmap(items[player.showItemInSlot(i)], i*40, 0, 0);
    }
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(inventory, 0,0,0);
}

void Draw::loadAllBitmaps(Screen scr){
    createBitmap(BACKGROUND, scr);
    createBitmap(GRASS, scr);
    loadBitmap(GRASSBLOCK1, "assets/grass1.png");
    loadBitmap(GRASSBLOCK2, "assets/grass2.png");
    loadBitmap(GRASSBLOCK3, "assets/grass3.png");
    loadBitmap(SHURIKEN_BMP, "assets/shuriken.png");
    loadBitmap(ARMOR_BMP, "assets/heavyarmor.png");
    loadBitmap(THR_KNIFE_BMP, "assets/throwingknife.png");
    loadBitmap(INV_SLOT_BMP, "assets/itemframe.png");
}