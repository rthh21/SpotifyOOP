#include "AudioFile.hpp"
#include "flac.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


FLAC::FLAC() : compression(0) {}
FLAC::FLAC(const std::string& PATH, int compression) : AudioFile(PATH), compression(compression) {}
FLAC::~FLAC() {}

Mix_Music* FLAC::file() const {
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


void FLAC::display() const {
    std::cout<<"display";
}

AudioFile* FLAC::clone() const {
    return new FLAC(PATH, compression); 
}