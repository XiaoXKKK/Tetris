#pragma once 
#include "define.h"
#include <fstream> 
#include <string> 

namespace lg {
    extern std::fstream file; 

    void log(std::string msg);

    void log(Matrix& m);
}