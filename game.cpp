#include "game.h"
#include "log.h"


namespace gm {
    bool running, locking;
    Piece one_piece;
    Matrix playfield;
    Matrix frame;
    std::chrono::milliseconds duration;
    std::queue<Tetromino> next_pieces;

    void init() {
        running = true;
        locking = false;
        // playfield[y][x]
        playfield = Matrix(22, std::vector<int>(10, 0));
        duration = 1000ms;
        frame = playfield;
        srand(time(0));
        preview();
        one_piece = pick();
    }
    Piece pick() {
        // Truly Pseudo Random
        // std::vector<Tetromino> bag7 = { i, j, l, o, s, t, z };
        // Piece p = Piece(bag7[rand() % 7], 4, 20, 0);
        
        Piece p = Piece(next_pieces.front(), 4, 20, 0);
        next_pieces.pop();
        preview();
        p.set_playfield(std::make_shared<Matrix>(playfield));
        return std::move(p);
    }

    void preview()
    {
        static std::vector<Tetromino> bag7 = { i, j, l, o, s, t, z };
        if (next_pieces.size() < PREVIEW) {
            std::random_shuffle(bag7.begin(), bag7.end());
            for (auto i : bag7) {
                next_pieces.push(i);
            }
        }
    }
    
    void lock()
    {
        merge(playfield, one_piece);
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
        // render the current piece
        merge(frame, one_piece);
        // render the destination of the current piece
        auto ghost = one_piece;
        ghost.set_ghost();
        while(ghost.down());
        merge(frame, ghost);
    }
    void merge(Matrix& m, Piece& p)
    {
        auto [x, y] = p.get_pos();
        for (auto i : iota(0, 4)) {
            auto [dx, dy] = p.get_mino(i);
            if(m[y + dy][x + dx] == 0)
                m[y + dy][x + dx] = p.get_color();
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
    void rotate(int i) {
        one_piece.rotate(i);
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