#pragma once
#include "define.h"
#include "color.h"

using Tetromino = std::vector<std::vector<int>>;
namespace gm{
    extern Tetromino I, O, T, S, Z, J, L;

    Tetromino rotate(Tetromino &t);

    extern std::map<int, Color> tetro_colors;
}