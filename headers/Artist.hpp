#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <vector>
#include <iostream>
#include "Album.hpp"
#include "Song.hpp"

class Artist {
    private:
        std::string name;
        std::string genre;
        std::vector<Album> albums;
        std::vector<Song> songs;
    public:
        void addAlbum(const Album& album);
        void addSong(const Song& song);
        
        Artist(const std::string& name, const std::string& genre);
        ~Artist();
        
        const std::string& getName() const;
        const std::string& getGenre() const;
        const std::vector<Album>& getAlbums() const;
        const std::vector<Song>& getSongs() const;
        
        friend std::ostream& operator<<(std::ostream& os, const Artist& artist);
};

#endif
