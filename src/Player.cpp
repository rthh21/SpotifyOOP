#include <string>
#include "Player.hpp"
#include "Song.hpp"
#include "AudioFile.hpp"
#include "flac.hpp"
#include "mp3.hpp"

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
 
void Player::start(){
    int sq = 0; // status queue
    
    //melodii
    std::shared_ptr<AudioFile> type1 = std::make_shared<FLAC>("music/stargazing.flac", 5);
    Song song1("Stargazing","rap",type1);
    std::shared_ptr<AudioFile> type2 = std::make_shared<MP3>("music/fein.mp3", 5);
    Song song2("FE!N","rap",type2);
    add_to_queue(song1);
    add_to_queue(song2);
    
    //start loop
    while(1){
        std::string c;
        std::cout<<"> ";
        std::cin>>c;
        
        c.erase(0, c.find_first_not_of(" \n\r\t"));
        c.erase(c.find_last_not_of(" \n\r\t") + 1);
        
        if(c=="play-queue" && !song_queue.empty()){
            play(song_queue);
            song_queue.pop_front();
            sq = 1;
        }
        if(!song_queue.empty() && !Mix_PlayingMusic() && sq == 1){
            play(song_queue);
            song_queue.pop_front();
        }
        if(song_queue.empty()){
            sq = 1;
        }
        
        if(c=="skip"){
            if(!song_queue.empty()){
                pause();
                play(song_queue);
                song_queue.pop_front();
            }
            else{
                pause();
                std::cout<<"Queue empty!\n";
            }
        }
        
        if(c=="pause"){
            pause();
        }
        if(c=="resume"){
            resume();
        }
        
        if(c=="queue"){
            int pos = 0;
            std::cout<<"Queue: \n";
            for(auto& song : song_queue){
                std::cout<<++pos<<": ";
                std::cout<<song;
            }
        }
        if(c=="break"){
            std::cout<<"\n\n Aplication killed, press any key!\n";
            std::cin.get();
            std::cin.get();
            break;
        }
    }    
}
 
 
int Player::queue_status(){
    if(song_queue.empty()) {
        return -1;
    }
    return 1;
}

void Player::add_to_queue(Song& song){
    std::cout << "Adding song: " << song.getTitle() << std::endl;
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
    if (position < song_queue.size()) {
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

void Player::play(std::deque<Song> &song_queue){
    Mix_PlayMusic(song_queue.front().getAudioFile()->file(),2);   
}

void Player::pause(){
    Mix_PauseMusic();
}
void Player::resume(){
    Mix_ResumeMusic();
}