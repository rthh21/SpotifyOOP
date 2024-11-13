#include "Album.hpp"


Album::Album(const std::string& name, const std::string& genre)
    : name(name), genre(genre) {}

Album::~Album() {}

void Album::addSong(const Song& song) {
    songs.push_back(song);
}

const std::string& Album::getName() const {
    return name;
}

const std::string& Album::getGenre() const {
    return genre;
}

const std::vector<Song>& Album::getSongs() const {
    return songs;
}

std::ostream& operator<<(std::ostream& os, const Album& auxAlbum) {
    os << "Album Name: " << auxAlbum.name << ", Genre: " << auxAlbum.genre << '\n';
    return os;
}