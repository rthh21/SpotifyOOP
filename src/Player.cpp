#include <thread>
#include "Player.hpp"
#include "Song.hpp"
#include "SDL.h"
#include "SDL_mixer.h"

std::deque<Song> Player::song_queue;

Player::Player() : volume(0) {}

Player::Player(int volume) : volume(volume) {}

Player::~Player() {}

int Player::init() const{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init(SDL_INIT_AUDIO) failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    if (Mix_Init(MIX_INIT_FLAC) == 0 || Mix_Init(MIX_INIT_MP3) == 0) {
        std::cerr << "Mix_Init failed: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
        Mix_Quit();
        SDL_Quit();
        return -1;
    }   

    return 0;
}

void Player::add_to_queue(Song& song){
    song_queue.push_back(song);    
}
void Player::add_to_queue(Album& album){
    for(const auto& song : album.getSongs())    
        song_queue.push_back(song);       
}
void Player::add_to_queue(Playlist& playlist){
    for(const auto& song : playlist.getSongs())    
        song_queue.push_back(song);       
}

void Player::remove_from_queue(std::size_t position){
    if (position >= 0 && position < song_queue.size()) {
        auto it = song_queue.begin();
        std::advance(it, position);  
        song_queue.erase(it);
    } else {
        std::cerr << "Invalid position\n";
    }
}

//test
// void Player::play_queue(){
//     std::thread audioThread(&Player::play_queue1, this);
//     audioThread.detach();
// }

void Player::play_queue(){
    while(!song_queue.empty()){
        song_queue.front().play();
        song_queue.pop_front();
    }
}

void Player::shuffle(const Playlist& targetPlaylist) {
    int i = 0;
    std::vector<Song> shuffledSongs = targetPlaylist.getSongs();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(std::begin(shuffledSongs), std::end(shuffledSongs), rng);

    std::cout << "\n\nShuffle ON!\n";
    for (const auto& song : shuffledSongs) {
        i++;
        std::cout << i << ". " << song.getTitle() << '\n';
    }
}

void Player::play(Song& song){
    song.play();
}

void Player::pause(){
    Mix_Pause(2);
}
void Player::resume(){
    Mix_Resume(2);
}