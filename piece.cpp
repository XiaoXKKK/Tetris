#include "piece.h"

namespace gm {
    std::pair<int, int> Piece::get_mino(int i)
    {
        assert(i >= 0 && i < 4);
        if (i == 0) return std::pair<int, int>(0, 0);
        return tetro_set[index][i];
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

    void Piece::move(int dx, int dy)
    {
        if (test(x + dx, y + dy, index)) {
            x += dx;
            y += dy;
        }
    }

    void Piece::down()
    {
        move(0, -1);
    }

    void Piece::left()
    {
        move(-1, 0);
    }

    void Piece::right()
    {
        move(1, 0);
    }

    void Piece::rotate()
    {
        // TODO: check if the rotation is valid
        index = (index + 1) % 4;
    }

    bool Piece::test(int x, int y, int index)
    {
        for (int i = 1;i < 4;i++) {
            auto [dx, dy] = get_mino(i);
            // check if the piece is out of bounds
            if (x + dx < 0 || x + dx >= (*sp_playfield).size() \
                || y + dy < 0 || y + dy >= (*sp_playfield)[0].size()) {
                return false;
            }
            // check if the piece is colliding with other pieces
            if ((*sp_playfield)[x + dx][y + dy] > 0) {
                return false;
            }
        }
        return true;
    }
}
