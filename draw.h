# pragma once

#include "define.h"
#include "tetromino.h"

namespace dw {
    void window(int top, int left, int weight, int height, std::string title);
    void tetromino(Tetromino &t, int top, int left);
}