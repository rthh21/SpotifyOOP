#include <iostream>

#define SDL_MAIN_HANDLED // fix pentru "main"


#include <array>
#include <thread>
#include <Helper.h>
#include <vector>
#include <cstring>
#include <fstream>
#include "Song.hpp"
#include "Album.hpp"
#include "Artist.hpp"
#include "Playlist.hpp"
#include "Player.hpp"
#include "AudioFile.hpp"
#include "FLAC.hpp"
#include "mp3.hpp"


#include "SDL.h"
#include "SDL_mixer.h"

int main(){
    Player player;
    player.init();
    player.start();
    
    Helper helper;
    helper.help();
    return 0;
}