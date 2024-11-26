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
#include "AudioFile.hpp"
#include "flac.hpp"
#include "mp3.hpp"

class Player {
private:
    int volume;
    static std::deque<Song> song_queue;
public:
    Player();
    explicit Player(int volume);
    ~Player();
        
    int init() const;
    void start();
    
    int queue_status();
    void add_to_queue(Song& song);
    void add_to_queue(Album& album);
    void add_to_queue(Playlist& playlist);
    void remove_from_queue(std::size_t position);
    
    void shuffle(const Playlist& targetPlaylist);
    
    
    void play(std::deque<Song> &song_queue);
    void pause();
    void resume();
};

#endif
