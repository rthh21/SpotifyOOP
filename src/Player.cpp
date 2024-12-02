#include "Player.hpp"
#include "AudioFile.hpp"
#include "flac.hpp"
#include "mp3.hpp"
#include "ogg.hpp"

#include "Exceptions.hpp"
#include "CheckDirectory.hpp"
#include "CheckInit.hpp"
#include "CheckPlaying.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>
namespace fs = std::filesystem;



std::deque<Song> Player::song_queue;

Player::Player() : volume(0) {}

Player::Player(int volume) : volume(volume) {}

Player::~Player() {}

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

    load_files();
}
 
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
 
void Player::start(){
    int sq = 0; // status queue
    
    //start loop
    while(1){
        std::string c;
        std::cout<<"> ";
        std::cin>>c;
        
        c.erase(0, c.find_first_not_of(" \n\r\t"));
        c.erase(c.find_last_not_of(" \n\r\t") + 1);
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------
        
        //test
        if(c=="test"){
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
        //test
        
        if(c=="play-song"){
            Song song_found = find_song();
            if(song_found.getTitle() != "--null"){
                play(song_found);
                // std::cout<<song_found.getTitle()<<" was found!\n";
            }
            else std::cout<<"Song not found.\n";
        }
        
        if(c=="play-playlist"){
            Playlist playlist_found = find_playlist();
            if(playlist_found.getName() != "--null"){
                clear_queue();
                play(playlist_found);
                std::cout<<playlist_found.getName()<<" was found!\n";
            }
            else std::cout<<"\nPlaylist not found!";
        }
        
        if(c=="play-album"){
            Album album_found = find_album();
            if(album_found.getName() != "--null"){
                clear_queue();
                play(album_found);
            }
            else std::cout<<"\nAlbum not found!";
        }
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------
        
        if(c=="queue"){
            if(song_queue.empty()){
                std::cout<<"Empty queue!"<<'\n';
            } else {
                int pos = 0;
                std::cout<<"Queue: \n";
                for(auto const &song : song_queue){
                    std::cout<<++pos<<": ";
                    std::cout<<song;
                }
            }
        }
        if(c=="queue-play" && !song_queue.empty()){
            play(song_queue);
            song_queue.pop_front();
            sq = 1;
        } else if(!song_queue.empty() && !Mix_PlayingMusic() && sq == 1){
            play(song_queue);
            song_queue.pop_front();
        }
        if(song_queue.empty() && Mix_PlayingMusic() && sq == 1){
            sq = 0;
            std::cout<<"Queue is empty!\n";
        }
        
        if(c=="queue-add"){
            std::cout<<"Select number:\n1 - song      2 - album      3 - playlist\n";
            int option;
            // std::string token;
            std::cin>>option;
            if(option == 1){
                Song song_found = find_song();
                if(song_found.getTitle() != "--null"){
                    add_to_queue(song_found);
                }
                else std::cout<<"Song wasn't found.";
                std::cout<<'\n';
            } else if(option == 2){
                Album album_found = find_album();
                if(album_found.getName() != "--null"){
                    add_to_queue(album_found);
                }
                else std::cout<<"\nAlbum not found!";
            } else if(option == 3){
                Playlist playlist_found = find_playlist();
                if(playlist_found.getName() != "--null"){
                    add_to_queue(playlist_found);   
                }
                else std::cout<<"\nPlaylist not found!";
            }
            else break;
        }
        
        if(c=="queue-remove"){
            std::size_t q_cnt;
            std::cin>>q_cnt;
            q_cnt--;
            if(q_cnt <= song_queue.size()){
                remove_from_queue(q_cnt);
                std::cout<<"Song removed!\n";
            } else std::cout<<"Invalid position!\n";
        }
        
        if(c=="queue-clear"){
            clear_queue();
            std::cout<<"Queue cleared.\n";
        }
        
        //---------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------
        
        if(c=="create-playlist"){
            std::string playlist_name;
            std::cout<<"Playlist name: ";
            std::cin.get();
            std::getline(std::cin, playlist_name, '\n');
            Playlist playlist(playlist_name,"rth");
            
            std::cout<<"Type: add song_name -> to add a song to the playlist.       Type: save -> to save & exit\n";
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
                    std::cout<<"Position: ";
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
 
Song Player::find_song() {
    std::string song_name;
    std::cin.get();
    std::getline(std::cin, song_name, '\n'); 
    Song song_found;
    std::cout<<"Searching for song: "<<song_name<<"\n";

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
            std::cout<<"Playlist found: "<<playlist.getName()<<"\n";
            playlist_found = playlist;
            return playlist_found;
        }
    }

    std::cout<<"Playlist not found.\n";
    Playlist playlist_not_found;
    return playlist_not_found;
}

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

    std::cout<<"Album not found.\n";
    Album album_not_found;
    return album_not_found;
}

void Player::add_to_queue(const Song& song){
    std::cout<<song.getTitle()<<" queued.\n";
    song_queue.push_back(song);    
}
void Player::add_to_queue(const Album& album){
    for(const auto& song : album.getSongs())    
        add_to_queue(song);       
}
void Player::add_to_queue(const Playlist& playlist){
    for(const auto& song : playlist.getSongs())    
        add_to_queue(song);      
}

void Player::remove_from_queue(const std::size_t position){
    if (position < song_queue.size()) {
        auto it = song_queue.begin();
        std::advance(it, position);  
        song_queue.erase(it);
    } else {
        std::cerr<<"Invalid position\n";
    }
}

void Player::shuffle(std::deque<Song> &song_queue) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(std::begin(song_queue), std::end(song_queue), rng);

    std::cout<<"Shuffle queue:\n";
    for (const auto& song : song_queue) {
        std::cout<<song;
    }
}

void Player::clear_queue(){
    while(song_queue.size()!=0){
        remove_from_queue(0);
    }
}

void Player::play(const std::deque<Song> &song_queue) {
    try {
        if(Mix_PlayMusic(song_queue.front().getAudioFile()->file(), 2) == -1){
            throw check_playing();
        }
        std::cout<<"Playing: "<<song_queue.front();
    } catch (const check_playing& e) {
        std::cerr<<"Error playing song: "<<e.what()<<std::endl;
    }
}

void Player::play(const Song& song){
    try {
        if(Mix_PlayMusic(song.getAudioFile()->file(), 2) == -1){
            throw check_playing();
        }
        std::cout<<"Playing: "<<song;
    } catch (const check_playing& e) {
        std::cerr<<"Error playing song: "<<e.what()<<std::endl;
    }
}
void Player::play(const Album& album){
    clear_queue();
    for(const auto& song : album.getSongs()){
        add_to_queue(song); 
    }
    play(song_queue);
}
void Player::play(const Playlist& playlist){
    clear_queue();
    for(const auto& song : playlist.getSongs()){
        add_to_queue(song); 
    }
    play(song_queue);
}

void Player::pause() {
    Mix_PauseMusic();
}
void Player::resume() {
    Mix_ResumeMusic();
}

void Player::song_cnt(){
        Song song;
        std::cout<<"Number of songs: "<<song.getCnt()-1<<'\n';
}

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

void Player::stop() const {
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}