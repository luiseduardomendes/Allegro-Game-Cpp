#include "mainHeader.hpp"

int main()
{
    al_init();

    Screen screen;
    Player player;
    Keyboard keyboard;
    PauseMenu pauseMenu;
    Colors colors;

    pauseMenu.init();

    screen.width = 1024;
    screen.height = 576;

    ALLEGRO_DISPLAY *display;
    display = al_create_display(screen.width, screen.height);

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));

    player.loadBitmap("assets/narutoback.png", UP);
    player.loadBitmap("assets/naruto.png", DOWN);
    player.loadBitmap("assets/narutoleft.png", LEFT);
    player.loadBitmap("assets/narutoright.png", RIGHT);

    player.keyDownInit();

    player.setPosition(screen.width/2, screen.height/2);

    al_clear_to_color(colors.black());
    player.setDirection(DOWN);
    player.drawPlayer();
    al_flip_display();

    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        keyboard.movePlayer(event, &player);
        player.movePlayer();
        keyboard.controllerKeys(event, &pauseMenu);

        player.drawPlayer();

        al_flip_display();
        al_clear_to_color(colors.black());

    } while (!pauseMenu.isGameEnded());

    return 0;
}
