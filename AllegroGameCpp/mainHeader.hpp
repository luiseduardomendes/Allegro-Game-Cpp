#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "player.hpp"
#include "pauseMenu.hpp"
#include "Colors.hpp"
#include "keyboard.hpp"

using namespace std;

typedef struct{
    int width, height;
}Screen;


enum {UP= 0, DOWN, LEFT, RIGHT};

