#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>
#include "Playlist.hpp"
#include "Song.hpp"
#include "Artist.hpp"
#include "AudioFile.hpp"
#include "flac.hpp"
#include "mp3.hpp"

class Player {
private:
    int volume;
    static std::deque<Song> song_queue;
    std::vector<Artist> artists;
    std::vector<Playlist> playlists;
public:
    Player();
    explicit Player(int volume);
    ~Player();
        
    void init();
    void load_files();
    Song& load_file_type(const std::string& token_artist);
    void start();
    void stop() const;
    
    Playlist find_playlist();
    Song find_song();
    Album find_album();
    
    void print_flac_songs();
    void print_mp3_songs();
    void print_ogg_songs();
    
    void add_to_queue(const Song& song);
    void add_to_queue(const Album& album);
    void add_to_queue(const Playlist& playlist);
    void remove_from_queue(const std::size_t position);
    void clear_queue();
    
    void shuffle(std::deque<Song> &song_queue);
    
    void play(std::deque<Song> &song_queue);
    void play(Song& song);
    void play(Album& album);
    void play(Playlist& playlist);
    
    void pause() const;
    void resume() const;
    static void song_cnt();
};

#endif
