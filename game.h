#pragma once 

namespace gm{
    extern bool running;
    extern int row, col;

    void init();

    void quit();
    void rotate();
    void down();
    void left();
    void right();
}