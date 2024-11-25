#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>
#include <memory>  // Include for smart pointers
#include "AudioFile.hpp"

class Song {
private:
    std::string title;
    std::string genre;
    std::shared_ptr<AudioFile> audiofile;  // Use unique_ptr for AudioFile
    
public:
    Song();
    Song(const std::string& title, const std::string& genre, std::shared_ptr<AudioFile> audiofile);  // Accept smart pointer

    ~Song();  // Destructor will automatically clean up the audiofile

    void play();

    const std::string& getTitle() const;
    const std::string& getGenre() const;

    friend std::ostream& operator<<(std::ostream& os, const Song& auxSong);
};

#endif
