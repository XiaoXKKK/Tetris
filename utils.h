#pragma once

#include <string>

namespace ut {
    // Return the frames per second.
    int fps();
    // Convert a utf32 string to utf8.
    std::string utf32_to_utf8(const std::u32string &utf32);
}
