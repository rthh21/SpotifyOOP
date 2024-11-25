#ifndef FLAC_H
#define FLAC_H

#include <string>
#include "AudioFile.hpp"


class FLAC : public AudioFile{
private:
    int compression; // level of compressiong
public:
    FLAC();
    explicit FLAC(const std::string& PATH, int compression);
    virtual ~FLAC();
    
    void play() const override;
    void display() const override;
    AudioFile* clone() const override;
};

#endif