#ifndef WAV_H
#define WAV_H

class WAV : public AudioFile{
private:
    int bitrate
public:
    WAV();
    explicit WAV(int bitrate);
    virtual ~WAV();
    
    void play() const override;
};

#endif