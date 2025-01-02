/**
 * @file Player.cpp
 * @author rthh (andreythstan25@gmail.com)
 * @brief This file handles the command loop and anything related to playback
 * @version 0.2
 * @date 03-12-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 
#include "Player.hpp"
#include "AudioFile.hpp"
#include "flac.hpp"
#include "mp3.hpp"
#include "ogg.hpp"
#include "SaveState.hpp"

#include "Exceptions.hpp"
#include "CheckDirectory.hpp"
#include "CheckInit.hpp"
#include "CheckPlaying.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

std::deque<Song> Player::song_queue;

/**
 * @brief Construct a new Player:: Player object.
 * @details Sets the default volume to 100. Sets sq (status queue) to 0 (no songs in queue). Sets c (command) to empty
 */
Player::Player() : volume(100), sq(0), current_song("") {}

/**
 * @brief Construct a new Player:: Player object with a specified volume
 * @details Sets the default volume to the desired value. Sets sq (status queue) to 0 (no songs in queue). Sets c (command) to empty
 * @param volume The audio volume of the player
 */
Player::Player(int volume, const std::string& current_song) : volume(volume), sq(0), current_song(current_song) {
    std::cout << "Loaded from previous session:\n";
    std::cout << "Volume: " << this->volume << '\n';
    if(!current_song.empty()){
        std::cout << "Current song: " << this->current_song << '\n'; 
    }
}

/**
 * @brief Destroy the Player:: Player object
 * 
 */
Player::~Player() {}

/**
 * @brief Initializes the audio player
 * @details This function initializes the audio player and verifies that everything is working.
 * @note This function must be called at the start of the program (It's called in function "start()") 
 */
void Player::init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        throw check_init("SDL_Init(SDL_INIT_AUDIO) failed: ");
    }

    if (Mix_Init(MIX_INIT_FLAC) == 0 || Mix_Init(MIX_INIT_MP3) == 0) {
        throw check_init("Mix_Init failed: ");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        stop();
        throw check_init("Mix_OpenAudio failed: ");
    }
    
    load_files(); /**< Calls "load_files()" as part of init. */
    
    Mix_VolumeMusic(volume);
    if(!current_song.empty()) {
        Song song_found = find_song(current_song);
        play(song_found);
        pause();
    }
}
 
/**
 * @brief Loads the files from "../music"
 * @details This function loads the music files from "../music".
 * 
 * The files inside "../music" have a "descriptor". A descriptor has the format "type-name". For examle: an artist "Travis Scott" has a 
 * directory named "Artist-Travis Scott". Inside "Artist-Travis Scott" is a directory named "Album-Utopia", creating the album Utopia. 
 * The artist or album directory can contain songs. A song has the descriptor "Song-name".
 * 
 * This function opens each file and creates an object based on the type and the name of the directort (from descriptor).
 * By iterating through each file using for loops, the code has now loaded all the songs.
 */
