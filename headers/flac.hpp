#ifndef FLAC_H
#define FLAC_H

#include "AudioFile.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class FLAC : public AudioFile{
private:
    int compression; 
public:
    FLAC();
    explicit FLAC(const std::string& PATH, int compression);
    ~FLAC() override;
    
    Mix_Music* file() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif