#include <iostream>
#include <array>
#include <Helper.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

class Song{
    private:
        std::string title;
        std::string genre;
        int duration;
    public:
        Song(){
            this->title = "null";
            this->genre = "null";
            this->duration = 0;
        }
        Song(const std::string& title, const std::string& genre){
            this->title = title;
            this->genre = genre;
            this->duration = 0;
        }
        Song(const std::string& title, const std::string& genre, const int duration){
            this->title = title;
            this->genre = genre;
            this->duration = duration;
        }
        ~Song(){}
        
        std::string getTitle() const { return this->title; }
        std::string getGenre() const { return genre; }
        int getDuration() const { return duration; }
        
        friend std::ostream& operator<<(std::ostream& os, const Song& auxSong){
            os << "Song name: "<<auxSong.title<<", genre: "<<auxSong.genre<<", and duration: "<<auxSong.duration<<'\n';
            return os;
        }
};

class Album{
    private:
        std::string name;
        std::string genre;
        std::vector<Song> songs;
    public:
        void addSong(const Song& song){
            songs.push_back(song);
        }
        
        Album(const std::string& name, const std::string& genre){
                this->name = name;
                this->genre = genre;
        }
        ~Album(){}
        
        std::string getName() const { return name; }
        std::string getGenre() const { return genre; }
        const std::vector<Song>& getSongs() const { return songs; }
        
        friend std::ostream& operator<<(std::ostream& os, const Album& auxAlbum){
            os << "Album Name: " << auxAlbum.name << ", Genre: " << auxAlbum.genre<<'\n';
            return os;
        }
};

class Artist{
    private:
        std::string name;
        std::string genre;
        std::vector<Album> albums;
        std::vector<Song> songs;
    public:
        void addAlbum(const Album& album){
            albums.push_back(album);
        }
        void addSong(const Song& song){
            songs.push_back(song);
        }
        
        
        Artist(const std::string& name, const std::string& genre){
            this->name = name;
            this->genre = genre;
        }
        ~Artist(){}
    
        std::string getName() const { return name; }
        std::string getGenre() const { return genre; }
        const std::vector<Album>& getAlbums() const { return albums; }
        const std::vector<Song>& getSongs() const { return songs; }
        
        friend std::ostream& operator<<(std::ostream& os, const Artist& artist){
            os << "Artist Name: " << artist.name << ", Genre: " << artist.genre<<'\n';
            return os;
        }
};

class Playlist{
    private:
        std::string name;
        std::string createdBy;
        std::vector<Song> songs;
    public:
        void addSong(const Song& song){
            songs.push_back(song);
        }
        void addAlbum(const Album& album){
            for(const auto& song : album.getSongs()){
                songs.push_back(song); 
            }
        }
        void removeSongPos(int x){
            songs.erase(songs.begin()+x);
        }
        void showSongs(){
            for(const auto& song : this->getSongs()){
                std::cout << song.getTitle() << "\n";
            }
        }
        
        Playlist(){
            this->name = "null";
            this->createdBy = "null";
        }
        Playlist(const std::string& name, const std::string& createdBy){
            this->name = name;
            this->createdBy = createdBy;
        }
        
        Playlist(const Playlist& CpyPlaylist){    /// COPY CONSTRUCTOR
            this->name = CpyPlaylist.name;
            this->createdBy = CpyPlaylist.createdBy;
            this->songs = CpyPlaylist.songs;
            std::cout<<"Copy constructor for playlist: "<<this->name<<std::endl;
        }
        
        ~Playlist(){
            std::cout<<"Destructor for playlist.\n";
        }
        
        Playlist& operator=(const Playlist& fPlaylist){ /// OP '='
            this->name = fPlaylist.name;
            this->createdBy = fPlaylist.createdBy;
            this->songs = fPlaylist.songs;
            std::cout<<" Succesfully '=' !\n";
            return *this;
        }
        
        std::string getName() const { return name; }
        std::string getCreatedBy() const { return createdBy; }
        const std::vector<Song>& getSongs() const { return songs; }
        
        friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist){
            os << "Playlist Name: " << playlist.name << ", created by: " << playlist.createdBy<<'\n';
            return os;
        }
};

class Player{
    private:
        std::string currentSong;
        int volume;
        Playlist playlist;
    public:
        Player(const std::string& currentSong, int volume){
            this->currentSong = currentSong;
            this->volume = volume;
        }
        
        Player(){
            this->currentSong = "null";
            this->volume = 0;
        }
        
        ~Player(){}
        
        std::string getCurrentSong() const { return currentSong; }
        int getVolume() const { return volume; }
        
        void shuffle(const Playlist& targetPlaylist) {
            std::vector<Song> shuffledSongs = targetPlaylist.getSongs();  // Use getter to access songs
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine rng(seed);
            std::shuffle(std::begin(shuffledSongs), std::end(shuffledSongs), rng);

            std::cout << "\n\nShuffle ON!\n";
            for (const auto& song : shuffledSongs) {
                std::cout << song;
            }
        }
};

int main(){
    
    std::ifstream fin("tastatura.txt");
    if (!fin.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1; 
    }
    
    std::string line;
    std::vector<Artist> artists;
    std::string name,genre;
    int artistCounter = -1, number;
    
    while(std::getline(fin,line)){
        std::stringstream ss(line);
        std::string type;
        std::getline(ss,type,':');
        
        if(type == "Artist"){
            std::getline(ss,name,',');
            std::getline(ss,genre);
            Artist artist(name,genre);
            artists.push_back(artist);
            artistCounter++;
        }
        
        if(type == "Album"){
            std::getline(ss,name,',');
            std::getline(ss,genre,',');
            std::string numberString;
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
            artists[artistCounter].addAlbum(album);
        }
        
        if(type == "Song"){
            std::string lengthString;
            std::getline(ss,name,',');
            std::getline(ss,genre,',');
            std::getline(ss,lengthString,'\n');
            Song song(name,genre);
            artists[artistCounter].addSong(song);
        }
    }
    
    for(const auto& artist : artists){
        std::cout << std::endl;
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
    
    Helper helper;
    helper.help();
    return 0;
}