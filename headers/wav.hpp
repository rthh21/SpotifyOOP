#ifndef WAV_H
#define WAV_H

#include <string>
#include "AudioFile.hpp"

class WAV : public AudioFile{
private:
    int bitrate;
public:
    WAV();
    explicit WAV(const std::string& PATH, int bitrate);
    virtual ~WAV();
    
    void play() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif