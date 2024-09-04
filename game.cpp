#include "game.h"
#include "log.h"


namespace gm {
    bool running, locking;
    Piece one_piece;
    Matrix playfield;
    Matrix frame;
    std::chrono::milliseconds duration;

    void init() {
        running = true;
        locking = false;
        // playfield[y][x]
        playfield = Matrix(22, std::vector<int>(10, 0));
        duration = 1000ms;
        frame = playfield;
        srand(time(0));
        one_piece = pick();
    }
    Piece pick() {
        std::vector<Tetromino> bag7 = { i, j, l, o, s, t, z };
        Piece p = Piece(bag7[rand() % 7], 4, 20, 0);
        p.set_playfield(std::make_shared<Matrix>(playfield));
        return std::move(p);
    }
    void lock()
    {
        auto [x, y] = one_piece.get_pos();
        for (auto i : iota(0, 4)) {
            auto [dx, dy] = one_piece.get_mino(i);
            playfield[y + dy][x + dx] = one_piece.get_color();
        }
    }
    void clear() {
        // lg::log(playfield);
        int count = 0;
        for (auto it = playfield.begin(); it != playfield.end();) {
            bool full = true;
            for (auto i : *it) {
                if (i == 0) {
                    full = false;
                    break;
                }
            }
            if (full) {
                it = playfield.erase(it);
                playfield.push_back(std::vector<int>(it->size(), 0));
                count++;
            } else {
                it++;
            }
        }
    }
    void render() {
        frame = playfield;
        // render the curre n t piece
        auto [x, y] = one_piece.get_pos();
        for (auto i : iota(0, 4)) {
            auto [dx, dy] = one_piece.get_mino(i);
            frame[y + dy][x + dx] = one_piece.get_color();
        }
        // render the destination of the current piece
        while (one_piece.test(x, --y));
        y++;

        for (auto i : iota(0, 4)) {
            auto [dx, dy] = one_piece.get_mino(i);
            if (frame[y + dy][x + dx] == 0)
                frame[y + dy][x + dx] = 0 - one_piece.get_color();
        }
    }
    void process() {
        render();
        if (ut::timer(duration)) {
            if (one_piece.down()) {
                return;
            }
            if (locking) {
                lock();
                clear();
                one_piece = pick();
                locking = false;
            }
            else {
                locking = true;
            }
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
    void drop() {
        while (one_piece.down());
        locking = true;
    }
}