#include <iostream>
#include "AudioFile.hpp"
#include "flac.hpp"
#include "SDL.h"
#include "SDL_mixer.h"


FLAC::FLAC() : compression(0) {}
FLAC::FLAC(const std::string& PATH, int compression) : AudioFile(PATH), compression(compression) {}
FLAC::~FLAC() {}

void FLAC::play() const {
    Mix_Music* music = Mix_LoadMUS(PATH.c_str());
    
    if (!music) {
        std::cerr << "Mix_LoadMUS failed: " << Mix_GetError() << '\n';
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
    }
    else if (Mix_PlayMusic(music, -1) == -1) {
        std::cerr << "Mix_PlayMusic failed: " << Mix_GetError() << '\n';
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
    }
    else{
        std::cout << "Playing FLAC\n";
        double duration = Mix_MusicDuration(music) * 1000; // seconds -> miliseconds
        SDL_Delay(duration);
    }
    
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void FLAC::display() const {
    std::cout<<"display";
}

AudioFile* FLAC::clone() const {
    return new FLAC(PATH, compression); 
}