/**
 * @file SaveState.cpp
 * @author rthh (andreythstan25@gmail.com)
 * @version 0.3
 * @date 08-01-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 
#include "SaveState.hpp"
#include <fstream>

SaveState::SaveState() : volume(100), current_song("--null") {};

SaveState::SaveState(int volume, const std::string& current_song)
    :volume(volume), current_song(current_song) {}
    
void SaveState::load_file(){
    std::ifstream sfin("state.txt");
    
    if(sfin.is_open()){
        sfin >> volume;
        sfin.ignore();
        if(!std::getline(sfin,current_song)){
            current_song = "";
        }
        sfin.close();
    }
    else {
        std::cout << "Can't open save file!\n";
    }
}        

void SaveState::save_file(int volume, const std::string& current_song){
    std::ofstream sfout("state.txt");
    
    if(sfout.is_open()){
        sfout << volume <<'\n';
        sfout << current_song;
        sfout.close();
    }
    else {
        std::cout << "Can't open save file!\n";
    }
}

int SaveState::getCurrentVolume() const{ return volume; }
const std::string& SaveState::getCurrentSong() const{ return current_song; }   