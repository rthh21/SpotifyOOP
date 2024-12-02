#include "Song.hpp"
#include "AudioFile.hpp"
#include "SDL.h"
#include "SDL_mixer.h"
#include "Song.hpp"

int Song::cnt = 0;

Song::Song() : title("--null"), genre("--null"), audiofile(nullptr) {++cnt;}  // nullptr instead of NULL

Song::Song(const std::string& title, const std::string& genre, std::shared_ptr<AudioFile> audiofile)
    : title(title), genre(genre), audiofile(std::move(audiofile)) {++cnt;}  // Move the smart pointer

Song::Song(const Song& other)
    : title(other.title), genre(other.genre), audiofile(other.audiofile) {}

Song::~Song() {}  

const int& Song::getCnt() const{
    return cnt;
}

const std::string& Song::getTitle() const {
    return title;
}

const std::string& Song::getGenre() const {
    return genre;
}

std::shared_ptr<AudioFile> Song::getAudioFile() const {
    return audiofile;
}

std::ostream& operator<<(std::ostream& os, const Song& auxSong) {
    os << "Song name: " << auxSong.getTitle() << ", genre: " << auxSong.getGenre() << '\n';
    return os;
}

Song& Song::operator=(Song other) {
    std::swap(title, other.title);
    std::swap(genre, other.genre);
    std::swap(audiofile, other.audiofile);
    return *this;
}