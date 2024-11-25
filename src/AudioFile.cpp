#include "AudioFile.hpp"

AudioFile::AudioFile() : PATH("NULL") {}

AudioFile::AudioFile(const std::string& PATH) : PATH(PATH) {}

AudioFile::~AudioFile() {}

void AudioFile::play_info() const{
    std::cout<<"PATH: "<<PATH<<std::endl;
    play();
    display();
}