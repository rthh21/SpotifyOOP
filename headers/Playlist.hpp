#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include <iostream>
#include "Song.hpp"
#include "Album.hpp"

class Playlist {
    private:
        std::string name;
        std::string createdBy;
        std::vector<Song> songs;
    public:
        void addSong(const Song& song);
        void addAlbum(const Album& album);
        void removeSongPos(int x);
        void showSongs();
        
        Playlist();
        Playlist(const std::string& name, const std::string& createdBy);
        Playlist(const Playlist& CpyPlaylist);
        ~Playlist();
        
        Playlist& operator=(const Playlist& equalPlaylist);
        
        const std::string& getName() const;
        const std::string& getCreatedBy() const;
        const std::vector<Song>& getSongs() const;
        
        friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);
};

#endif
