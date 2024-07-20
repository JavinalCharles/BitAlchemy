#pragma once

#include <stdexcept>

namespace ba {

class Inaccessible : public std::runtime_error {
public:
    Inaccessible(const std::string& msg);
    Inaccessible(const char* msg);

};
   
}