#include "mainHeader.hpp"

using namespace std;

typedef struct{
    int width, height;
}Screen;

int main()
{
    al_init();

    Screen screen;
    Player player;
    Colors colors;

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

    player.setPosition(screen.width/2, screen.height/2);
    player.loadBitmap("naruto.png", UP);
    player.keyDownInit();

    al_clear_to_color(colors.black());
    al_flip_display();

    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        player.movePlayer(event);
        player.drawPlayer();

        al_flip_display();
        al_clear_to_color(colors.black());

    } while (1);

    return 0;
}
