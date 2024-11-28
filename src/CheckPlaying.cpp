#include "CheckPlaying.hpp"

check_playing::check_playing() : message("Can't play audio file!") {}

const char* check_playing::what() const noexcept { 
    return message.c_str();
}