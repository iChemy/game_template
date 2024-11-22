#include <iostream>
#include "def.hpp"
#include "stream.hpp"

std::ostream& operator<<(std::ostream& os, const player& p) {
    switch (p)
    {
    case player::RED:
        os << "RED";
        break;
    case player::BLUE:
        os << "BLUE";
    default:
        break;
    }

    return os;
}