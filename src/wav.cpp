#include "wav.hpp"
#include <iostream>

WAV::WAV() : bitrate(24) {}
WAV::WAV(const std::string& PATH, int bitrate) : AudioFile(PATH), bitrate(bitrate) {}
WAV::~WAV() {}

void WAV::play() const {
    std::cout<< "Playing wav file from "<< PATH <<" with bitrate: "<< bitrate<<'\n';
} 
void WAV::display() const{
    std::cout<<"display";
}
AudioFile* WAV::clone() const{
    return new WAV(PATH, bitrate);
}