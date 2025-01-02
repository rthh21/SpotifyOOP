#ifndef SAVESTATE_HPP
#define SAVESTATE_HPP 

#include "Song.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>

class SaveState{
private:
    int volume;
    std::string current_song;
public:
    SaveState();
    SaveState(int volume, const std::string& current_song);
    
    void load_file();
    
    int getCurrentVolume() const;
    const std::string& getCurrentSong() const;
    
    
    friend class Player;
};

#endif