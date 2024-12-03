#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Song.hpp"
#include "Artist.hpp"
#include "Playlist.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <random>

class Player {
private:
    int volume; /**< Global player volume. Used to set a specific value (range: 0-100) */
    int sq; /**< Global queue status flag. 0 - no songs in queue / 1 - songs in queue. It is used to play the next song from the queue when the previous one has finished playing. */
    std::string c; /**< This string is used to get the commands of the user. */
    static std::deque<Song> song_queue; /**< An array made out of "Song" objects. Used as a versatile queue for the player */
    std::vector<Artist> artists; /**< An array made out of "Artist" artists. Used as a way to store all the artists loaded from /music/ directory */
    std::vector<Playlist> playlists; /**< An array made out of "Playlist" artists. Used to store all the user-created playlists*/

public:
    Player();
    explicit Player(int volume);
    ~Player();
    void init();
    void load_files();
    Song& load_file_type(const std::string& token_artist);

    /**< Playback Methods*/
    void start();
    void stop() const;
    void help() const;
    void play(const Song& song);
    void play(const Album& album);
    void play(const Playlist& playlist);
    static void play(const std::deque<Song>& song_queue);
    static void pause();
    static void resume();

    /**< Queue Management Methods*/
    void add_to_queue(const Song& song);
    void add_to_queue(const Album& album);
    void add_to_queue(const Playlist& playlist);
    void remove_from_queue(const std::size_t position);
    void clear_queue();
    void shuffle(std::deque<Song>& song_queue);

    /**< Song/Album/Playlist methods*/
    Playlist find_playlist();
    Song find_song();
    Album find_album();
    void print_flac_songs();
    void print_mp3_songs();
    void print_ogg_songs();

    /**< Static methods*/
    static void song_cnt();
};

#endif
