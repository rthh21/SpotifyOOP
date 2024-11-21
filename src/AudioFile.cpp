#include "AudioFile.hpp"

AudioFile::AudioFile() : PATH("NULL"), duration(0) {}

explicit AudioFile::AudioFile(const std::string& PATH, int duration) : PATH(PATH), duration(duration) {}
virtual AudioFile::AudioFile* clone() const = 0;

virtual ~AudioFile() {}

virtual void AudioFile::play() const = 0;
virtual void AudioFile::display() const = 0;

void AudioFile::play_info() const{
    std::cout<<"PATH: "<<PATH<<", duration: "<< duration<<std::endl;
    //TODO : SFML PLAY
}