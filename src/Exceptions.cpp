#include "Exceptions.hpp"
#include <string>

const char* AudioExceptions::what() const noexcept {
        return "Audio exception";
}