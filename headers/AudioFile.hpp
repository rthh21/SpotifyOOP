#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_mixer.h"

class AudioFile{
protected:
    std::string PATH;
public:
    AudioFile();
    explicit AudioFile(const std::string& PATH);
    virtual ~AudioFile();
    
    void play_info() const;
    
    virtual Mix_Music* file() const = 0;
    virtual void display() const = 0;
    virtual AudioFile* clone() const = 0;
};

#endif