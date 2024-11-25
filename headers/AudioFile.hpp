#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <iostream>
#include <string>

class AudioFile{
protected:
    std::string PATH;
public:
    AudioFile();
    explicit AudioFile(const std::string& PATH);
    virtual ~AudioFile();
    
    void play_info() const;
    
    virtual void play() const = 0;
    virtual void display() const = 0;
    virtual AudioFile* clone() const = 0;
};

#endif