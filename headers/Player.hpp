#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>
#include "Playlist.hpp"
#include "Song.hpp"

class Player {
private:
    int volume;
    static std::deque<Song> song_queue;
public:
    Player();
    explicit Player(int volume);
    ~Player();
        
    int init() const;
    
    void add_to_queue(Song& song);
    void add_to_queue(Album& album);
    void add_to_queue(Playlist& playlist);
    void remove_from_queue(std::size_t position);
    void play_queue();
    // int play_queue1();
    
    void shuffle(const Playlist& targetPlaylist);
    
    
    void play(Song& song);
    void pause();
    void resume();
};

#endif
