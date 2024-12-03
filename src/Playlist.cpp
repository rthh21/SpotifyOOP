/**
 * @file Playlist.cpp
 * @author rthh (andreythstan25@gmail.com)
 * @brief Manages music playback, song queue, and created playlists.
 * @details This file defines the Player class, which handles functionalities related to playing music, 
 *          managing song queues, and supporting the creation, modification, and playback of playlists.
 * @version 0.2
 * @date 03-12-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Playlist.hpp"
#include <iostream>

/**
 * @class Playlist
 * @brief Represents a music playlist that can hold songs and albums.
 * @details The Playlist class provides methods for adding and removing songs, displaying songs, and retrieving information 
 * about the playlist such as its name, creator, and list of songs.
 */
Playlist::Playlist() : name("--null"), createdBy("--null") {}

/**
 * @brief Constructs a Playlist object with a given name and creator.
 * @param name The name of the playlist.
 * @param createdBy The name of the person who created the playlist.
 */
Playlist::Playlist(const std::string& name, const std::string& createdBy)
    : name(name), createdBy(createdBy) {}

/**
 * @brief Copy constructor for creating a Playlist object from an existing one.
 * @param CpyPlaylist The Playlist object to copy.
 */
Playlist::Playlist(const Playlist& CpyPlaylist)
    : name(CpyPlaylist.name), createdBy(CpyPlaylist.createdBy), songs(CpyPlaylist.songs) {
}

/**
 * @brief Destroys the Playlist object.
 */
Playlist::~Playlist() {}

/**
 * @brief Assigns the contents of one Playlist object to another.
 * @param equalPlaylist The Playlist object to copy from.
 * @return A reference to the current Playlist object.
 */
Playlist& Playlist::operator=(const Playlist& equalPlaylist) {
    name = equalPlaylist.name;
    createdBy = equalPlaylist.createdBy;
    songs = equalPlaylist.songs;
    return *this;
}

/**
 * @brief Adds a song to the playlist.
 * @param song The Song object to add to the playlist.
 */
void Playlist::addSong(const Song& song) {
    songs.push_back(song);
}

/**
 * @brief Adds all songs from an album to the playlist.
 * @param album The Album object whose songs are to be added to the playlist.
 */
void Playlist::addAlbum(const Album& album) {
    for(const auto& song : album.getSongs()) {
        songs.push_back(song);
    }
}

/**
 * @brief Removes a song at a given position from the playlist.
 * @param x The position of the song to remove (1-based index).
 */
void Playlist::removeSongPos(int x) {
        songs.erase(songs.begin() + x - 1);
}

/**
 * @brief Displays all songs in the playlist with their respective positions.
 */
void Playlist::showSongs() {
    int i = 0;
    for(const auto& song : songs) {
        i++;
        std::cout << i << ". " << song.getTitle() << '\n';
    }
}

/**
 * @brief Gets the name of the playlist.
 * @return A constant reference to the name of the playlist.
 */
const std::string& Playlist::getName() const {
    return name;
}

/**
 * @brief Gets the name of the creator of the playlist.
 * @return A constant reference to the name of the creator.
 */
const std::string& Playlist::getCreatedBy() const {
    return createdBy;
}

/**
 * @brief Gets the list of songs in the playlist.
 * @return A constant reference to the vector containing songs in the playlist.
 */
const std::vector<Song>& Playlist::getSongs() const {
    return songs;
}

/**
 * @brief Overloads the output stream operator to print playlist information.
 * @param os The output stream to write to.
 * @param playlist The Playlist object to print.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "Playlist Name: " << playlist.name << ", created by: " << playlist.createdBy << '\n';
    return os;
}