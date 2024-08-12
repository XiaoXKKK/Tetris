#include "game.h"

namespace gm{
    bool running;
    int row, col;

    void init(){
        row = 2;
        col = 15;
        running = true;
    }
    void quit(){
        running = false;
    }
    void rotate(){
        row--;
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