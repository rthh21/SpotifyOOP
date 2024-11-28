#ifndef CHECKPLAYING_HPP
#define CHECKPLAYING_HPP

#include <string>
#include "Exceptions.hpp"

class check_playing : public AudioExceptions {
private:
    std::string message;
public:
    check_playing();
    
    virtual const char* what() const noexcept override;
};

#endif