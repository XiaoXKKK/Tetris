#pragma once

#include "define.h"

namespace ut {
    // Return the frames per second.
    int fps();
    // Convert a utf32 string to utf8.
    std::string utf32_to_utf8(const std::u32string &utf32);
    // 
    inline int b2c(int block){
        return block * 2 - 1;
    }
    bool timer(std::chrono::milliseconds ms);
}
