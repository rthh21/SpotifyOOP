#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include <vector>
#include "Song.hpp"

// Iterator Design
template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() = default;
};

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
        
        AlbumIterator createIterator() const{
            return AlbumIterator(songs);
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Album& auxAlbum);
};

#endif