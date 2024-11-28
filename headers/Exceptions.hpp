#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class AudioExceptions : public std::exception{
public:
    virtual const char* what() const noexcept override;
};

#endif