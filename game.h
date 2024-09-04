#pragma once 

#include "tetromino.h"
#include "piece.h"
#include "utils.h"
#include "draw.h"
#include "define.h"

namespace gm{
    extern bool running, locking;
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
    // lock the piece when it reaches the bottom
    void lock();
    // clear the full lines
    void clear();
    // key event
    void quit();
    void rotate();
    void down();
    void left();
    void right();
    void drop();
}