void Player::load_files() {
    std::string song_name;

    try {
        std::string path = "..\\music";
        if (!fs::is_directory(path)){
            throw is_not_directory(path);
        }
        
        for (const auto &entry : fs::directory_iterator(path)) {
            std::string token = entry.path().string();
            
            //artist
            if (token.find("Artist-") != std::string::npos) {
                std::string artist_name = token.substr(token.find("Artist-") + 7);
                std::cout<<"Artist: "<<artist_name<<'\n';
                Artist artist(artist_name,"");
                for (const auto & artist_token : fs::directory_iterator(token)) {
                    std::string token_artist = artist_token.path().string();
                    
                    //album
                    if (token_artist.find("Album-") != std::string::npos) {
                        std::string album_name = token_artist.substr(token_artist.find("Album-") + 6);
                        std::cout<<"Album: "<<album_name<<'\n';
                        Album album(album_name,"");
                        for (const auto & artist_token : fs::directory_iterator(token_artist)) {
                            std::string token_album = artist_token.path().string();
                            if (token_album.find(".flac") != std::string::npos) {
                                song_name = token_album.substr(token_album.find_last_of("\\") + 1);
                                song_name = song_name.substr(song_name.find('-') + 1, song_name.find(".flac") - song_name.find('-') - 1);
                                std::shared_ptr<AudioFile> flac_ptr = std::make_shared<FLAC>(token_album,5);
                                Song song(song_name, artist_name, flac_ptr);
                                album.addSong(song);
                                std::cout<<"Song: "<<song_name<<'\n';
                            } 
                            else if (token_album.find(".mp3") != std::string::npos) {
                                song_name = token_album.substr(token_album.find_last_of("\\") + 1);
                                song_name = song_name.substr(song_name.find('-') + 1, song_name.find(".mp3") - song_name.find('-') - 1);
                                std::shared_ptr<AudioFile> mp3_ptr = std::make_shared<MP3>(token_album,5);
                                Song song(song_name, artist_name, mp3_ptr);
                                album.addSong(song);
                                std::cout<<"Song: "<<song_name<<'\n';
                            }
                            else if (token_album.find(".ogg") != std::string::npos) {
                                song_name = token_album.substr(token_album.find_last_of("\\") + 1);
                                song_name = song_name.substr(song_name.find('-') + 1, song_name.find(".ogg") - song_name.find('-') - 1);
                                std::shared_ptr<AudioFile> ogg_ptr = std::make_shared<OGG>(token_album,5);
                                Song song(song_name, artist_name, ogg_ptr);
                                album.addSong(song);
                                std::cout<<"Song: "<<song_name<<'\n';
                            }
                        }
                        artist.addAlbum(album);
                    }
                    
                    //melodie
                    if (token_artist.find(".flac") != std::string::npos) {
                        song_name = token_artist.substr(token_artist.find_last_of("\\") + 1);
                        song_name = song_name.substr(song_name.find('-') + 1, song_name.find(".flac") - song_name.find('-') - 1);
                        std::shared_ptr<AudioFile> flac_ptr = std::make_shared<FLAC>(token_artist,5);
                        Song song(song_name, artist_name, flac_ptr);
                        artist.addSong(song);
                        std::cout<<"Song: "<<song_name<<'\n';
                    } 
                    else if (token_artist.find(".mp3") != std::string::npos) {
                        song_name = token_artist.substr(token_artist.find_last_of("\\") + 1);
                        song_name = song_name.substr(song_name.find('-') + 1, song_name.find(".mp3") - song_name.find('-') - 1);
                        std::shared_ptr<AudioFile> mp3_ptr = std::make_shared<MP3>(token_artist,5);
                        Song song(song_name, artist_name, mp3_ptr);
                        artist.addSong(song);
                        std::cout<<"Song: "<<song_name<<'\n';
                    }
                    else if (token_artist.find(".ogg") != std::string::npos) {
                        song_name = token_artist.substr(token_artist.find_last_of("\\") + 1);
                        song_name = song_name.substr(song_name.find('-') + 1, song_name.find(".ogg") - song_name.find('-') - 1);
                        std::shared_ptr<AudioFile> ogg_ptr = std::make_shared<OGG>(token_artist,5);
                        Song song(song_name, artist_name, ogg_ptr);
                        artist.addSong(song);
                        std::cout<<"Song: "<<song_name<<'\n';
                    }
                }
                artists.push_back(artist);
            }
        }
    } catch (const is_not_directory& e) {
        std::cerr<<"Error: "<<e.what()<<std::endl;
    }

}

/////////////////////////////////////////////////
/// Program loop start
/////////////////////////////////////////////////

/**
 * @brief The loop of the program. The function handles the user-input.
 * @details This function creates a console-like environment for user interaction and processes commands 
 * to control the audio playback, manage playlists, and interact with loaded songs. It continuously runs 
 * until the user decides to exit, responding to commands for volume control, song playback, and queue management.
 * 
 * The available commands are:
 * 
 * - volume: Prints the current volume level.
 * - set-volume [int]: Sets the volume to a specified value.
 * - mute: Mutes the audio (sets the volume to 0).
 * - unmute: Unmutes the audio (restores the volume to the previous level).
 * 
 * - song-count: Prints the number of songs loaded.
 * - flac: Prints the songs with ".flac" extension.
 * - mp3: Prints the songs with ".mp3" extension.
 * - ogg: Prints the songs with ".ogg" extension.
 * 
 * - play-song [title]: Searches for and plays a specific song by title, if found.
 * - play-playlist [title]: Plays the playlist with the given title, if it exists.
 * - play-album [title]: Plays the album with the given title, if it exists.
 * 
 * - queue: Displays the current queue of songs.
 * - queue-play: Plays the first song in the queue and removes it from the queue.
 * - queue-add [n] [title]: Adds a song, album, or playlist to the queue. n: 1-song 2-album 3-playlist
 * - queue-remove [position]: Removes a song from the queue at the specified position.
 * - queue-clear: Clears the entire queue.
 * 
 * - create-playlist: Allows the user to create a new playlist and add songs to it.
 * - playlist-remove: Removes a song from a specified playlist.
 * 
 * - skip: Skips to the next song in the queue or pauses playback if the queue is empty.
 * - shuffle: Shuffles the order of the songs in the queue.
 * - pause: Pauses the currently playing music.
 * - resume: Resumes playback of paused music.
 * - stop: Stops the playback, ends the program, and waits for user input before exiting.
 */
void Player::start(){    
    while(1){
        std::cout<<"> ";
        std::cin>>c;
        
        c.erase(0, c.find_first_not_of(" \n\r\t"));
        c.erase(c.find_last_not_of(" \n\r\t") + 1);
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------    
        
        if(c=="help"){
            help();
        }        
        if(c=="volume"){
            std::cout<<"-> Volume: "<<volume<<'\n';
        }
        if(c=="set-volume"){
            int set_volume;
            std::cin>>set_volume;
            if(set_volume>=0 && set_volume<=100){
                volume = set_volume;
                Mix_VolumeMusic(volume);
                std::cout<<"-> Volume set to: "<<volume<<'\n';
            }
            else std::cout<<"(!) Volume should be in the interval 0-100!\n";
        }
        
        if(c=="mute"){
            Mix_VolumeMusic(0);
            std::cout<<"-> Muted!\n";
        }
        if(c=="unmute"){
            Mix_VolumeMusic(volume);
            std::cout<<"-> Unmuted, volume: "<<volume<<'\n';
        }
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------
 
        if(c=="song-count"){
            song_cnt();
        }
        if(c=="flac"){
            print_flac_songs();
        }
        if(c=="mp3"){
            print_mp3_songs();
        }
        if(c=="ogg"){
            print_ogg_songs();
        }        
        
        if(c=="play-song"){
            Song song_found = find_song();
            if(song_found.getTitle() != "--null"){
                play(song_found);
                current_song = song_found.getTitle();
                // std::cout<<song_found.getTitle()<<" was found!\n";
            }
            else std::cout<<"(!) Song not found.\n";
        }
        
        if(c=="play-playlist"){
            Playlist playlist_found = find_playlist();
            if(playlist_found.getName() != "--null"){
                clear_queue();
                play(playlist_found);
                std::cout<<playlist_found.getName()<<" was found!\n";
            }
            else std::cout<<"\n(!) Playlist not found!";
        }
        
        if(c=="play-album"){
            Album album_found = find_album();
            if(album_found.getName() != "--null"){
                clear_queue();
                play(album_found);
            }
            else std::cout<<"\n(!) Album not found!";
        }
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------
        
        if(c=="queue"){
            if(song_queue.empty()){
                std::cout<<"(!) Empty queue!"<<'\n';
            } else {
                int pos = 0;
                std::cout<<"-> Queue: \n";
                for(auto const &song : song_queue){
                    std::cout<<++pos<<": ";
                    std::cout<<song;
                }
            }
        }
        
        if (c == "queue-play" && !song_queue.empty()) {
            play(song_queue);
            song_queue.pop_front();
            sq = 1; 
        } else if (!song_queue.empty() && !Mix_PlayingMusic() && sq == 1) {
            play(song_queue);
            song_queue.pop_front();
        }
        
        if (song_queue.empty() && !Mix_PlayingMusic() && sq == 1) {
            sq = 0; 
            std::cout << "-> Queue is empty!\n";
        }
        
        if(c=="queue-add"){
            std::cout<<"-> Select number:\n1 - song      2 - album      3 - playlist\n";
            int option;
            std::cin>>option;
            if(option == 1){
                Song song_found = find_song();
                if(song_found.getTitle() != "--null"){
                    add_to_queue(song_found);
                }
                else std::cout<<"(!) Song wasn't found.";
                std::cout<<'\n';
            } else if(option == 2){
                Album album_found = find_album();
                if(album_found.getName() != "--null"){
                    add_to_queue(album_found);
                }
                else std::cout<<"\n(!) Album not found!";
            } else if(option == 3){
                Playlist playlist_found = find_playlist();
                if(playlist_found.getName() != "--null"){
                    add_to_queue(playlist_found);   
                }
                else std::cout<<"\n(!) Playlist not found!";
            }
            else break;
        }
        
        if(c=="queue-remove"){
            std::size_t q_cnt;
            std::cin>>q_cnt;
            q_cnt--;
            if(q_cnt <= song_queue.size()){
                remove_from_queue(q_cnt);
                std::cout<<"-> Song removed!\n";
            } else std::cout<<"(!) Invalid position!\n";
        }
        
        if(c=="queue-clear"){
            clear_queue();
            std::cout<<"-> Queue cleared.\n";
        }
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------
        
        if(c=="create-playlist"){
            std::string playlist_name;
            std::cout<<"Playlist name: ";
            std::cin.get();
            std::getline(std::cin, playlist_name, '\n');
            Playlist playlist(playlist_name,"rth");
            
            std::cout<<"-> Type: add song_name -> to add a song to the playlist.       Type: save -> to save & exit\n";
            std::string token;
            while(std::cin>>token){
                if(token == "add"){
                    Song song_found = find_song();
                    if(song_found.getTitle() != "--null"){
                        playlist.addSong(song_found);
                        std::cout<<"-> "<<song_found.getTitle()<<" was found & added!\n";
                        std::cout<<"-> Song number: "<<song_found.getCnt()<<'\n';
                    }
                } else if(token == "save") {
                    break;
                }
            }
            playlists.push_back(playlist);
            std::cout<<"-> Playlist "<<playlist<<" by "<<playlist.getCreatedBy()<<" created\n";
            playlist.showSongs();
        }
        
        if(c=="playlist-remove"){
            if(!playlists.empty()) {
                std::cout<<"Name: ";
                Playlist playlist_found = find_playlist();
                if(playlist_found.getName() != "--null") {
                    int position;
                    std::cout<<"-> Position: ";
                    std::cin >> position;
                    std::vector<Song> playlist_songs = playlist_found.getSongs();
                    std::cout<<"-> Song: "<<playlist_songs[position-1]<<"removed!\n";
                    playlist_found.removeSongPos(position-1);
                    }
                else {
                    std::cout<<"(!) Can't find playlist.\n";
                }
            }
            else {
                std::cout<<"(!) No playlists were created! Use: create-playlist\n";
            }
        }
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------
        
        if(c=="skip"){
            if(!song_queue.empty()){
                pause();
                play(song_queue);
                song_queue.pop_front();
            }
            else{
                pause();
            }
        }
        
        if(c=="shuffle"){
            shuffle(song_queue);
        }
        
        if(c=="pause"){
            pause();
        }
        if(c=="resume"){
            resume();
        }
        
        if(c=="stop"){
            if(Mix_PlayingMusic())
                pause();
            std::cout<<"\n\nAplication killed, press any key!\n";
            std::cin.get();
            std::cin.get();
            stop();
            break;
        }
    }    
}
/////////////////////////////////////////////////
/// Program loop end
/////////////////////////////////////////////////

/**
 * @brief This function handles the search of a song
 * @details This function inputs the title of the song and searches it by going throught each artist object and album object.
 * @note If the song is not found, the function returns a blank object with "--null" name. 
 * "--null" is used in start() to determine if a song really exists or not.
 *
 * @return Song 
 */
