#ifndef MP3_H
#define MP3_h

class MP3 : public AudioFile{
private:
    int bitrate;
public:
    MP3();
    explicit MP3(int bitrate);
    virtual ~MP3();
    
    void play() const override;
};

#endif