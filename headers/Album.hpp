#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include <vector>
#include "Song.hpp"

/**
 * @brief Iterator template
 * @details This template is part of the Iterator Design Pattern.
 * @tparam T 
 */
template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0; /**< Used to determine if an object exists after the current one */
    virtual T next() = 0;
    virtual ~Iterator() = default;
};

/**
 * @brief AlbumIterator
 * @details This class is part of the Iterator Design Pattern. Used to go iterate over each song element.
 */
class AlbumIterator : public Iterator<Song> {
private:
    const std::vector<Song>& songs;
    size_t index;

public:
    AlbumIterator(const std::vector<Song>& songs)
        : songs(songs), index(0) {}

    bool hasNext() override {
        return index < songs.size();
    }

    Song next() override {
        return songs[index++];
    }
};

/**
 * @brief Album class
 * @details This class is used to store each album that's loaded in "music" file.
 */
class Album{
    private:
        std::string name; /**< The name of the album */
        std::string genre; /**< The genre of the album TODO */
        std::vector<Song> songs; /**< An vector of Song type objects. It is used to store the songs of an album */
    public:
        void addSong(const Song& song);
        
        Album();
        Album(const std::string& name, const std::string& genre);
        ~Album();
        
        const std::string& getName() const;
        const std::string& getGenre() const;
        const std::vector<Song>& getSongs() const;
        
        /**< Part of the Iterator Design Pattern */
        AlbumIterator createIterator() const{
            return AlbumIterator(songs);
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Album& auxAlbum);
};

#endif