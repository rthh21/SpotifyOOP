#ifndef CHECKDIRECTORY_HPP
#define CHECKDIRECTORY_HPP

#include <string>
#include "Exceptions.hpp"

//used in load_songs() in Player.cpp
class is_not_directory : public AudioExceptions{
private:
    std::string message;
public:
    explicit is_not_directory(const std::string& path);
    
    virtual const char* what() const noexcept override;
};

#endif