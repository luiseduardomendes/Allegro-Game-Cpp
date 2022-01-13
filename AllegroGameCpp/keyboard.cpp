#include "mainHeader.hpp"

void Keyboard::movePlayer(ALLEGRO_EVENT event, Player *player){

    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        switchMovement(event, player);

    else if(event.type == ALLEGRO_EVENT_KEY_UP)
        stopMovement(event, player);


}

void Keyboard::switchMovement(ALLEGRO_EVENT event, Player *player){

    switch (event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
            player->setKeyDown(UP, true);
            break;
        case ALLEGRO_KEY_DOWN:
            player->setKeyDown(DOWN, true);
            break;
        case ALLEGRO_KEY_LEFT:
            player->setKeyDown(LEFT, true);
            break;
        case ALLEGRO_KEY_RIGHT:
            player->setKeyDown(RIGHT, true);
            break;
    }

}

void Keyboard::stopMovement(ALLEGRO_EVENT event, Player *player){
    switch (event.keyboard.keycode){
        case ALLEGRO_KEY_UP:
            player->setKeyDown(UP, false);
            break;
        case ALLEGRO_KEY_DOWN:
            player->setKeyDown(DOWN, false);
            break;
        case ALLEGRO_KEY_LEFT:
            player->setKeyDown(LEFT, false);
            break;
        case ALLEGRO_KEY_RIGHT:
            player->setKeyDown(RIGHT, false);
            break;
    }
}

void Keyboard::controllerKeys(ALLEGRO_EVENT event, PauseMenu *pauseMenu, Player* player, Screen* scr, Chests chests[]){
    if (event.type == ALLEGRO_EVENT_KEY_DOWN){
        switch (event.keyboard.keycode){
        case ALLEGRO_KEY_ESCAPE:
            pauseMenu->setEndOfGame(true);
            break;
        case ALLEGRO_KEY_F:
            player->throwProjectile();
            break;
        case ALLEGRO_KEY_V: 
            player->setSpeed(5);
            player->startTimer(TIMER_INCREASE_SPEED);
            break;
        case ALLEGRO_KEY_MINUS:
            scr->zoom*=0.9;
            break;
        case ALLEGRO_KEY_EQUALS:
            scr->zoom*=1.1;
            break;
        case ALLEGRO_KEY_E:
            checkChests(chests, player);
            break;
        case ALLEGRO_KEY_1:
            if (player->showItemInSlot(0).returnItemType() == ITEM_TYPE_THROWING_WEAPON)
                player->setWeaponEquiped(0);
            else if (player->showItemInSlot(0).returnItemType() == ITEM_TYPE_ARMOR)
                player->setArmorEquiped(0);
            break;
        case ALLEGRO_KEY_2:
            if (player->showItemInSlot(1).returnItemType() == ITEM_TYPE_THROWING_WEAPON)
                player->setWeaponEquiped(1);
            else if (player->showItemInSlot(1).returnItemType() == ITEM_TYPE_ARMOR)
                player->setArmorEquiped(1);
            break;
        case ALLEGRO_KEY_3:
            if (player->showItemInSlot(2).returnItemType() == ITEM_TYPE_THROWING_WEAPON)
                player->setWeaponEquiped(2);
            else if (player->showItemInSlot(2).returnItemType() == ITEM_TYPE_ARMOR)
                player->setArmorEquiped(2);
            break;
        case ALLEGRO_KEY_4:
            if (player->showItemInSlot(3).returnItemType() == ITEM_TYPE_THROWING_WEAPON)
                player->setWeaponEquiped(3);
            else if (player->showItemInSlot(3).returnItemType() == ITEM_TYPE_ARMOR)
                player->setArmorEquiped(3);
            break;
        case ALLEGRO_KEY_5:
            if (player->showItemInSlot(4).returnItemType() == ITEM_TYPE_THROWING_WEAPON)
                player->setWeaponEquiped(4);
            else if (player->showItemInSlot(4).returnItemType() == ITEM_TYPE_ARMOR)
                player->setArmorEquiped(4);
            break;
        }
    }
}
