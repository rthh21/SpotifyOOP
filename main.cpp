#include <iostream>
#include <Helper.h>
#define SDL_MAIN_HANDLED // fix pentru "main"

#include "Player.hpp"
#include "SDL.h"
#include "SDL_mixer.h"

int main(){
    Player player;
    player.start();
    
    Helper helper;
    helper.help();
    return 0;
}