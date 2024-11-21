#ifndef FLAC_H
#define FLAC_H

class FLAC : public AudioFile{
private:
    int compression; // level of compressiong
public:
    FLAC();
    explicit FLAC(int compression);
    virtual ~FLAC();
    
    void play() const override;
};

#endif