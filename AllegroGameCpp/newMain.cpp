#include "mainHeader.hpp"

int main(){
    Player player;
    Keyboard keyboard;
    PauseMenu pauseMenu;
    Enemies enemies[NUM_ENEMIES];
    Screen scr;
    Draw draw;
    scr.height = 576;
    scr.width = 1024;

    pauseMenu.init();

    if(!al_init())
        cout << "Allegro nao pode ser inicializada" << endl;

    ALLEGRO_DISPLAY *display = NULL;
    if (!(display = al_create_display(scr.width, scr.height)))
        cout << "Display nao pode ser criado" << endl;
    
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();

    draw.createBitmap(BACKGROUND, scr);
    draw.createBitmap(GRASS, scr);

    player.loadBitmap("assets/narutoback.png", UP);
    player.loadBitmap("assets/naruto.png", DOWN);
    player.loadBitmap("assets/narutoleft.png", LEFT);
    player.loadBitmap("assets/narutoright.png", RIGHT);

    for(int i = 0; i < NUM_ENEMIES; i++){
        enemies[i].loadBitmap("assets/akatsukiback.png", UP);
        enemies[i].loadBitmap("assets/akatsuki.png", DOWN);
        enemies[i].loadBitmap("assets/akatsukileft.png", LEFT);
        enemies[i].loadBitmap("assets/akatsukiright.png", RIGHT);
    }

    player.projectile.loadBitmap("assets/shuriken.png");

    player.initPlayer();
    player.setSpeed(2);
    player.setPosition(45, 45);
    player.setDirection(DOWN);
    player.setHitBox();
    player.projectile.setThrowingStatus(false);

    player.projectile.initProjectile();

    for (int i = 0; i < NUM_ENEMIES; i ++){
        enemies[i].initEnemy();
        enemies[i].setPosition((scr.width / 4) + (rand() % (scr.width*3/4)), (scr.height / 4) + (rand() % (scr.height*3/4)));
        enemies[i].setDirection(DOWN);
        enemies[i].setHitBox();
        enemies[i].projectile.setThrowingStatus(false);
    }

    ALLEGRO_TIMER *timerFrame = al_create_timer(1.0/60.0);
    ALLEGRO_TIMER *timerProjectile = al_create_timer(1.0/60.0);
    ALLEGRO_TIMER *timerChangeDir = al_create_timer(2.50);
    al_start_timer(timerFrame);
    al_start_timer(timerProjectile);
    al_start_timer(timerChangeDir);

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    eventQueue = al_create_event_queue();

    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timerFrame));
    al_register_event_source(eventQueue, al_get_timer_event_source(timerProjectile));
    al_register_event_source(eventQueue, al_get_timer_event_source(timerChangeDir));

    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        keyboard.movePlayer(event, &player);
        player.movePlayer();
        keyboard.controllerKeys(event, &pauseMenu, &player);

        if (event.type == ALLEGRO_EVENT_TIMER){
            if (event.timer.source == timerFrame){
                al_set_target_bitmap(draw.getBitmap(BACKGROUND));
                al_clear_to_color(al_map_rgb(0,0,0));
                
                draw.drawNonStaticElements(player, enemies);

                al_set_target_bitmap(al_get_backbuffer(display));

                al_draw_bitmap(draw.getBitmap(BACKGROUND), 0, 0, 0);
                al_flip_display();
            }

            else if(event.timer.source == timerProjectile){
                if (player.projectile.isThrowing()){
                    if (player.projectile.projectileCoord().x > scr.width || player.projectile.projectileCoord().x < 0 || player.projectile.projectileCoord().y > scr.height || player.projectile.projectileCoord().y < 0)
                        player.projectile.setThrowingStatus(false);

                    else   
                        player.projectile.moveProj();
                }
                for (int i = 0; i < NUM_ENEMIES; i ++){
                    if (enemies[i].showAliveStatus()){
                        enemies[i].moveEnemy();
                    }
                }
                
            }
            else if(event.timer.source == timerChangeDir){
                for (int i = 0; i < NUM_ENEMIES; i ++){
                    if (enemies[i].showAliveStatus()){
                        enemies[i].setDirectionPlayer(player);
                    }
                }

            }
        }

    } while (!pauseMenu.isGameEnded());

    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}