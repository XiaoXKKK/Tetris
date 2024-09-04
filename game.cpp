#include "game.h"

namespace gm{
    bool running;
    Piece one_piece;
    Matrix playfield;
    Matrix frame;
    std::chrono::milliseconds duration;

    void init() {
        running = true;
        one_piece = pick();
        // playfield[x][y] 
        playfield = Matrix(10, std::vector<int>(22, 0));
        duration = 1000ms;
        frame = playfield;
        one_piece.set_playfield(playfield);
    }
    Piece pick() {
        return Piece(j, 4, 20, 0);
    }
    void render() {
        frame = playfield;
        // render the curre n t piece
        auto [x, y] = one_piece.get_pos();
        for (auto i : iota(0, 4)) {
            auto [dx, dy] = one_piece.get_mino(i);
            frame[x + dx][y + dy] = one_piece.get_color();
        }
        // render the destination of the current piece
        while (one_piece.test(x, --y, 0));
        y++;
        for (auto i : iota(0, 4)) {
            auto [dx, dy] = one_piece.get_mino(i);
            if (frame[x + dx][y + dy] == 0)
                frame[x + dx][y + dy] = 0 - one_piece.get_color();
        }
    }
    void process() {
        render();
        if (ut::timer(duration)) {
            one_piece.down();
        } 
    }

    void quit() {
        running = false;
    }
    void rotate() {
        one_piece.rotate();
    }
    void down() {
        one_piece.down();
    }
    void left() {
        one_piece.left();
    }
    void right() {
        one_piece.right();
    }
}