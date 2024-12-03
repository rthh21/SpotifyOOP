/**
 * @file ogg.cpp
 * @author rthh (andreythstan25@gmail.com)
 * @brief This file handles the ogg type files.
 * @version 0.2
 * @date 03-12-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ogg.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/**
 * @class OGG
 * @brief Represents an OGG audio file with additional properties and methods.
 * @details The OGG class extends the AudioFile class and provides specific handling for OGG files,
 *          including loading, displaying, and cloning functionality.
 */

/**
 * @brief Default constructor for the OGG class.
 * @details Initializes an OGG object with a bitrate of 0.
 */
OGG::OGG() : bitrate(0) {}

/**
 * @brief Constructs an OGG object with a given file path and bitrate.
 * @param PATH The path to the OGG audio file.
 * @param bitrate The bitrate of the OGG audio file.
 */
OGG::OGG(const std::string& PATH, int bitrate) : AudioFile(PATH), bitrate(bitrate) {}

/**
 * @brief Destructor for the OGG class.
 * @details Cleans up any resources associated with the OGG object.
 */
OGG::~OGG() {}

/**
 * @brief Loads and returns an SDL_Mixer music object from the OGG file.
 * @return A pointer to the Mix_Music object representing the loaded audio file, or nullptr if loading fails.
 */
Mix_Music* OGG::file() const {
    Mix_Music* music = Mix_LoadMUS(PATH.c_str());

    if (!music) {
        std::cerr << "Mix_LoadMUS failed: " << Mix_GetError() << '\n';
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return nullptr;
    }
    
    return music;
}

/**
 * @brief Displays a placeholder message to indicate the display functionality.
 */
void OGG::display() const {
    std::cout << "OGG audio file with path: " << PATH << " and bitrate level: " << bitrate << ".\n";
}
/**
 * @brief Clones the current OGG object and returns a new instance.
 * @return A pointer to a newly created AudioFile object that is a copy of the current OGG object.
 */
AudioFile* OGG::clone() const {
    return new OGG(PATH, bitrate);
}
