#include "BA/Exceptions/Inaccessible.hpp"

namespace ba {

Inaccessible::Inaccessible(const std::string& msg)
    : std::runtime_error(msg) {

}

Inaccessible::Inaccessible(const char* msg)
    : std::runtime_error(msg) {

}

}