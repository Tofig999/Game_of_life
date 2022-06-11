#include "Exceptions.h"


const char *InvalidPositionException::what() const throw() {
    return "Invalid row or column.";
}
