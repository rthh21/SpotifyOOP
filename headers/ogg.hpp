#ifndef OGG_HPP
#define OGG_HPP

#include <string>
#include "AudioFile.hpp"
#define SDL_MAIN_HANDLED // fix pentru "main"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class OGG : public AudioFile{
private:
    int bitrate;
public:
    OGG();
    explicit OGG(const std::string& PATH, int bitrate);
    virtual ~OGG();
    
    Mix_Music* file() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif