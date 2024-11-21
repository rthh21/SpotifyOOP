#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <iostream>
#include <string>

class AudioFile{
protected:
    std::string PATH;
    int duration;
public:
    AudioFile();
    explicit AudioFile(const std::string& PATH, int duration);
    virtual AudioFile* clone() const;
    virtual ~AudioFile();
    
    virtual void play() const;
    virtual void display() const;
    
    //TODO:
    void play_info() const;
};

#endif