Song Player::find_song() {
    std::string song_name;
    std::cin.get();
    std::getline(std::cin, song_name, '\n'); 
    Song song_found;
    std::cout<<"-> Searching for song: "<<song_name<<"\n";

    for (const auto& artist : artists) {
        for (const auto& search_song : artist.getSongs()) {
            if (search_song.getTitle() == song_name) {
                //std::cout<<"Song found: "<<search_song.getTitle()<<"\n";
                return search_song; 
            }
        }
        for (const auto& album : artist.getAlbums()) {
            for (const auto& search_song : album.getSongs()) {
                if (search_song.getTitle() == song_name) {
                    //std::cout<<"Song found: "<<search_song.getTitle()<<"\n";
                    return search_song; 
                }
            }
        }
    }

    std::cout<<"(!) Song not found.\n";
    return song_found; 
}

Song Player::find_song(const std::string& song_name) {
    Song song_found;
    for (const auto& artist : artists) {
        for (const auto& search_song : artist.getSongs()) {
            if (search_song.getTitle() == song_name) {
                //std::cout<<"Song found: "<<search_song.getTitle()<<"\n";
                return search_song; 
            }
        }
        for (const auto& album : artist.getAlbums()) {
            for (const auto& search_song : album.getSongs()) {
                if (search_song.getTitle() == song_name) {
                    //std::cout<<"Song found: "<<search_song.getTitle()<<"\n";
                    return search_song; 
                }
            }
        }
    }

    std::cout<<"(!) Song not found.\n";
    return song_found; 
}

/**
 * @brief This function handles the search (by name) of a song 
 * @details This function inputs the name of a created playlist and searches it.
 * @note If the playlist is not found, the function returns a blank object with "--null" name.
 * "--null" is used in start() to determine if a playlist really exists or not.
 *
 * @return Song 
 */
Playlist Player::find_playlist(){
    Playlist playlist_found;
    std::string playlist_name;

    std::cin.get();
    std::getline(std::cin, playlist_name, '\n');
    if (!playlist_name.empty() && playlist_name.back() == '\n') {
        playlist_name.pop_back();
    }

    for (const auto& playlist : playlists) {
        if (playlist.getName() == playlist_name) {
            std::cout<<"-> Playlist found: "<<playlist.getName()<<"\n";
            playlist_found = playlist;
            return playlist_found;
        }
    }

    std::cout<<"(!) Playlist not found.\n";
    Playlist playlist_not_found;
    return playlist_not_found;
}

/**
 * @brief This function handles the search (by name) of an album 
 * @details This function inputs the name of a created playlist and searches it.
 * @note If the album is not found, the function returns a blank object with "--null" name. 
 * "--null" is used in start() to determine if an album really exists or not.
 *
 * @return Song 
 */
Album Player::find_album() {
    Album album_found;
    std::string album_name;

    std::cin.get();
    std::getline(std::cin, album_name, '\n');
    if (!album_name.empty() && album_name.back() == '\n') {
        album_name.pop_back();
    }


    for (const auto& artist : artists) {
        for (const auto& album : artist.getAlbums()) {
            if (album.getName() == album_name) {
                std::cout<<"Album found: "<<album.getName()<<"\n";
                album_found = album;
                return album_found;
            }
        }
    }

    std::cout<<"(!) Album not found.\n";
    Album album_not_found;
    return album_not_found;
}

/**
 * @brief This function adds a specified song by its title to the song_queue deque
 * @details Adds a song to the end of song_queue using push_back() method.
 * @param song 
 */
void Player::add_to_queue(const Song& song){
    std::cout<<song.getTitle()<<" queued.\n";
    song_queue.push_back(song);    
}
/**
 * @brief The function adds the songs of a specified album to the song_queue deque
 * @details By going through all the songs in the album, the function adds them to the end using push_back().
 * @param album 
 */
void Player::add_to_queue(const Album& album){
    for(const auto& song : album.getSongs())    
        add_to_queue(song);       
}
/**
 * @brief The function adds the songs of a playlist to the song_queue deque
 * @details By going through all the songs in the playlist, the function adds them to the end using push_back().
 * @param playlist 
 */
void Player::add_to_queue(const Playlist& playlist){
    for(const auto& song : playlist.getSongs())    
        add_to_queue(song);      
}

/**
 * @brief The function handles removes a specified position from the song_queue deque
 * @details The function checks if the position is in the range of the queue and deletes it 
 * using erase. If the position given is not in the queue, it prints an error message.
 *
 * @param position The position to be removed from the queue
 */
