#include "mp3.hpp"

MP3::MP3() : bitrate(0) {}
explicit MP3::MP3(int bitrate) : bitrate(bitrate) {}
virtual MP3::~MP3() {}

void play() const override{
    std::cout<< "Playing mp3 file from "<< PATH <<" with bitrate: "<< bitrate<<std::endl;
} 