#include "wav.hpp"

WAV::WAV() : bitrate(24) {}
explicit WAV::WAV(int bitrate) : bitrate(bitrate) {}
virtual WAV::~WAV() {}

void play() const override{
    std::cout<< "Playing wav file from "<< PATH <<" with bitrate: "<< bitrate<<std::endl;
} 