#include <iostream>
#include <cstdlib>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

typedef struct{
    int x, y;
}Coordinates;

typedef struct{
    Coordinates inf, sup;
}HitBoxRange;

#include "player.hpp"
#include "pauseMenu.hpp"
#include "projectile.hpp"
#include "Colors.hpp"
#include "keyboard.hpp"

using namespace std;

typedef struct{
    int width, height;
}Screen;



enum {UP= 0, DOWN, LEFT, RIGHT};

