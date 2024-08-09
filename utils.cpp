#include "utils.h"

#include <chrono>
using namespace std::chrono_literals;

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