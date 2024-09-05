#include "game.h"
#include "log.h"


namespace gm {
    bool running, locking, holding, end, helping, reseting;
    Piece one_piece;
    Matrix playfield;
    Matrix frame;
    std::chrono::milliseconds duration;
    std::queue<Tetromino> next_pieces;
    Tetromino hold_piece;
    int score;
    int level;
    int lines;
    
    void init() {
        running = true;
        locking = false;
        holding = false;
        helping = false;
        reseting = false;
        end = false;
        // playfield[y][x]
        playfield = Matrix(22, std::vector<int>(10, 0));
        duration = 1000ms;
        frame = playfield;
        srand(time(0));
        preview();
        one_piece = pick();
        hold_piece.clear();
        score = 0;
        level = 1;
        lines = 0;
    }
    Piece pick() {
        // Truly Pseudo Random
        // std::vector<Tetromino> bag7 = { i, j, l, o, s, t, z };
        // Piece p = Piece(bag7[rand() % 7], 4, 20, 0);
        
        Piece p = Piece(next_pieces.front(), 4, 20, 0);
        next_pieces.pop();
        preview();
        p.set_playfield(std::make_shared<Matrix>(playfield));
        if (!p.test(4, 20)) {
            end = true;
        }
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
            }
            else {
                it++;
            }
        }
        switch (count) {
        case 1:
            score += 100 * level;
            break;
        case 2:
            score += 300 * level;
            break;
        case 3:
            score += 500 * level;
            break;
        case 4:
            score += 800 * level;
            break;
        default:
            break;
        }
        lines += count;
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
    void levelup() {
        level = lines / 10 + 1;
        duration = std::chrono::milliseconds((int)(pow(0.8 - (level - 1) * 0.007, level - 1) * 1000));
    }

    void process() {
        if (end || helping) return;
        render();
        if (ut::timer(duration)) {
            if (one_piece.down()) {
                return;
            }
            if (locking) {
                lock();
                clear();
                levelup();
                one_piece = pick();
                locking = false;
                holding = false;
                reseting = false;
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
        score++;
    }
    void left() {
        one_piece.left();
    }
    void right() {
        one_piece.right();
    }
    void drop() {
        while (one_piece.down())
            score += 2;
        locking = true;
    }
    void reset() {
        init();
        reseting = true;
    }
    void help()
    {
        helping = !helping;
        reseting = !helping;
    }
    void hold() {
        if (holding) {
            return;
        }
        if (hold_piece.empty()) {
            hold_piece = one_piece.get_tetromino();
            one_piece = pick();
        }
        else {
            auto temp = one_piece.get_tetromino();
            one_piece = Piece(hold_piece, 4, 20, 0);
            hold_piece = temp;
            one_piece.set_playfield(std::make_shared<Matrix>(playfield));
        }
        holding = true;
    }
}

/**
 *      https://harddrop.com/wiki/Scoring
 * 
 * Single	100 x level	
 * Double	300 x level	
 * Triple	500 x level	
 * Tetris	800 x level	
 * Soft drop	1 point per cell	
 * Hard drop	2 points per cell	
**/