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
    Damage damage;

    pauseMenu.init();
    player.countSlowInit();

    screen.width = 1024;
    screen.height = 576;

    ALLEGRO_DISPLAY *display;
    display = al_create_display(screen.width, screen.height);

    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
    ALLEGRO_TIMER *timerProjectile;

    timerProjectile = al_create_timer(1.0/60.0);
    al_start_timer(timerProjectile);

    player.initTimerSlow(1.0);

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timerProjectile));
    al_register_event_source(eventQueue, al_get_timer_event_source(player.showTimerSlow()));

    player.loadBitmap("assets/narutoback.png", UP);
    player.loadBitmap("assets/naruto.png", DOWN);
    player.loadBitmap("assets/narutoleft.png", LEFT);
    player.loadBitmap("assets/narutoright.png", RIGHT);
    projectile.loadBitmap("assets/shuriken.png");
    player.projectile.loadBitmap("assets/shuriken.png");

    player.initPlayer();

    projectile.initProjectile();
    player.projectile.initProjectile();

    player.setPosition(screen.width/2, screen.height/2);

    al_clear_to_color(colors.black());
    player.setDirection(DOWN);
    player.drawPlayer();
    al_flip_display();

    player.projectile.setThrowingStatus(false);
    projectile.setThrowingStatus(false);
    projectile.setProjDir(RIGHT, 1);

    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        keyboard.movePlayer(event, &player);
        player.movePlayer();
        keyboard.controllerKeys(event, &pauseMenu, &player);

        if (event.type == ALLEGRO_EVENT_TIMER){
            if (event.timer.source == timerProjectile){
                if(projectile.isThrowing())
                    projectile.moveProj();
                else{
                    projectile.setCoord(0, rand() % (screen.height/2));
                    projectile.setHitBox();
                    projectile.setThrowingStatus(true);
                }

                if(player.projectile.projectileCoord().x < screen.width && player.projectile.isThrowing())
                    player.projectile.moveProj();


                if(damage.projectileHitPlayer(&projectile, &player)){
                    player.startTimerSlow();
                }



            }
            if (event.timer.source == player.showTimerSlow()){
                player.stopTimerSlow();
                player.setSpeed(5);
                player.initTimerSlow(5.0);
            }

        }

        player.drawHealthBar();

        if(player.projectile.isThrowing()){
            player.projectile.drawHitbox();
            player.projectile.drawBitmap();
        }

        if (projectile.isThrowing()){
            projectile.drawHitbox();
            projectile.drawBitmap();
        }
        al_draw_circle(200,100,5,colors.white(), 5);

        player.drawPlayer();
        player.drawHitbox();
        player.drawTimerSlow();

        al_flip_display();
        al_clear_to_color(colors.black());

    } while (!pauseMenu.isGameEnded());

    return 0;
}

bool pointInsideBox(Coordinates point_, HitBoxRange box_){
    if (point_.x >= box_.inf.x && point_.x <= box_.sup.x && point_.y >= box_.inf.y && point_.y <= box_.sup.y)
        return true;
    else
        return false;
}

bool isProjectileIn(Player player, Projectile projectile){
    Coordinates aux1, aux2;

    aux1.x = projectile.showHitBox().inf.x;
    aux1.y = projectile.showHitBox().sup.y;

    aux2.x = projectile.showHitBox().sup.x;
    aux2.y = projectile.showHitBox().inf.y;

    if (pointInsideBox(aux1, player.showHitBox()) ||
        pointInsideBox(aux2, player.showHitBox()) ||
        pointInsideBox(projectile.showHitBox().inf, player.showHitBox()) ||
        pointInsideBox(projectile.showHitBox().sup, player.showHitBox()))
        return true;
    return false;
}
