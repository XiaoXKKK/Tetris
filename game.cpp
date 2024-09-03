#include "game.h"

namespace gm{
    bool running;
    int row, col;
    Tetromino_0 cur;
    Tetromino cur_s;
    int index;

    void init(){
        row = 2;
        col = 15;
        running = true;
        cur = J;
        cur_s = i;
    }
    void quit(){
        running = false;
    }
    void rotate(){
        //cur = rotate(cur);
        index = (index + 1) % 4;
    }
    void down() {
        row++;
    }
    void left(){
        col--;
    }
    void right(){
        col++;
    }
}