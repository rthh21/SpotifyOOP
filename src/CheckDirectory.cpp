#include "CheckDirectory.hpp"

is_not_directory::is_not_directory(const std::string& path) : message("Can't find path: " + std::move(path)) {}

const char* is_not_directory::what() const noexcept { 
    return message.c_str();
}