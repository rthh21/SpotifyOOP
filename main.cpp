#include <iostream>
#include <Helper.h>

#include "Exceptions.hpp"
#include "CheckInit.hpp"

#define SDL_MAIN_HANDLED // fix pentru "main"

#include "Player.hpp"
#include "SaveState.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(){
    SaveState state;
    state.load_file();
    Player player(state.getCurrentVolume(),state.getCurrentSong());
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