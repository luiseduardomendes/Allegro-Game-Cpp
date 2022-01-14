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
            switch (player->showItemInSlot(0).returnItemType())
            {
            case ITEM_TYPE_THROWING_WEAPON:
                player->equipWeapon(0);
                break;
            case ITEM_TYPE_ARMOR:
                player->equipArmor(0);
                break;
            case ITEM_TYPE_HELMET:
                player->equipHelmet(0);
                break;
            case ITEM_TYPE_LEGS:
                player->equipLegs(0);
                break;
            case ITEM_TYPE_BOOTS:
                player->equipBoots(0);
                break;
            }
            break;
        case ALLEGRO_KEY_2:
            switch (player->showItemInSlot(1).returnItemType())
            {
            case ITEM_TYPE_THROWING_WEAPON:
                player->equipWeapon(1);
                break;
            case ITEM_TYPE_ARMOR:
                player->equipArmor(1);
                break;
            case ITEM_TYPE_HELMET:
                player->equipHelmet(1);
                break;
            case ITEM_TYPE_LEGS:
                player->equipLegs(1);
                break;
            case ITEM_TYPE_BOOTS:
                player->equipBoots(1);
                break;
            }
            break;
        case ALLEGRO_KEY_3:
            switch (player->showItemInSlot(2).returnItemType())
            {
            case ITEM_TYPE_THROWING_WEAPON:
                player->equipWeapon(2);
                break;
            case ITEM_TYPE_ARMOR:
                player->equipArmor(2);
                break;
            case ITEM_TYPE_HELMET:
                player->equipHelmet(2);
                break;
            case ITEM_TYPE_LEGS:
                player->equipLegs(2);
                break;
            case ITEM_TYPE_BOOTS:
                player->equipBoots(2);
                break;
            }
            break;
        case ALLEGRO_KEY_4:
            switch (player->showItemInSlot(3).returnItemType())
            {
            case ITEM_TYPE_THROWING_WEAPON:
                player->equipWeapon(3);
                break;
            case ITEM_TYPE_ARMOR:
                player->equipArmor(3);
                break;
            case ITEM_TYPE_HELMET:
                player->equipHelmet(3);
                break;
            case ITEM_TYPE_LEGS:
                player->equipLegs(3);
                break;
            case ITEM_TYPE_BOOTS:
                player->equipBoots(3);
                break;
            }
            break;
        case ALLEGRO_KEY_5:
            switch (player->showItemInSlot(4).returnItemType())
            {
            case ITEM_TYPE_THROWING_WEAPON:
                player->equipWeapon(4);
                break;
            case ITEM_TYPE_ARMOR:
                player->equipArmor(4);
                break;
            case ITEM_TYPE_HELMET:
                player->equipHelmet(4);
                break;
            case ITEM_TYPE_LEGS:
                player->equipLegs(4);
                break;
            case ITEM_TYPE_BOOTS:
                player->equipBoots(4);
                break;
            }
            break;
        case ALLEGRO_KEY_6:
            switch (player->showItemInSlot(5).returnItemType())
            {
            case ITEM_TYPE_THROWING_WEAPON:
                player->equipWeapon(5);
                break;
            case ITEM_TYPE_ARMOR:
                player->equipArmor(5);
                break;
            case ITEM_TYPE_HELMET:
                player->equipHelmet(5);
                break;
            case ITEM_TYPE_LEGS:
                player->equipLegs(5);
                break;
            case ITEM_TYPE_BOOTS:
                player->equipBoots(5);
                break;
            }
            break;
        case ALLEGRO_KEY_7:
            switch (player->showItemInSlot(6).returnItemType())
            {
            case ITEM_TYPE_THROWING_WEAPON:
                player->equipWeapon(6);
                break;
            case ITEM_TYPE_ARMOR:
                player->equipArmor(6);
                break;
            case ITEM_TYPE_HELMET:
                player->equipHelmet(6);
                break;
            case ITEM_TYPE_LEGS:
                player->equipLegs(6);
                break;
            case ITEM_TYPE_BOOTS:
                player->equipBoots(6);
                break;
            }
            break;
        }
    }
}
