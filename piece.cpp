#include "piece.h"
#include "log.h"

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
        if (status == 2) return (int)Color::White;
        return status ? tetro_set[index][0].second : -tetro_set[index][0].second;
    }

    char Piece::get_name()
    {
        return tetro_set[index][0].first;
    }

    int Piece::get_last_kick()
    {
        return last_kick;
    }

    void Piece::set_ghost()
    {
        status = 0;
    }

    void Piece::set_hold()
    {
        status = 2;
    }

    Tetromino Piece::get_tetromino()
    {
        return tetro_set;
    }

    Piece::Piece(Tetromino& t, int x, int y, int index) : tetro_set(t), x(x), y(y), index(index), status(1), last_kick(-1)
    {
        char name = tetro_set[index][0].first;
        if (name == 'I') offset = gm::offset_i;
        else if (name == 'O') offset = gm::offset_o;
        else offset = gm::offset;
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

    bool Piece::rotate(int time)
    {
        assert(time >= 1 && time < 4);
        int next_idx = (index + time) % 4;
        for (int i = 0;i < 5;i++) {
            auto [dx_0, dy_0] = offset[index][i];
            auto [dx_1, dy_1] = offset[next_idx][i];
            auto dx = dx_0 - dx_1;
            auto dy = dy_0 - dy_1;
            if(time == 3){
                lg::log("Piece " + std::string(1, get_name()));
                lg::log("Position: " + std::to_string(x) + " " + std::to_string(y));
                lg::log("Desitnation: " + std::to_string(x + dx) + " " + std::to_string(y + dy));
                lg::log("Kick: " + std::to_string(i));
            }
            if (test(x + dx, y + dy, next_idx)) {
                last_kick = i;
                if(time == 3) lg::log("success");
                index = next_idx;
                x += dx;
                y += dy;
                return true;
            }
        }
        last_kick = -1;
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
