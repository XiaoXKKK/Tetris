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
        std::pair<int, int> get_mino(int i, int next_idx = -1);
        std::pair<int, int> get_pos();
        int get_color();
        bool test(int x, int y, int next_idx = -1);
        Piece() = default;
        Piece(Tetromino& t, int x, int y, int index = 0);
        void set_playfield(std::shared_ptr<Matrix> sp);

        bool move(int dx, int dy);
        bool down();
        bool left();
        bool right();
        bool rotate();
    };
}