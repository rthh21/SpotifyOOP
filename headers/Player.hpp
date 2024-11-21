#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>
#include "Playlist.hpp"
#include "Song.hpp"

class Player {
    private:
        int volume;
    public:
        Player();
        explicit Player(int volume);
        ~Player();
        
        const int& getVolume() const;
        void shuffle(const Playlist& targetPlaylist);
};

#endif
