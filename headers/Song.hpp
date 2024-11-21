#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>

class Song {
private:
    std::string title;
    std::string genre;

public:
    Song();
    Song(const std::string& title, const std::string& genre);

    ~Song();

    const std::string& getTitle() const;
    const std::string& getGenre() const;

    friend std::ostream& operator<<(std::ostream& os, const Song& auxSong);
};

#endif