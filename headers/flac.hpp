#ifndef FLAC_H
#define FLAC_H

#include <string>
#include "AudioFile.hpp"
#define SDL_MAIN_HANDLED // fix pentru "main"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class FLAC : public AudioFile{
private:
    int compression; // level of compressiong
public:
    FLAC();
    explicit FLAC(const std::string& PATH, int compression);
    virtual ~FLAC();
    
    Mix_Music* file() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif