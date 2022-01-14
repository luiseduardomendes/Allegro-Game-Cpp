#include "mainHeader.hpp"


// compilation
/* g++ main.cpp Colors.cpp chests.cpp common.cpp Damage.cpp enemies.cpp items.cpp keyboard.cpp obstacles.cpp pauseMenu.cpp player.cpp projectile.cpp draw.cpp $(pkg-config --libs allegro-5 allegro_font-5  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_dialog-5 --cflags) -lm -o AllegroGameTest1 */

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
    al_init_font_addon();
    al_init_ttf_addon();

    draw.loadAllBitmaps(scr);
    draw.initFonts();

    player.loadAllBitmaps();

    for(int i = 0; i < NUM_ENEMIES; i++){
        enemies[i].loadAllBitmaps();
    }

    for(int i = 0; i < NUM_CHESTS; i++){
        chests[i].loadBitmapOpen("assets/chestOpen.png");
        chests[i].loadBitmapClosed("assets/chestClosed.png");
        chests[i].setCoord(rand() % scr.bgWidth, rand() % scr.bgHeight);
        chests[i].setOpenStatus(false);
        do{
            Item buffer;
            int randomNumber = rand() % 10;
            if(randomNumber < 4){
                buffer = createShuriken();
            } 
            else if (randomNumber < 8 && randomNumber >= 4){
                buffer = createThrowingKnife();
            }
            else if (randomNumber <= 10 && randomNumber >= 4){
                buffer = createArmor();
            }
            chests[i].setItem(buffer);
        } while (!(chests[i].returnItem().returnItemId() != ITEM_ID_EMPTY));
    }


    player.initPlayer();
    player.setSpeed(2);
    player.setPosition(45, 45);
    player.setDirection(DOWN);
    player.setHitBox();
    player.projectile.setThrowingStatus(false);

    player.projectile.initProjectile();

    draw.initInventory(player);

    for (int i = 0; i < NUM_ENEMIES; i ++){
        enemies[i].initEnemy();
        enemies[i].setDirection(DOWN);
        do{
            enemies[i].setPosition(rand() % (scr.bgWidth), rand() % (scr.bgHeight));

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
        
        if (damage.isNextPositionPlayerValid(player, obs))
            player.movePlayer();

        keyboard.controllerKeys(event, &pauseMenu, &player, &scr, chests);

        if (event.type == ALLEGRO_EVENT_TIMER){
            if (event.timer.source == timerFrame){
                al_set_target_bitmap(draw.getBitmap(BACKGROUND));
                al_draw_bitmap(draw.getBitmap(GRASS), 0,0,0);
                
                
                draw.drawNonStaticElements(player, enemies);
                draw.drawStaticElements(chests);
                
                player.drawHealthBar();                

                al_set_target_bitmap(al_get_backbuffer(display));
                
                al_clear_to_color(al_map_rgb(0,0,0));

                al_draw_scaled_bitmap(draw.getBitmap(BACKGROUND), player.showCoord().x - scr.width*scr.zoom/2, player.showCoord().y - scr.height*scr.zoom/2, scr.width*scr.zoom, scr.height*scr.zoom, 0, 0, scr.width, scr.height, 0);
                
                draw.drawInventory(player, display);
                draw.drawEquipedItems(player, display);

                al_flip_display();
            }

            else if(event.timer.source == timerProjectile){
                if (player.projectile.isThrowing()){
                    if (damage.isNextPositionProjValid(player.projectile, obs))
                        player.projectile.moveProj();
                    else
                        player.projectile.setThrowingStatus(false);

                    for (int i = 0; i < NUM_ENEMIES; i ++)
                        if (enemies[i].isAlive())
                            damage.playerProjectileHit(&enemies[i], &player);

                }
                for (int i = 0; i < NUM_ENEMIES; i ++){
                    if (enemies[i].isAlive()){
                        
                        if (damage.isNextPositionEnemyValid(enemies[i], obs))
                            enemies[i].moveEnemy();

                        if (enemies[i].projectile.isThrowing()){
                            if (damage.isNextPositionProjValid(enemies[i].projectile, obs))
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