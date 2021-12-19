#include "mainHeader.hpp"

void Draw::loadBitmap(int bmpName, char* fileName){
    switch (bmpName)
    {
    case GRASSBLOCK1:
        grassBlock1 = al_load_bitmap(fileName);
        break;
    case GRASSBLOCK2:
        grassBlock1 = al_load_bitmap(fileName);
        break;
    case GRASSBLOCK3:
        grassBlock1 = al_load_bitmap(fileName);
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
    }

}

void Draw::createBitmapGrass(ALLEGRO_DISPLAY *display, Screen screen){
    int flagGrass;
    al_set_target_bitmap(grass);

    for(int i = 0; i < screen.width; i += 40){
        for (int j = 0; j < screen.height; j += 40){
            flagGrass = rand() % 20;
            if (flagGrass == 0)
                al_draw_bitmap(grassBlock2, i, j, 0);
            else if (flagGrass == 1)
                al_draw_bitmap(grassBlock3, i, j, 0);
            else
                al_draw_bitmap(grassBlock1, i, j, 0);

        }
    }
    al_set_target_bitmap(al_get_backbuffer(display));   
}

void Draw::drawNonStaticElements(Player player, Enemies enemies[]){    
    al_draw_bitmap(grass, 0, 0, 0);

    player.drawHitbox();
    player.drawPlayer();

    for (int i = 0; i < NUM_ENEMIES; i ++){
        if (enemies[i].showAliveStatus()){
            enemies[i].drawBitmap();
            enemies[i].drawHitbox();
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
        background = al_create_bitmap(scr.width, scr.height);
        break;
    case GRASS:
        grass = al_create_bitmap(scr.width, scr.height);
        break;
    }
    
}