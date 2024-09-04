#include "piece.h"

namespace gm {
    std::pair<int, int> Piece::get_mino(int i, int next_idx)
    {
        assert(i >= 0 && i < 4);
        if (i == 0) return std::pair<int, int>(0, 0);
        if (next_idx == -1)
            return tetro_set[index][i];
        else 
            return tetro_set[next_idx][i];
    }

    std::pair<int, int> Piece::get_pos()
    {
        return std::pair<int, int>(x, y);
    }

    int Piece::get_color()
    {
        return tetro_set[index][0].second;
    }

    Piece::Piece(Tetromino& t, int x, int y, int index) : tetro_set(t), x(x), y(y), index(index)
    {
    }

    void Piece::set_playfield(std::shared_ptr<Matrix> sp)
    {
        sp_playfield = sp;
    }

    bool Piece::move(int dx, int dy)
    {
        if (test(x + dx, y + dy, index)) {
            x += dx;
            y += dy;
            return true;
        }
        return false;
    }

    bool Piece::down()
    {
        return move(0, -1);
    }

    bool Piece::left()
    {
        return move(-1, 0);
    }

    bool Piece::right()
    {
        return move(1, 0);
    }

    bool Piece::rotate()
    {
        // TODO: check if the rotation is valid
        int next_idx = (index + 1) % 4;
        if (test(x, y, next_idx)) {
            index = next_idx;
            return true;
        }
        return false;
    }

    bool Piece::test(int x, int y, int index)
    {
        for (int i = 0;i < 4;i++) {// Bug Fixed 
            auto [dx, dy] = get_mino(i, index);
            // check if the piece is out of bounds
            if (x + dx < 0 || x + dx >= (*sp_playfield)[0].size() \
                || y + dy < 0 || y + dy >= (*sp_playfield).size()) {
                return false;
            }
            // check if the piece is colliding with other pieces
            if ((*sp_playfield)[y + dy][x + dx] > 0) {
                return false;
            }
        }
        return true;
    }
}
