#pragma once 
#include "tetromino.h"
#include "define.h"

namespace gm {
    class Piece
    {
    private:

        Tetromino tetro_set;
        int x, y;
        int index;// [0, R, 2, L]
        std::shared_ptr<Matrix> sp_playfield;
    public:
        std::pair<int, int> get_mino(int i);
        std::pair<int, int> get_pos();
        int get_color();
        bool test(int x, int y, int index);
        Piece() = default;
        Piece(Tetromino& t, int x, int y, int index);
        void set_playfield(Matrix& m) { sp_playfield = std::make_shared<Matrix>(m); }

        void move(int dx, int dy);
        void down();
        void left();
        void right();
        void rotate();
    };
}