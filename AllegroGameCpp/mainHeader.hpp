#include <iostream>
#include <cstdlib>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

enum {UP= 0, DOWN, LEFT, RIGHT};
enum {TIMER_SLOW, TIMER_MOVE, TIMER_DAMAGE, TIMER_THROWING, TIMER_INCREASE_SPEED};
enum bitmaps{WALL, SPIKE, ROCK, GRASS, GRASSBLOCK1, GRASSBLOCK2, GRASSBLOCK3, BACKGROUND, INV_SLOT_BMP, THR_KNIFE_BMP, SHURIKEN_BMP, ARMOR_BMP};
enum items {EMPTY, SHURIKEN, THROWING_KNIFE, LIGHT_ARMOR, ARMOR, HEAVY_ARMOR};

#define NUM_WALLS 300
#define NUM_ENEMIES 5
#define NUM_CHESTS 10

typedef struct{
    int x, y;
}Coordinates;

typedef struct{
    Coordinates inf, sup;
}HitBoxRange;

typedef struct{
    int width, height;
    int bgWidth, bgHeight;
    double zoom;
}Screen;


#include "obstacles.hpp"
#include "chests.hpp"
#include "Colors.hpp"
#include "projectile.hpp"
#include "player.hpp"
#include "enemies.hpp"

double distanceBetween(Coordinates a, Coordinates b);
void createObstacles(Obstacles obstacles[], Screen screen);
bool isEnemyIn(Player player, Enemies enemy);
bool pointInsideBox(Coordinates, HitBoxRange);
bool isProjectileIn(HitBoxRange HB, Projectile projectile);
bool isHitboxIn(HitBoxRange HB1, HitBoxRange HB2);

#include "Damage.hpp"
#include "draw.hpp"
#include "pauseMenu.hpp"
#include "keyboard.hpp"

using namespace std;

