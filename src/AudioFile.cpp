/**
 * @file AudioFile.cpp
 * @author rthh (andreythstan25@gmail.com)
 * @version 0.3
 * @date 08-01-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 
#include "AudioFile.hpp"

AudioFile::AudioFile() : PATH("NULL") {}

AudioFile::AudioFile(const std::string& PATH) : PATH(PATH) {}

AudioFile::~AudioFile() {}

void AudioFile::interface() const{
    display();
    Mix_Music* music = file();
    if (music) {
        std::cout << "Music loaded successfully from: " << PATH << "\n";
        if (Mix_PlayMusic(music, 1) == -1) {
            std::cerr << "Mix_PlayMusic failed: " << Mix_GetError() << '\n';
        }
    }
}
