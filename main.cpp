#include <iostream>
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

#define SDL_MAIN_HANDLED // fix pentru "main"

#include "SDL.h"
#include "SDL_mixer.h"

int main(){
    Player player;
    player.init();
    
    std::shared_ptr<AudioFile> type1 = std::make_unique<FLAC>("music/stargazing.flac", 5);
    Song song1("Stargazing","rap",type1);
    player.add_to_queue(song1);
    std::shared_ptr<AudioFile> type2 = std::make_unique<MP3>("music/fein.mp3", 5);
    Song song2("FE!N","rap",type2);
    player.add_to_queue(song2);
    
    Helper helper;
    helper.help();
    return 0;
}