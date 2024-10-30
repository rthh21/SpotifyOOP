#include <iostream>
#include <array>
#include <Helper.h>
#include <vector>
#include <cstring>

class Song{
    public:
        std::string title;
        std::string genre;
        int duration;
        
        Song(){
            this->title = "null";
            this->genre = "null";
            this->duration = 0;
        }
        
        Song(const std::string title, const std::string genre, const int duration){
            this->title = title;
            this->genre = genre;
            this->duration = duration;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Song& song){
            os << "Song name: "<<song.title<<", genre: "<<song.genre<<", and duration: "<<song.duration;
            return os;
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
        
        void addSongInAlbum(const Song &song){
            songs.push_back(song);
        }   
        
        friend std::ostream& operator<<(std::ostream& os, const Album& album) {
        os << "Album Name: " << album.name << ", Genre: " << album.genre;
        return os;
    }
};

class Artist{
    public:
        std::string name;
        std::string genre;
        std::vector<Album> albums;
        std::vector<Song> songs;
        
        Artist(const std::string name, const std::string genre){
            this->name = name;
            this->genre = genre;
        }
        
        void addAlbum(const Album& album){
            albums.push_back(album);
        }
        
        void addSongToArtist(const Song& song){
            songs.push_back(song);
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Artist& artist){
            os << "Artist Name: " << artist.name << ", Genre: " << artist.genre;
            return os;
        }
};

class Playlist{
    private:
        std::vector<Song> songs;
    public:
        std::string name;
        std::string createdBy;
    
    //constructor
    Playlist(){
        this->name = "null";
        this->createdBy = "null";
    }
    
    Playlist(const std::string name, const std::string createdBy){
        this->name = name;
        this->createdBy = createdBy;
    }
    
    //contructor copy
    Playlist(const Playlist& CpyPlaylist){
        this->name = CpyPlaylist.name;
        this->createdBy = CpyPlaylist.createdBy;
        this->songs = CpyPlaylist.songs;
        std::cout<<"Copy constructor for playlist: "<<this->name<<std::endl;
    }
    
    //destructor
    ~Playlist(){
        std::cout<<"Destructor for playlist.\n";
    }
    
    //Operator '='
    Playlist& operator=(const Playlist& fPlaylist){
        this->name = fPlaylist.name;
        this->createdBy = fPlaylist.createdBy;
        this->songs = fPlaylist.songs;
        std::cout<<" Succesfully '=' !\n";
        return *this;
    }
    
    void addSongInPlaylist(const Song& song){
        songs.push_back(song);
    }
    void removeSongPosInPlaylist(int x){
        songs.erase(songs.begin()+x);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist){
        os << "Playlist Name: " << playlist.name << ", Genre: " << playlist.createdBy;
        return os;
    }
};

int main() {
    std::cout<<"Type 'exit' to end the program.";
    std::string token;
    
    while (1) {
        std::cout<<"\n> ";
        std::getline(std::cin, token);
        
        if (token.find("exit") != std::string::npos) 
            break;
        
        if(token.find("new") != std::string::npos){
            //TODO
            if(token.find("song") != std::string::npos){
                std::string title, genre;
                int duration;
                std::cout<<"\nEnter song title: ";
                std::getline(std::cin, title);
                std::cout<<"Enter song genre: ";
                std::getline(std::cin, genre);
                std::cout<<"Enter song duration: ";
                std::cin>>duration;
                Song song1(title,genre,duration);
                std::cout<<song1;
            }
            //TODO
        }
    }
    
    Helper helper;
    helper.help();
    
    return 0;
}
