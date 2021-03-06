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

#define NUM_WALLS 300
#define NUM_ENEMIES 10
#define NUM_CHESTS 30

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

#include "items.hpp"
#include "obstacles.hpp"
#include "chests.hpp"
#include "Colors.hpp"
#include "projectile.hpp"
#include "player.hpp"
#include "enemies.hpp"
#include "common.hpp"

#include "Damage.hpp"
#include "draw.hpp"
#include "pauseMenu.hpp"
#include "keyboard.hpp"

using namespace std;

