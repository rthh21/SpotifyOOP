#include <iostream>
#include <array>
#include <Helper.h>

class Song{
    public:
        std::string title;
        std::string genre;
        int duration;
        
        Song(const std::string title, const std::string genre, const int duration){
            this->title = title;
            this->genre = genre;
            this->duration = duration;
        }
};

class Album{
    public:
        std::string name;
        std::string genre;
        std::vector<Song> songs;
        
        Album(const std::string name, const std::string genre){
            this->name = name;
            this->genre = genre;
        }
        
        void songAdd(const Song &song){
            songs.push_back(song);
        }      
};

class Artist{
    public:
        std::string name;
        std::string genre;
        std::vector<Album> albums;
        
        Artist(const std::string name, const std::string genre){
            this->name = name;
            this->genre = genre;
        }
        
        void albumAdd(const Album& album){
            albums.push_back(album);
        }
};


int main() {
    
    Artist artist1("Travis Scott", "RAP");
    
    Helper helper;
    helper.help();
    
    return 0;
}
