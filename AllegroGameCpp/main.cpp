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
    Enemies enemy[5];

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
    ALLEGRO_TIMER *timerProjectile, *timerMovePlayer;

    timerProjectile = al_create_timer(1.0/60.0);

    al_start_timer(timerProjectile);


    player.initTimer(TIMER_SLOW, 1.0);
    for (int i = 0; i < 5; i ++){
        enemy[i].initTimer(TIMER_MOVE, 1.0/4);
        enemy[i].startTimer(TIMER_MOVE);
        enemy[i].initTimer(TIMER_DAMAGE, 3.0);
    }

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timerProjectile));
    al_register_event_source(eventQueue, al_get_timer_event_source(player.showTimer(TIMER_SLOW)));
    for (int i = 0; i < 5; i ++){
        al_register_event_source(eventQueue, al_get_timer_event_source(enemy[i].showTimer(TIMER_MOVE)));
        al_register_event_source(eventQueue, al_get_timer_event_source(enemy[i].showTimer(TIMER_DAMAGE)));
    }
    player.loadBitmap("assets/narutoback.png", UP);
    player.loadBitmap("assets/naruto.png", DOWN);
    player.loadBitmap("assets/narutoleft.png", LEFT);
    player.loadBitmap("assets/narutoright.png", RIGHT);
    for (int i = 0; i < 5; i ++){
        enemy[i].loadBitmap("assets/akatsukiback.png", UP);
        enemy[i].loadBitmap("assets/akatsuki.png", DOWN);
        enemy[i].loadBitmap("assets/akatsukileft.png", LEFT);
        enemy[i].loadBitmap("assets/akatsukiright.png", RIGHT);
    }

    projectile.loadBitmap("assets/shuriken.png");
    player.projectile.loadBitmap("assets/shuriken.png");

    player.initPlayer();
    for (int i = 0; i < 5; i ++){

        enemy[i].initEnemy();
        enemy[i].setDirection(DOWN);
    }

    projectile.initProjectile();
    player.projectile.initProjectile();

    player.setPosition(screen.width/2, screen.height/2);
    enemy[0].setPosition(screen.width/3, screen.height/2);
    enemy[1].setPosition(screen.width/3, screen.height/4);
    enemy[2].setPosition(screen.width/3, screen.height*3/4);
    enemy[3].setPosition(screen.width*2/3, screen.height*3/4);
    enemy[4].setPosition(screen.width*2/3, screen.height/2);




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
        for (int i = 0; i < 5; i ++)
            enemy[i].moveEnemy();
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
                    player.setSlow(0.5);
                    player.startTimer(TIMER_SLOW);
                }



            }
            if (event.timer.source == player.showTimer(TIMER_SLOW)){
                player.resetSpeed();
                player.stopTimer(TIMER_SLOW);
            }
            for (int i = 0; i < 5; i ++){
                if (event.timer.source == enemy[i].showTimer(TIMER_MOVE)){
                    enemy[i].setDirectionPlayer(player);

                }
                if (event.timer.source == enemy[i].showTimer(TIMER_DAMAGE)){
                    enemy[i].setHitPlayer(false);
                }
            }


        }
        for (int i = 0; i < 5; i ++){
            if(!enemy[i].isHitPlayerOn() && damage.enemyHitPlayer(&enemy[i], &player)){
                enemy[i].startTimer(TIMER_DAMAGE);
                enemy[i].setHitPlayer(true);
            }
            if (player.playerProjectileHit(enemy[i].showHitBox())){
                player.projectile.setThrowingStatus(false);
                enemy[i].decrementHealth(200);

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

        if(player.showHealth() == 0)
            pauseMenu.setEndOfGame(true);

        player.drawPlayer();
        player.drawHitbox();
        for (int i = 0; i < 5; i ++){
            if (enemy[i].showHealth() > 0){
                enemy[i].drawBitmap();
                enemy[i].drawHitbox();
            }
        }

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

bool isProjectileInEnemy(HitBoxRange HB, Projectile projectile){
    Coordinates aux1, aux2;

    aux1.x = projectile.showHitBox().inf.x;
    aux1.y = projectile.showHitBox().sup.y;

    aux2.x = projectile.showHitBox().sup.x;
    aux2.y = projectile.showHitBox().inf.y;

    if (pointInsideBox(aux1, HB) ||
        pointInsideBox(aux2, HB) ||
        pointInsideBox(projectile.showHitBox().inf, HB) ||
        pointInsideBox(projectile.showHitBox().sup, HB))
        return true;
    return false;
}



bool isEnemyIn(Player player, Enemies enemy){
    Coordinates aux1, aux2;

    aux1.x = enemy.showHitBox().inf.x;
    aux1.y = enemy.showHitBox().sup.y;

    aux2.x = enemy.showHitBox().sup.x;
    aux2.y = enemy.showHitBox().inf.y;

    if (pointInsideBox(aux1, player.showHitBox()) ||
        pointInsideBox(aux2, player.showHitBox()) ||
        pointInsideBox(enemy.showHitBox().inf, player.showHitBox()) ||
        pointInsideBox(enemy.showHitBox().sup, player.showHitBox()))
        return true;
    return false;
}

