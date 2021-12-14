#include <iostream>
#include <cstdlib>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

enum {UP= 0, DOWN, LEFT, RIGHT};
enum {TIMER_SLOW, TIMER_MOVE, TIMER_DAMAGE};
enum {WALL, SPIKE, ROCK};

typedef struct{
    int x, y;
}Coordinates;

typedef struct{
    Coordinates inf, sup;
}HitBoxRange;

#include "obstacles.hpp"

#include "Colors.hpp"
#include "projectile.hpp"
#include "player.hpp"
#include "enemies.hpp"


bool isEnemyIn(Player player, Enemies enemy);
bool pointInsideBox(Coordinates, HitBoxRange);
bool isProjectileIn(HitBoxRange HB, Projectile projectile);
bool isHitboxIn(HitBoxRange HB1, HitBoxRange HB2);

#include "Damage.hpp"
#include "pauseMenu.hpp"
#include "keyboard.hpp"

using namespace std;

typedef struct{
    int width, height;
}Screen;
