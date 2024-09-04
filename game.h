#pragma once 

#include "tetromino.h"
#include "piece.h"
#include "utils.h"
#include "draw.h"

namespace gm{
    extern bool running;
    extern Piece one_piece;
    extern Matrix playfield;
    extern std::chrono::milliseconds duration;
    extern Matrix frame;

    // extern int row, col;
    // extern Tetromino_0 cur;
    // extern Tetromino cur_s;
    // extern int index;

    // init game
    void init();
    // render game
    void render();
    // process game
    void process();
    // pick a piece
    Piece pick();
    // key event
    void quit();
    void rotate();
    void down();
    void left();
    void right();
}