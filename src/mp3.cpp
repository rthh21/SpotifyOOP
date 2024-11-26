#include <iostream>
#include "mp3.hpp"
#include "SDL.h"
#include "SDL_mixer.h"

MP3::MP3() : bitrate(0) {}
MP3::MP3(const std::string& PATH, int bitrate) : AudioFile(PATH), bitrate(bitrate) {}
MP3::~MP3() {}

void MP3::play() const {
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
    else {
        std::cout << "Playing MP3\n";
        // double duration = Mix_MusicDuration(music) * 1000; // seconds -> miliseconds
        // SDL_Delay(duration);
        std::cin.get();
    }
    
    Mix_FreeMusic(music);
}

Mix_Music* MP3::file() const {
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

void MP3::display() const{
    std::cout<<"display";
}
AudioFile* MP3::clone() const{
    return new MP3(PATH, bitrate);
}