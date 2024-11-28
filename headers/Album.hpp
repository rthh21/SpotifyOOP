#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include <iostream>
#include <vector>
#include "Song.hpp"

class Album{
    private:
        std::string name;
        std::string genre;
        std::vector<Song> songs;
    public:
        void addSong(const Song& song);
        
        Album();
        Album(const std::string& name, const std::string& genre);
        ~Album();
        
        const std::string& getName() const;
        const std::string& getGenre() const;
        const std::vector<Song>& getSongs() const;
        
        friend std::ostream& operator<<(std::ostream& os, const Album& auxAlbum);
};

#endif