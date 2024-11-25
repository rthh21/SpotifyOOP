#ifndef MP3_H
#define MP3_h

#include <string>
#include "AudioFile.hpp"

class MP3 : public AudioFile{
private:
    int bitrate;
public:
    MP3();
    explicit MP3(const std::string& PATH, int bitrate);
    virtual ~MP3();
    
    void play() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif