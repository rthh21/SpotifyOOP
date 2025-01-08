#ifndef SAVESTATE_HPP
#define SAVESTATE_HPP 

#include "Song.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>

/**
 * @brief SaveState class
 * @details This class is used to store, load and save the previous session information: last song played and volume.
            The user can then choose to play the last session song.
 */
class SaveState{
private:
    int volume;
    std::string current_song;
public:
    SaveState();
    SaveState(int volume, const std::string& current_song);
    
    void load_file();
    void save_file(int volume, const std::string& current_song);
    
    int getCurrentVolume() const;
    const std::string& getCurrentSong() const;
    
    
    friend class Player;
};

#endif