#include "mainHeader.hpp"


// compilation
/* g++ newMain.cpp Colors.cpp common.cpp Damage.cpp enemies.cpp keyboard.cpp obstacles.cpp pauseMenu.cpp player.cpp projectile.cpp draw.cpp $(pkg-config --libs allegro-5 allegro_font-5  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_dialog-5 --cflags) -lm -o AllegroGameTest1 */

int main(){
    Player player;
    Keyboard keyboard;
    PauseMenu pauseMenu;
    Enemies enemies[NUM_ENEMIES];
    Screen scr;
    Draw draw;
    DmgAndColision damage;
    Obstacles obs[NUM_WALLS];
    Chests chests[NUM_CHESTS];
    scr.width = 1360;
    scr.height = 760;
    scr.bgWidth = scr.width*2;
    scr.bgHeight = scr.height*2;
    scr.zoom = 1;

    bool nextPosValid;

    srand(time(NULL));

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
    draw.loadBitmap(GRASSBLOCK1, "assets/grass1.png");
    draw.loadBitmap(GRASSBLOCK2, "assets/grass2.png");
    draw.loadBitmap(GRASSBLOCK3, "assets/grass3.png");
    

    player.loadBitmap("assets/narutoback.png", UP);
    player.loadBitmap("assets/naruto.png", DOWN);
    player.loadBitmap("assets/narutoleft.png", LEFT);
    player.loadBitmap("assets/narutoright.png", RIGHT);
    player.initInventory();

    for(int i = 0; i < NUM_ENEMIES; i++){
        enemies[i].loadBitmap("assets/akatsukiback.png", UP);
        enemies[i].loadBitmap("assets/akatsuki.png", DOWN);
        enemies[i].loadBitmap("assets/akatsukileft.png", LEFT);
        enemies[i].loadBitmap("assets/akatsukiright.png", RIGHT);
        enemies[i].projectile.loadBitmap("assets/shuriken.png");
    }

    for(int i = 0; i < NUM_CHESTS; i++){
        chests[i].loadBitmapOpen("assets/chestOpen.png");
        chests[i].loadBitmapClosed("assets/chestClosed.png");
        chests[i].setCoord((scr.width / 4) + (rand() % (scr.width*3/4)), (scr.height / 4) + (rand() % (scr.height*3/4)));
        chests[i].setOpenStatus(false);
        chests[i].setItem(rand() % 5);
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
        do{
            enemies[i].initEnemy();
            enemies[i].setPosition((scr.width / 4) + (rand() % (scr.width*3/4)), (scr.height / 4) + (rand() % (scr.height*3/4)));
            enemies[i].setDirection(DOWN);
            enemies[i].setHitBox();
            nextPosValid = true;
            /*for (int j = 0; j < NUM_WALLS; j ++){
                if(isHitboxIn(obs[j].showHitBox(), enemies[i].showHitBox()))
                    nextPosValid = false;
            }*/
        } while(!nextPosValid);
        enemies[i].projectile.initProjectile();
        enemies[i].projectile.setThrowingStatus(false);
    }

    createObstacles(obs, scr);
    for (int i = 0; i < NUM_WALLS; i ++)
        obs[i].loadBitmapWall("assets/wall.png");

    draw.createBitmapGrass(display, scr);
    for (int i = 0; i < NUM_WALLS; i ++)
        obs[i].drawBitmapWall();
    
    al_set_target_bitmap(al_get_backbuffer(display));
    
    for (int i = 0; i < NUM_ENEMIES;i ++){
        enemies[i].initTimer(TIMER_THROWING, 2.5);
        enemies[i].startTimer(TIMER_THROWING);
    }

    ALLEGRO_TIMER *timerFrame = al_create_timer(1.0/60.0);
    ALLEGRO_TIMER *timerProjectile = al_create_timer(1.0/60.0);
    ALLEGRO_TIMER *timerChangeDir = al_create_timer(1.00);
    al_start_timer(timerFrame);
    al_start_timer(timerProjectile);
    al_start_timer(timerChangeDir);

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    eventQueue = al_create_event_queue();

    player.initTimer(TIMER_INCREASE_SPEED, 1.00);

    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timerFrame));
    al_register_event_source(eventQueue, al_get_timer_event_source(timerProjectile));
    al_register_event_source(eventQueue, al_get_timer_event_source(timerChangeDir));
    for (int i = 0; i < NUM_ENEMIES; i ++)
        al_register_event_source(eventQueue, al_get_timer_event_source(enemies[i].showTimer(TIMER_THROWING)));
    al_register_event_source(eventQueue, al_get_timer_event_source(player.showTimer(TIMER_INCREASE_SPEED)));

    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        keyboard.movePlayer(event, &player);
        
        nextPosValid = true;
        for (int i = 0; i < NUM_WALLS; i ++)
            if (abs(obs[i].showCoord().x - player.showCoord().x) < 100 &&
                abs(obs[i].showCoord().y - player.showCoord().y) < 100)
                if (!damage.isNextPositionPlayerValid(player, obs[i])){
                    nextPosValid = false;
                    break;
                }
        if (nextPosValid)
            player.movePlayer();

        keyboard.controllerKeys(event, &pauseMenu, &player, &scr);

        if (event.type == ALLEGRO_EVENT_TIMER){
            if (event.timer.source == timerFrame){
                al_set_target_bitmap(draw.getBitmap(BACKGROUND));
                al_draw_bitmap(draw.getBitmap(GRASS), 0,0,0);
                
                draw.drawNonStaticElements(player, enemies);
                player.drawHealthBar();                

                al_set_target_bitmap(al_get_backbuffer(display));
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_scaled_bitmap(draw.getBitmap(BACKGROUND), player.showCoord().x - scr.width*scr.zoom/2, player.showCoord().y - scr.height*scr.zoom/2, scr.width*scr.zoom, scr.height*scr.zoom, 0, 0, scr.width, scr.height, 0);
                al_flip_display();
            }

            else if(event.timer.source == timerProjectile){
                if (player.projectile.isThrowing()){
                    nextPosValid = true;
                    for (int j = 0; j < NUM_WALLS; j ++)
                        if (abs(obs[j].showCoord().x - player.showCoord().x) < 100 && abs(obs[j].showCoord().y - player.showCoord().y) < 100)
                            if (!damage.isNextPositionProjectileValid(player.projectile, obs[j])){
                                nextPosValid = false;
                                break;
                            }

                    if (nextPosValid)
                        player.projectile.moveProj();
                    else
                        player.projectile.setThrowingStatus(false);
                    for (int i = 0; i < NUM_ENEMIES; i ++)
                        if (enemies[i].isAlive())
                            damage.playerProjectileHit(&enemies[i], &player);

                }
                for (int i = 0; i < NUM_ENEMIES; i ++){
                    if (enemies[i].isAlive()){
                        nextPosValid = true;
                        for (int j = 0; j < NUM_WALLS; j ++)
                            if (abs(obs[j].showCoord().x - enemies[i].showCoord().x) < 100 &&
                                    abs(obs[j].showCoord().y - enemies[i].showCoord().y) < 100)
                                if (!damage.isNextPositionEnemyValid(enemies[i], obs[j])){
                                    nextPosValid = false;
                                    break;
                                }

                        if (nextPosValid)
                            enemies[i].moveEnemy();


                        if (enemies[i].projectile.isThrowing()){
                            nextPosValid = true;
                            for (int j = 0; j < NUM_WALLS; j ++){
                                if (abs(obs[j].showCoord().x - enemies[i].showCoord().x) < 100 && abs(obs[j].showCoord().y - enemies[i].showCoord().y) < 100){
                                    if (!damage.isNextPositionProjectileValid(enemies[i].projectile, obs[j])){
                                        nextPosValid = false;
                                        break;
                                    }
                                }
                            }

                            if (nextPosValid)
                                enemies[i].projectile.moveProj();
                            else
                                enemies[i].projectile.setThrowingStatus(false);
                                
                            damage.enemyHitPlayer(&enemies[i], &player);
                            damage.projectileHitPlayer(&enemies[i].projectile, &player);
                        }   
                    }
                }
            }
            else if(event.timer.source == timerChangeDir){
                for (int i = 0; i < NUM_ENEMIES; i ++){
                    if (enemies[i].isAlive()){
                        enemies[i].setDirectionPlayer(player);
                    }
                }

            }
            else if (event.timer.source == player.showTimer(TIMER_INCREASE_SPEED)){
                player.resetSpeed();
                player.stopTimer(TIMER_INCREASE_SPEED);
            }
            else 
                for (int i = 0; i < NUM_ENEMIES; i ++)
                    if (enemies[i].isAlive())
                        if(event.timer.source == enemies[i].showTimer(TIMER_THROWING))
                            if (distanceBetween(player.showCoord(), enemies[i].showCoord()) < 350 && !enemies[i].projectile.isThrowing()) {
                                enemies[i].throwProjectile(player);
                                al_start_timer(timerChangeDir);
                                enemies[i].startTimer(TIMER_THROWING);
                            }
        }

    } while (!pauseMenu.isGameEnded());

    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}