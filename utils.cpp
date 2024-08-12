#include "utils.h"
#include "define.h"

int ut::fps()
{
    static auto start = std::chrono::steady_clock::now();
    auto end = start;
    static int frames = 0;
    static int fps = 0;

    end = std::chrono::steady_clock::now();
    frames++;
    if (end - start >= 1s)
    {
        fps = frames;
        frames = 0;
        start = end;
    }
    return fps;
}

std::string ut::utf32_to_utf8(const std::u32string &utf32)
{
    static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.to_bytes(utf32);
}