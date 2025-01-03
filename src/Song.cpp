/**
 * @file Song.cpp
 * @author rthh (andreythstan25@gmail.com)
 * @brief This file handles the loaded songs
 * @details This file has a shared pointer used to manage the type of the audio file
 * @version 0.2
 * @date 03-12-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Song.hpp"
#include "AudioFile.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int Song::cnt = 0;

Song::Song() : title("--null"), genre("--null"), duration(0), audiofile(nullptr) {++cnt;}  // nullptr instead of NULL

Song::Song(const std::string& title, const std::string& genre, double duration, std::shared_ptr<AudioFile> audiofile)
    : title(title), genre(genre), duration(duration), audiofile(std::move(audiofile)) {++cnt;}  // Move the smart pointer

Song::Song(const Song& other)
    : title(other.title), genre(other.genre), duration(other.duration), audiofile(other.audiofile) {}

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

int Song::getDuration() const {
    return duration;
}

std::shared_ptr<AudioFile> Song::getAudioFile() const {
    return audiofile;
}

std::ostream& operator<<(std::ostream& os, const Song& auxSong) {
    os << "Song name: " << auxSong.getTitle() << ", duration (s): " << auxSong.getDuration() << '\n';
    return os;
}

Song& Song::operator=(Song other) {
    std::swap(title, other.title);
    std::swap(genre, other.genre);
    std::swap(duration, other.duration);
    std::swap(audiofile, other.audiofile);
    return *this;
}