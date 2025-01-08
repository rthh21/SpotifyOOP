#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <vector>
#include <iostream>
#include "Album.hpp"
#include "Song.hpp"

/**
 * @brief Artist class
 * @details This class is used to store each artist that's loaded in "music" file.
 */
class Artist {
private:
    std::string name; /**< The name of the artist */
    std::string genre; 
    std::vector<Album> albums; /**< An vector of Album type objects. It is used to store the albums of an artist */
    std::vector<Song> songs; /**< An vector of Song type objects. It is used to store the songs of an artist */
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
