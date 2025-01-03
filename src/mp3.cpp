#include "mp3.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

MP3::MP3() : bitrate(0) {}
MP3::MP3(const std::string& PATH, int bitrate) : AudioFile(PATH), bitrate(bitrate) {}
MP3::~MP3() {}

Mix_Music* MP3::file() const {
    Mix_Music* music = Mix_LoadMUS(PATH.c_str());

    if (!music) {
        std::cerr << "Mix_LoadMUS failed: " << Mix_GetError() << '\n';
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return nullptr;
    }
    
    return music;
}

void MP3::display() const {
    std::cout << "MP3 audio file with path: " << PATH << " and bitrate level: " << bitrate << ".\n";
}
AudioFile* MP3::clone() const{
    return new MP3(PATH, bitrate);
}