#include "Song.hpp"
#include "AudioFile.hpp"

Song::Song() : title("null"), genre("null"), audiofile(nullptr) {}  // nullptr instead of NULL
Song::Song(const std::string& title, const std::string& genre, std::shared_ptr<AudioFile> audiofile)
    : title(title), genre(genre), audiofile(std::move(audiofile)) {}  // Move the smart pointer

Song::~Song() {}  

void Song::play() {
    if (audiofile) {
        audiofile->play();  // Play using the smart pointer
    }
}

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
