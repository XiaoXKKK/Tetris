#pragma once
#include "define.h"
#include "color.h"

using Tetromino_0 = std::vector<std::vector<int>>;

namespace gm {
    [[deprecated("Use Tetromino instead")]]extern Tetromino_0 I, O, T, S, Z, J, L; // deprecated

    extern Tetromino i, o, t, s, z, j, l;

    extern Offset offset, offset_i, offset_o;

    [[deprecated]]Tetromino_0 rotate(Tetromino_0 &t);

    extern std::map<int, Color> tetro_colors;
}