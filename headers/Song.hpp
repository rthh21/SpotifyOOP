#ifndef SONG_H
#define SONG_H

#include "AudioFile.hpp"
#include <iostream>
#include <string>
#include <memory>

class Song {
private:
    std::string title;
    std::string genre;
    std::shared_ptr<AudioFile> audiofile; 
    static int cnt;
public:
    Song();
    Song(const std::string& title, const std::string& genre, std::shared_ptr<AudioFile> audiofile);  
    Song(const Song& other);
    ~Song(); 

    const int& getCnt() const;
    const std::string& getTitle() const;
    const std::string& getGenre() const;
    std::shared_ptr<AudioFile> getAudioFile() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Song& auxSong);
    Song &operator=(Song other);
};

#endif
