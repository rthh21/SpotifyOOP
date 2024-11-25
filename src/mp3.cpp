#include "mp3.hpp"
#include <iostream>

MP3::MP3() : bitrate(0) {}
MP3::MP3(const std::string& PATH, int bitrate) : AudioFile(PATH), bitrate(bitrate) {}
MP3::~MP3() {}

void MP3::play() const {
    std::cout<< "Playing mp3 file from "<< PATH <<" with bitrate: "<< bitrate<<'\n';
}  
void MP3::display() const{
    std::cout<<"display";
}
AudioFile* MP3::clone() const{
    return new MP3(PATH, bitrate);
}