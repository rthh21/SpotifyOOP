#include "Artist.hpp"

Artist::Artist(const std::string& name, const std::string& genre)
    : name(name), genre(genre) {}

Artist::~Artist() {}

void Artist::addAlbum(const Album& album) {
    albums.push_back(album);
}

void Artist::addSong(const Song& song) {
    songs.push_back(song);
}

const std::string& Artist::getName() const {
    return name;
}

const std::string& Artist::getGenre() const {
    return genre;
}

const std::vector<Album>& Artist::getAlbums() const {
    return albums;
}

const std::vector<Song>& Artist::getSongs() const {
    return songs;
}

std::ostream& operator<<(std::ostream& os, const Artist& artist) {
    os << "Artist Name: " << artist.name << ", Genre: " << artist.genre << '\n';
    return os;
}