void Player::remove_from_queue(const std::size_t position){
    if (position < song_queue.size()) {
        auto it = song_queue.begin();
        std::advance(it, position);  
        song_queue.erase(it);
    } else {
        std::cerr<<"(!) Invalid position\n";
    }
}

/**
 * @brief Shuffles the song queue to randomize the order of songs.
 * @details This function generates a random seed based on the current system time, and uses 
 * it to shuffle the queue using `std::shuffle`. After shuffling, it outputs the contents of 
 * the queue to the console.
 * 
 * @param song_queue A reference to a `std::deque<Song>` that represents the queue of songs to be shuffled.
 */
void Player::shuffle(std::deque<Song> &song_queue) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(std::begin(song_queue), std::end(song_queue), rng);

    std::cout<<"-> Shuffle queue:\n";
    for (const auto& song : song_queue) {
        std::cout<<song;
    }
}

/**
 * @brief This function clears the queue of songs
 * @details This function calls remove_from_queue(0) until there are no more songs left.

 */
void Player::clear_queue(){
    while(song_queue.size()!=0){
        remove_from_queue(0);
    }
}

/**
 * @brief This function handles the playback of the first song in the queue
 * @note This function handles the error of not playing the audio file;
 * @param song_queue 
 */
void Player::play(const std::deque<Song> &song_queue) {
    try {
        if(Mix_PlayMusic(song_queue.front().getAudioFile()->file(), 2) == -1){
            throw check_playing();
        }
        std::cout<<"-> Playing: "<<song_queue.front();
    } catch (const check_playing& e) {
        std::cerr<<"(!) Error playing song: "<<e.what()<<std::endl;
    }
}

/**
 * @brief This function handles the playback of a specified song
 * @note This function handles the error of not playing the audio file;
 * @param song_queue 
 */
void Player::play(const Song& song){
    try {
        if(Mix_PlayMusic(song.getAudioFile()->file(), 2) == -1){
            throw check_playing();
        }
        std::cout<<"-> Playing: "<<song;
    } catch (const check_playing& e) {
        std::cerr<<"(!) Error playing song: "<<e.what()<<std::endl;
    }
}

/**
 * @brief Plays all songs from an album
 * @details This function clears the current queue, adds all songs from the specified album to the queue, 
 *          and then plays the queue.
 * 
 * @param album A constant reference to an `Album` object that represents the album whose songs are to be played.
 */
void Player::play(const Album& album){
    clear_queue();
    for(const auto& song : album.getSongs()){
        add_to_queue(song); 
    }
    play(song_queue);
    song_queue.pop_front();
}

/**
 * @brief Plays all songs from a playlist
 * @details This function clears the current queue, adds all songs from the specified playlist to the queue,
 *          and then plays the queue.
 * 
 * @param playlist A constant reference to a `Playlist` object that represents the playlist whose songs are to be played.
 */
void Player::play(const Playlist& playlist){
    clear_queue();
    for(const auto& song : playlist.getSongs()){
        add_to_queue(song); 
    }
    play(song_queue);
}

/**
 * @brief Pauses the currently playing music
 * @details This function pauses playback of the currently playing music using the audio library.
 */
void Player::pause() {
    Mix_PauseMusic();
}

/**
 * @brief Resumes the playback of the currently paused music
 * @details This function resumes playback of the music that was previously paused using the audio library.
 */
void Player::resume() {
    Mix_ResumeMusic();
}

/**
 * @brief Prints the number of songs available
 * @details This function prints the total number of songs managed by the `Song` object, decrementing by one 
 *          (likely due to a specific count requirement).
 */
void Player::song_cnt(){
        Song song;
        std::cout<<"-> Number of songs: "<<song.getCnt()-1<<'\n';
}

/**
 * @brief Prints all songs in FLAC format
 * @details This function iterates over all artists and their albums, printing each song that is in FLAC format.
 */
