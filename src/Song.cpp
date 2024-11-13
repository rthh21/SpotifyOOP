#include "Song.hpp"


Song::Song() : title("null"), genre("null"), duration(0) {}
Song::Song(const std::string& title, const std::string& genre)
    : title(title), genre(genre), duration(0) {}
Song::Song(const std::string& title, const std::string& genre, int duration)
    : title(title), genre(genre), duration(duration) {}
Song::~Song() {}

const std::string& Song::getTitle() const {
    return title;
}
const std::string& Song::getGenre() const {
    return genre;
}
const int& Song::getDuration() const {
    return duration;
}

std::ostream& operator<<(std::ostream& os, const Song& auxSong) {
    os << "Song name: " << auxSong.title << ", genre: " << auxSong.genre
       << ", and duration: " << auxSong.duration << '\n';
    return os;
}
