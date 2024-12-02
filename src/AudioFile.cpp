#include "AudioFile.hpp"

AudioFile::AudioFile() : PATH("NULL") {}

AudioFile::AudioFile(const std::string& PATH) : PATH(PATH) {}

AudioFile::~AudioFile() {}

void AudioFile::interface() const{
    Mix_Music* music = file();
    if (music) {
        std::cout << "Music loaded successfully from: " << PATH << "\n";
        if (Mix_PlayMusic(music, 1) == -1) {
            std::cerr << "Mix_PlayMusic failed: " << Mix_GetError() << '\n';
        }
    }
}
