#include <iostream>
#include "ogg.hpp"
#include "SDL.h"
#include "SDL_mixer.h"

OGG::OGG() : bitrate(0) {}
OGG::OGG(const std::string& PATH, int bitrate) : AudioFile(PATH), bitrate(bitrate) {}
OGG::~OGG() {}

Mix_Music* OGG::file() const {
    Mix_Music* music = Mix_LoadMUS(PATH.c_str());

    if (!music) {
        std::cerr << "Mix_LoadMUS failed: " << Mix_GetError() << '\n';
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return nullptr;
    }
    // Returning the pointer to the caller
    return music;
}

void OGG::display() const{
    std::cout<<"display";
}
AudioFile* OGG::clone() const{
    return new OGG(PATH, bitrate);
}