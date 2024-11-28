#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>
#include <memory> 
#include "AudioFile.hpp"
#include "SDL.h"
#include "SDL_mixer.h"

class Song {
private:
    std::string title;
    std::string genre;
    std::shared_ptr<AudioFile> audiofile; 
    static int cnt;
public:
    Song();
    Song(const std::string& title, const std::string& genre, std::shared_ptr<AudioFile> audiofile);  

    ~Song(); 

    const int& getCnt() const;
    const std::string& getTitle() const;
    const std::string& getGenre() const;
    std::shared_ptr<AudioFile> getAudioFile();
    
    friend std::ostream& operator<<(std::ostream& os, const Song& auxSong);
};

#endif
