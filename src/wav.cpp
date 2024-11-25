#include <iostream>
#include "wav.hpp"
#include "SDL.h"
#include "SDL_mixer.h"

WAV::WAV() : bitrate(24) {}
WAV::WAV(const std::string& PATH, int bitrate) : AudioFile(PATH), bitrate(bitrate) {}
WAV::~WAV() {}

void WAV::play() const {
    Mix_Chunk* music = Mix_LoadWAV(PATH.c_str());
    
    if (!music) {
        std::cerr << "Mix_LoadWAV failed: " << Mix_GetError() << '\n';
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
    }
    else if (Mix_PlayChannel(-1, music, 0) == -1) {
        std::cerr << "Mix_PlayChannel failed: " << Mix_GetError() << '\n';
        Mix_FreeChunk(music);
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
    }
    else {
        std::cout << "Playing WAV\n";
        while (Mix_PlayingMusic()) {
            SDL_Delay(100);  // Wait for 100ms before checking again
        }
    }
    
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void WAV::display() const{
    std::cout<<"display";
}
AudioFile* WAV::clone() const{
    return new WAV(PATH, bitrate);
}