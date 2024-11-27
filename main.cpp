#include <iostream>
#include <Helper.h>
#define SDL_MAIN_HANDLED // fix pentru "main"

#include "Player.hpp"
<<<<<<< HEAD
=======
#include "AudioFile.hpp"
#include "flac.hpp"
#include "mp3.hpp"


>>>>>>> e5c6dd872569a695c1945b76b941ecc2f0e2477a
#include "SDL.h"
#include "SDL_mixer.h"

int main(){
    Player player;
    player.start();
    
    Helper helper;
    helper.help();
    return 0;
}