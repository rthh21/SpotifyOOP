#include <iostream>
#include <Helper.h>

#include "Exceptions.hpp"
#include "CheckInit.hpp"

#define SDL_MAIN_HANDLED // fix pentru "main"

#include "Player.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(){
    Player player;
    try {
        player.init();
        player.start();
    } catch (const check_init &e){
        std::cerr << "Error: " << e.what()<<std::endl;
    }
    
    Helper helper;
    helper.help();
    return 0;
}