#include <iostream>
#include <array>
#include <Helper.h>
#include <vector>
#include <cstring>
#include <fstream>
#include "Song.hpp"
#include "Album.hpp"
#include "Artist.hpp"
#include "Playlist.hpp"
#include "Player.hpp"

#define SDL_MAIN_HANDLED // fix pentru "main"

#include "SDL.h"
#include "SDL_mixer.h"

int main(){

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init(SDL_INIT_AUDIO) failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (Mix_Init(MIX_INIT_FLAC) == 0) {
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

    const char* filename = "music/stargazing.flac";
    Mix_Music* music = Mix_LoadMUS(filename);
    if (!music) {
        std::cerr << "Mix_LoadMUS failed: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return -1;
    }

    if (Mix_PlayMusic(music, -1) == -1) {
        std::cerr << "Mix_PlayMusic failed: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return -1;
    }

    std::cout << "Playing FLAC file. Press any key to quit...\n";
    std::cin.get();

    // Clean up and quit
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

//----------------------------------------------------------------------------------
    std::ifstream fin("tastatura.txt");
    if (!fin.is_open()) {
        std::cerr << "Error: Could not open the file." << '\n';
        return -1; 
    }
    
    std::vector<Artist> artists;
    std::vector<Playlist> playlists;
    Player player(50);
    
    std::string line;
    while(std::getline(fin,line)){
        std::stringstream ss(line);
        std::string type;
        std::getline(ss,type,':');
        
        if(type == "Artist"){
            std::string name, genre;
            std::getline(ss,name,',');
            std::getline(ss,genre);
            Artist artist(name,genre);
            artists.push_back(artist);
        }
        
        if(type == "Album"){
            std::string name, genre;
            std::getline(ss,name,',');
            std::getline(ss,genre,',');
            std::string numberString;
            int number;
            std::getline(ss,numberString);
            number = std::stoi(numberString);
            
            Album album(name,genre);
            
            for(int i = 0; i < number; i++){
                std::getline(fin,line);
                std::stringstream sss(line); // sss = ss song
                std::getline(sss,name,',');
                Song song(name,genre);
                album.addSong(song);
            }
            artists.back().addAlbum(album);
        }
        
        if(type == "Song"){
            std::string name, genre, lengthString;
            std::getline(ss,name,',');
            std::getline(ss,genre,',');
            std::getline(ss,lengthString,'\n');
            Song song(name,genre);
            artists.back().addSong(song);

        }
        
        if(type == "Playlist"){
            std::string name;
            std::getline(ss,name,':');
            Playlist playlist(name,"rthh");
            while(std::getline(fin,line)){  
                std::stringstream ssp(line);
                int nrArtist;
                std::string aux;
                std::getline(ssp,aux,':');
                nrArtist = std::stoi(aux)-1;
                if(line.find('-') != std::string::npos){  
                    int nrAlbum;
                    std::getline(ssp,aux,'-');
                    nrAlbum = std::stoi(aux) - 1;
                    std::vector<Album> auxA = artists[nrArtist].getAlbums();
                    std::vector<Song> auxS = auxA[nrAlbum].getSongs();
                    while(std::getline(ssp,aux,',')){
                        int nrSong;
                        nrSong = std::stoi(aux) - 1;
                        playlist.addSong(auxS[nrSong]);
                    }
                } else {
                    std::vector<Song> auxA = artists[nrArtist].getSongs();
                    while(std::getline(ssp,aux,',')){
                        int nrSong;
                        nrSong = std::stoi(aux) - 1;
                        playlist.addSong(auxA[nrSong]);
                    }
                }
            }
            playlists.push_back(playlist);
        }  
    }
    

    for(const auto& artist : artists){
        std::cout << '\n';
        std::cout << artist;
        for(const auto& album : artist.getAlbums()){
            std::cout << "   " << album;
            for(const auto& song : album.getSongs()){
                std::cout << "      " << song;
            }
        }
        for(const auto& song : artist.getSongs()){
            std::cout << "   " << song;
        }
    }
    std::cout << "----------------------------\nPlaylist: " << playlists[0].getName() << " by " << playlists[0].getCreatedBy() << '\n';
    playlists[0].showSongs();
    player.shuffle(playlists[0]);
    std::cout << "\nPlaylist: "<< playlists[0].getName() << '\n';
    playlists[0].removeSongPos(1);
    playlists[0].showSongs();        
    
    std::cout << "\nVolum: " << player.getVolume();
    
    Song songtest("test","test");
    Album albumtest("test","jazz");
    std::cout << "getGenre: " << albumtest.getGenre() << '\n';
    
    Helper helper;
    helper.help();
    return 0;
}