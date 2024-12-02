#include "Playlist.hpp"
#include <iostream>

Playlist::Playlist() : name("--null"), createdBy("--null") {}

Playlist::Playlist(const std::string& name, const std::string& createdBy)
    : name(name), createdBy(createdBy) {}

Playlist::Playlist(const Playlist& CpyPlaylist)
    : name(CpyPlaylist.name), createdBy(CpyPlaylist.createdBy), songs(CpyPlaylist.songs) {
}

Playlist::~Playlist() {}

Playlist& Playlist::operator=(const Playlist& equalPlaylist) {
    name = equalPlaylist.name;
    createdBy = equalPlaylist.createdBy;
    songs = equalPlaylist.songs;
    return *this;
}

void Playlist::addSong(const Song& song) {
    songs.push_back(song);
}

void Playlist::addAlbum(const Album& album) {
    for(const auto& song : album.getSongs()) {
        songs.push_back(song);
    }
}

void Playlist::removeSongPos(int x) {
        songs.erase(songs.begin() + x - 1);
}

void Playlist::showSongs() {
    int i = 0;
    for(const auto& song : songs) {
        i++;
        std::cout << i << ". " << song.getTitle() << '\n';
    }
}

const std::string& Playlist::getName() const {
    return name;
}

const std::string& Playlist::getCreatedBy() const {
    return createdBy;
}

const std::vector<Song>& Playlist::getSongs() const {
    return songs;
}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "Playlist Name: " << playlist.name << ", created by: " << playlist.createdBy << '\n';
    return os;
}
