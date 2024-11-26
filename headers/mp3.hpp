#ifndef MP3_HPP
#define MP3_HPP

#include <string>
#include "AudioFile.hpp"
#define SDL_MAIN_HANDLED // fix pentru "main"

#include "SDL.h"
#include "SDL_mixer.h"

class MP3 : public AudioFile{
private:
    int bitrate;
public:
    MP3();
    explicit MP3(const std::string& PATH, int bitrate);
    virtual ~MP3();
    
    Mix_Music* file() const override; 
    void play() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif