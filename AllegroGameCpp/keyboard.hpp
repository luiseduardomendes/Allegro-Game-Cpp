#pragma once

class Keyboard{
public:
    void switchMovement(ALLEGRO_EVENT event, Player *player);
    void stopMovement(ALLEGRO_EVENT event, Player *player);
    void movePlayer(ALLEGRO_EVENT event, Player *player);
    void controllerKeys(ALLEGRO_EVENT, PauseMenu *pauseMenu);
};
