#include "Player.hpp"

Player::Player() : volume(0) {}

Player::Player(int volume) : volume(volume) {}

Player::~Player() {}

const int& Player::getVolume() const {
    return volume;
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
