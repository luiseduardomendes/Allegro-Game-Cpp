#include "mainHeader.hpp"
void Draw::initFonts(){
    font_pixel24 = al_load_font("fonts/pixelfont.ttf", 24, 0);
}

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
        return items[ITEM_ID_THROWING_KNIFE];
    case SHURIKEN_BMP:
        return items[ITEM_ID_SHURIKEN];
    case ARMOR_BMP:
        return items[ITEM_ID_ARMOR];
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

void Draw::drawGrass(){
    al_draw_bitmap(grass, 0, 0, 0);
}

void Draw::drawNonStaticElements(Player player, Enemies enemies[]){    

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
        player.projectile.drawBitmap(player.returnWeaponEquiped().returnItemId());
    }
    for (int i = 0; i < NUM_ENEMIES; i ++){
        if (enemies[i].projectile.isThrowing()){
            enemies[i].projectile.drawHitbox();
            enemies[i].projectile.drawBitmap(ITEM_ID_SHURIKEN);
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
    equipments = al_create_bitmap(3*40, 4*40);
    

}

void Draw::drawInventory(Player player, ALLEGRO_DISPLAY* display){
    Colors colors;
    al_set_target_bitmap(inventory);
    al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
    for (int i = 0; i < player.showMaxStorage(); i ++){
        al_draw_bitmap(inventorySlot, i*40, 0, 0);
        if (player.showItemInSlot(i).returnItemId() != ITEM_ID_EMPTY){
            al_draw_bitmap(items[player.showItemInSlot(i).returnItemId()], i*40, 0, 0);
            if (player.showItemInSlot(i).returnStack() > 1)
                al_draw_textf(font_pixel24, al_map_rgb(255,255,255), (i*40)+20, 20, 0, "%d", player.showItemInSlot(i).returnStack());
        }
    }

    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(inventory, 500, 650, 0);
}

void Draw::loadAllBitmaps(Screen scr){
    createBitmap(BACKGROUND, scr);
    createBitmap(GRASS, scr);
    loadBitmap(GRASSBLOCK1, "assets/grass1.png");
    loadBitmap(GRASSBLOCK2, "assets/grass2.png");
    loadBitmap(GRASSBLOCK3, "assets/grass3.png");

    inventorySlot = al_load_bitmap("assets/itemframe.png");
    items[ITEM_ID_THROWING_KNIFE] = al_load_bitmap("assets/throwingknife.png");
    items[ITEM_ID_SHURIKEN] = al_load_bitmap("assets/shuriken.png");    
    items[ITEM_ID_ARMOR] = al_load_bitmap("assets/armor.png");
    items[ITEM_ID_HEAVYARMOR] = al_load_bitmap("assets/armor.png");
    items[ITEM_ID_LIGHTARMOR] = al_load_bitmap("assets/armor.png");
    items[ITEM_ID_HELMET] = al_load_bitmap("assets/helmet.png");
    items[ITEM_ID_LEGS] = al_load_bitmap("assets/legs.png");
    items[ITEM_ID_BOOTS] = al_load_bitmap("assets/boots.png");

}

void Draw::drawStaticElements(Chests chests[]){
    for(int i = 0; i < NUM_CHESTS; i ++)
        chests[i].drawBitmap();
    
}

void Draw::drawEquipedItems(Player player, ALLEGRO_DISPLAY* display){
    al_set_target_bitmap(equipments);
    
    al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));

    al_draw_bitmap(inventorySlot, 40, 0, 0);
    al_draw_bitmap(inventorySlot, 0, 40, 0);
    al_draw_bitmap(inventorySlot, 40, 40, 0);
    al_draw_bitmap(inventorySlot, 80, 40, 0);
    al_draw_bitmap(inventorySlot, 40, 80, 0);
    al_draw_bitmap(inventorySlot, 40, 120, 0);
    
    switch (player.returnWeaponEquiped().returnItemId()){
    case ITEM_ID_SHURIKEN:
        al_draw_bitmap(items[ITEM_ID_SHURIKEN], 0, 40, 0);
        break;
    case ITEM_ID_THROWING_KNIFE:
        al_draw_bitmap(items[ITEM_ID_THROWING_KNIFE], 0, 40, 0);
        break;
    }
    switch (player.returnArmorEquiped().returnItemId()){
    case ITEM_ID_ARMOR:
        al_draw_bitmap(items[ITEM_ID_ARMOR], 40, 40, 0);
        break;
    case ITEM_ID_LIGHTARMOR:
        al_draw_bitmap(items[ITEM_ID_ARMOR], 40, 40, 0);
        break;
    case ITEM_ID_HEAVYARMOR:
        al_draw_bitmap(items[ITEM_ID_ARMOR], 40, 40, 0);
        break;
    }
    switch (player.returnHelmetEquiped().returnItemId()){
    case ITEM_ID_HELMET:
        al_draw_bitmap(items[ITEM_ID_HELMET], 40, 0, 0);
        break;
    }
    switch (player.returnLegsEquiped().returnItemId()){
    case ITEM_ID_LEGS:
        al_draw_bitmap(items[ITEM_ID_LEGS], 40, 80, 0);
        break;
    }
    switch (player.returnBootsEquiped().returnItemId()){
    case ITEM_ID_BOOTS:
        al_draw_bitmap(items[ITEM_ID_BOOTS], 40, 120, 0);
        break;
    }
    if (player.returnWeaponEquiped().returnStack() > 1)
        al_draw_textf(font_pixel24, al_map_rgb(255,255,255), 20, 60, 0, "%d", player.returnWeaponEquiped().returnStack());
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(equipments, 1200, 120, 0);
}