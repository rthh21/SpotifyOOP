#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/**
 * @brief AudioFile class
 * @details This class is used to store additional information about a song. Using SDl2, it creates a music type object.
 */
class AudioFile{
protected:
    std::string PATH; /**< The path of a song. Used for SDL2 Mix_Music */
public:
    AudioFile();
    explicit AudioFile(const std::string& PATH);
    virtual ~AudioFile();
    
    void interface() const;
    
    virtual Mix_Music* file() const = 0;
    virtual void display() const = 0;
    virtual AudioFile* clone() const = 0;
};

#endif