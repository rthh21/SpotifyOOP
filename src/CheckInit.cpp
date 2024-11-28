#include "CheckInit.hpp"

check_init::check_init(std::string msg) : message("Init failed! => " + std::move(msg)) {}

const char* check_init::what() const noexcept { 
    return message.c_str();
}