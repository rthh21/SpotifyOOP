#ifndef MP3_HPP
#define MP3_HPP

#include "AudioFile.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class MP3 : public AudioFile{
private:
    int bitrate;
public:
    MP3();
    explicit MP3(const std::string& PATH, int bitrate);
    ~MP3() override;
    
    Mix_Music* file() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif