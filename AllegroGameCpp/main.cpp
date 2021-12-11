#include "mainHeader.hpp"
bool isProjectileIn(Player player, Projectile projectile);
bool pointInsideBox(Coordinates point_, HitBoxRange box_);
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
    al_init_primitives_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
    ALLEGRO_TIMER *timerProjectile;
    timerProjectile = al_create_timer(1.0/60.0);
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
    player.projectile.loadBitmap("assets/shuriken.png");

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
    projectile.setProjDir(LEFT, 10);

    player.projectile.setCoord(0,0);
    player.projectile.setHitBox();
    player.projectile.setThrowingStatus(0);


    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        keyboard.movePlayer(event, &player);
        player.movePlayer();
        keyboard.controllerKeys(event, &pauseMenu, &player);

        if (event.type == ALLEGRO_EVENT_TIMER){
            if (event.timer.source == timerProjectile){
                if(projectile.projectileCoord().x < screen.width)
                    projectile.moveProj();
                else
                    projectile.setCoord(0, screen.height/2);

                if(player.projectile.projectileCoord().x < screen.width && player.projectile.isThrowing())
                    player.projectile.moveProj();


            }
        }
        projectile.setHitBox();
        player.projectile.setHitBox();
        player.setHitBox();
        HitBoxRange buffHB = player.showHitBox(), buffHBproj = projectile.showHitBox();
        HitBoxRange buffPHB = player.projectile.showHitBox();
        al_draw_rectangle(buffHB.inf.x, buffHB.inf.y, buffHB.sup.x, buffHB.sup.y, colors.white(), 1);
        al_draw_rectangle(buffHBproj.inf.x, buffHBproj.inf.y, buffHBproj.sup.x, buffHBproj.sup.y, colors.white(), 1);
        al_draw_rectangle(buffPHB.inf.x, buffPHB.inf.y, buffPHB.sup.x, buffPHB.sup.y, colors.white(), 1);

        if (isProjectileIn(player, projectile))
            projectile.setCoord(0, rand() % (screen.height/2));

        player.drawPlayer();
        player.projectile.drawBitmap();
        projectile.drawBitmap();

        al_flip_display();
        al_clear_to_color(colors.black());

    } while (!pauseMenu.isGameEnded());

    return 0;
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
}

bool pointInsideBox(Coordinates point_, HitBoxRange box_){
    if (point_.x >= box_.inf.x && point_.x <= box_.sup.x && point_.y >= box_.inf.y && point_.y <= box_.sup.y)
        return true;
    else
        return false;
}
