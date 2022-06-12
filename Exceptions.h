#pragma once

#include <exception>

class InvalidPositionException : public std::exception {
public:
    const char *what() const throw();
};
