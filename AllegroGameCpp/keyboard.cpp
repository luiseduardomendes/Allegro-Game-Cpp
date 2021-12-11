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

void Keyboard::controllerKeys(ALLEGRO_EVENT event, PauseMenu *pauseMenu, Player* player){
    if (event.type == ALLEGRO_EVENT_KEY_DOWN){
        switch (event.keyboard.keycode){
        case ALLEGRO_KEY_ESCAPE:
            pauseMenu->setEndOfGame(true);
            break;
        case ALLEGRO_KEY_F:
            player->throwProjectile();
            break;
        }
    }
}
