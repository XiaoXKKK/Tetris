#include "game.h"

namespace gm{
    bool running;
    int row, col;
    Tetromino cur;

    void init(){
        row = 2;
        col = 15;
        running = true;
        cur = J;
    }
    void quit(){
        running = false;
    }
    void rotate(){
        cur = rotate(cur);
    }
    void down(){
        row++;
    }
    void left(){
        col--;
    }
    void right(){
        col++;
    }
}