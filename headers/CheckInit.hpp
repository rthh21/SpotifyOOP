#ifndef CHECKINIT_HPP
#define CHECKINIT_HPP

#include <string>
#include "Exceptions.hpp"

class check_init : public AudioExceptions {
private:
    std::string message;
public:
    explicit check_init(std::string msg);

    virtual const char* what() const noexcept override;
};

#endif