void Player::print_flac_songs(){
    for(const auto &artist : artists){
        for(const auto &song : artist.getSongs()){
            if(auto flac_pointer = std::dynamic_pointer_cast<FLAC>(song.getAudioFile()))
                std::cout<<song;
        }
        for(const auto &album : artist.getAlbums()){
            for(const auto &song : album.getSongs()){
                if(auto flac_pointer = std::dynamic_pointer_cast<FLAC>(song.getAudioFile()))
                std::cout<<song;
            }
        }
    }
}

/**
 * @brief Prints all songs in MP3 format
 * @details This function iterates over all artists and their albums, printing each song that is in MP3 format.
 */
void Player::print_mp3_songs(){
    for(const auto &artist : artists){
        for(const auto &song : artist.getSongs()){
            if(auto mp3_pointer = std::dynamic_pointer_cast<MP3>(song.getAudioFile())){
                std::cout<<song;
            }
        }
        for(const auto &album : artist.getAlbums()){
            for(const auto &song : album.getSongs()){
                if(auto mp3_pointer = std::dynamic_pointer_cast<MP3>(song.getAudioFile())){
                    std::cout<<song;
                }
            }
        }
    }
}

/**
 * @brief Prints all songs in OGG format
 * @details This function iterates over all artists and their albums, printing each song that is in OGG format.
 */
void Player::print_ogg_songs(){
    for(const auto &artist : artists){
        for(const auto &song : artist.getSongs()){
            if(auto ogg_pointer = std::dynamic_pointer_cast<OGG>(song.getAudioFile())){
                std::cout<<song;
            }
        }
        for(const auto &album : artist.getAlbums()){
            for(const auto &song : album.getSongs()){
                if(auto ogg_pointer = std::dynamic_pointer_cast<OGG>(song.getAudioFile())){
                    std::cout<<song;
                }
            }
        }
    }
}


void Player::help() const {
    std::cout << "\nCommands:\n";
    std::cout << "\n";
    std::cout << "volume - Prints the current volume level.\n";
    std::cout << "set-volume [int] - Sets the volume to a specified value.\n";
    std::cout << "mute - Mutes the audio (sets the volume to 0).\n";
    std::cout << "unmute - Unmutes the audio (restores the volume to the previous level).\n";
    std::cout << "\n";
    std::cout << "song-count - Prints the number of songs loaded.\n";
    std::cout << "flac - Prints the songs with \".flac\" extension.\n";
    std::cout << "mp3 - Prints the songs with \".mp3\" extension.\n";
    std::cout << "ogg - Prints the songs with \".ogg\" extension.\n";
    std::cout << "\n";
    std::cout << "play-song [title] - Searches for and plays a specific song by title, if found.\n";
    std::cout << "play-playlist [title] - Plays the playlist with the given title, if it exists.\n";
    std::cout << "play-album [title] - Plays the album with the given title, if it exists.\n";
    std::cout << "\n";
    std::cout << "queue - Displays the current queue of songs.\n";
    std::cout << "queue-play - Plays the first song in the queue and removes it from the queue.\n";
    std::cout << "queue-add - Adds a song, album, or playlist to the queue.\n";
    std::cout << "queue-remove [position] - Removes a song from the queue at the specified position.\n";
    std::cout << "queue-clear - Clears the entire queue.\n";
    std::cout << "\n";
    std::cout << "create-playlist - Allows the user to create a new playlist and add songs to it.\n";
    std::cout << "playlist-remove - Removes a song from a specified playlist.\n";
    std::cout << "\n";
    std::cout << "skip - Skips to the next song in the queue or pauses playback if the queue is empty.\n";
    std::cout << "shuffle - Shuffles the order of the songs in the queue.\n";
    std::cout << "pause - Pauses the currently playing music.\n";
    std::cout << "resume - Resumes playback of paused music.\n";
    std::cout << "stop - Stops the playback, ends the program, and waits for user input before exiting.\n";
    std::cout << "\n";
}

/**
 * @brief Stops playback and shuts down the audio system
 * @details This function closes the audio library, quits its operations, and de-initializes SDL.
 */
void Player::stop() const {
    std::ofstream sfout("state.txt");
    
    if(sfout.is_open()){
        sfout << volume <<'\n';
        sfout << current_song;
        sfout.close();
    }
    else {
        std::cout << "Can't open save file!\n";
    }
    
    sfout.close();
    
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}