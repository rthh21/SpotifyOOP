#include "Song.hpp"


Song::Song() : title("null"), genre("null") {}
Song::Song(const std::string& title, const std::string& genre)
    : title(title), genre(genre) {}
Song::~Song() {}

const std::string& Song::getTitle() const {
    return title;
}
const std::string& Song::getGenre() const {
    return genre;
}

std::ostream& operator<<(std::ostream& os, const Song& auxSong) {
    os << "Song name: " << auxSong.title << ", genre: " << auxSong.genre << '\n';
    return os;
}
