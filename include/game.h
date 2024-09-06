#pragma once 

#include "tetromino.h"
#include "piece.h"
#include "utils.h"
#include "draw.h"
#include "define.h"
#include "control.h"
#include "window.h"

namespace gm{
    extern bool running, locking, holding, end, helping, reseting;
    extern Piece one_piece;
    extern Matrix playfield;
    extern std::chrono::milliseconds duration;
    extern Matrix frame;
    extern std::queue<Tetromino> next_pieces;
    extern Tetromino hold_piece;
    extern int score;
    extern int level;
    extern int lines;
    extern int t_spin;
    extern std::random_device rd;
    extern std::mt19937 g;
    extern int b2b, combo;

    // extern int row, col;
    // extern Tetromino_0 cur;
    // extern Tetromino cur_s;
    // extern int index;

    // init game
    void init();
    // render a frame
    void render();
    // code reuse
    void merge(Matrix &m, Piece &p, bool check = false);
    // process game
    void process();
    // pick a piece
    Piece pick();
    // preview the next 5 pieces
    void preview();
    // lock the piece when it reaches the bottom
    void lock();
    // clear the full lines
    void clear();
    // level up
    void levelup();
    // key event
    void hold();
    void quit();
    void rotate(int i);
    void down();
    void left();
    void right();
    void drop();
    void help();
    void reset();
}