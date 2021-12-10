#include "mainHeader.hpp"


int main()
{
    al_init();

    Screen screen;
    Player player;
    Keyboard keyboard;
    PauseMenu pauseMenu;
    Colors colors;
    Projectile projectile;

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
    ALLEGRO_TIMER *timerProjectile;
    timerProjectile = al_create_timer(1.0/10.0);
    al_start_timer(timerProjectile);

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timerProjectile));

    player.loadBitmap("assets/narutoback.png", UP);
    player.loadBitmap("assets/naruto.png", DOWN);
    player.loadBitmap("assets/narutoleft.png", LEFT);
    player.loadBitmap("assets/narutoright.png", RIGHT);
    projectile.loadBitmap("assets/shuriken.png");

    player.keyDownInit();

    player.setPosition(screen.width/2, screen.height/2);

    al_clear_to_color(colors.black());
    player.setDirection(DOWN);
    player.drawPlayer();
    al_flip_display();

    projectile.setCoord(0, rand() % screen.height);
    projectile.setProjDir(UP, 0);
    projectile.setProjDir(DOWN, 0);
    projectile.setProjDir(RIGHT, 0);
    projectile.setProjDir(LEFT, 50);

    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        keyboard.movePlayer(event, &player);
        player.movePlayer();
        keyboard.controllerKeys(event, &pauseMenu);

        if (event.type == ALLEGRO_EVENT_TIMER){
            if (event.timer.source == timerProjectile){
                if(projectile.projectileCoord().x < screen.width)
                    projectile.moveProj();
                else
                    projectile.setCoord(0, screen.height/2);
                projectile.setHitBox();
            }
        }

        player.drawPlayer();
        projectile.drawBitmap();

        al_flip_display();
        al_clear_to_color(colors.black());

    } while (!pauseMenu.isGameEnded());

    return 0;
}
