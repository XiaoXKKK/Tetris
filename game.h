#pragma once 

#include "tetromino.h"

namespace gm{
    extern bool running;
    extern int row, col;
    extern Tetromino_0 cur;
    extern Tetromino cur_s;
    extern int index;

    void init();

    void quit();
    void rotate();
    void down();
    void left();
    void right();
}