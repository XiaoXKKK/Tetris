#pragma once
#include "define.h"
#include "color.h"

using Tetromino_0 = std::vector<std::vector<int>>;

namespace gm {
    extern Tetromino_0 I, O, T, S, Z, J, L;

    extern Tetromino i, o, t, s, z, j, l;

    Tetromino_0 rotate(Tetromino_0 &t);

    extern std::map<int, Color> tetro_colors;
}