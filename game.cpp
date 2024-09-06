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
    int t_spin;
    std::random_device rd;
    std::mt19937 g(rd());

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
        preview();
        one_piece = pick();
        hold_piece.clear();
        score = 0;
        level = 1;
        lines = 0;
        t_spin = 0;
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
            std::shuffle(bag7.begin(), bag7.end(), g);
            for (auto i : bag7) {
                next_pieces.push(i);
            }
        }
    }
    
    void lock()
    {
        merge(playfield, one_piece, true);
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
        int base = 0;
        switch (count) {
        case 0:
            base = t_spin == 1 ? 400 : t_spin == 2 ? 100 : 0;
            break;
        case 1:
            base = t_spin == 1 ? 800 : t_spin == 2 ? 200 : 100;
            break;
        case 2:
            base = t_spin == 1 ? 1200 : t_spin == 2 ? 400 : 300;
            break;
        case 3:
            base = t_spin == 1 ? 1600 : 500;
            break;
        case 4:
            base = 800;
            break;
        default:
            break;
        }
        score += base * level;
        ui::show_clear(count, t_spin);
        t_spin = 0;
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
    void merge(Matrix& m, Piece& p, bool check)
    {
        // check T-spin 
        static auto check_corner = [&m, &p]() {
            int dx[4] = { 1, 1, -1, -1 };
            int dy[4] = { 1, -1, 1, -1 };
            auto [x, y] = p.get_pos();
            int count = 0;
            int bx, by;
            for (auto i : iota(0, 4)) {
                if (y + dy[i] < 0 || y + dy[i] >= m.size() || x + dx[i] < 0 || x + dx[i] >= m[0].size() || \
                    m[y + dy[i]][x + dx[i]] != 0) {
                    count++;
                }
                else {
                    bx = x + dx[i];
                    by = y + dy[i];
                }
            }
            if (count == 3) {
                if(m[by][x] && m[y][bx]) {
                    return 2; // Mini T-Spin
                }
                return 1; // T-Spin
            }
            return 0;
            };
        
        auto [x, y] = p.get_pos();
        for (auto i : iota(0, 4)) {
            auto [dx, dy] = p.get_mino(i);
            if(m[y + dy][x + dx] == 0)
                m[y + dy][x + dx] = p.get_color();
        }
        // check T-spin 
        if (check && p.get_name() == 'T') {
            int result = check_corner();
            lg::log("T-Spin: " + std::to_string(result));
            if (result > 0 && (gm::command == KEY_ROTATECCW || gm::command == KEY_ROTATECW || gm::command == KEY_ROTATE180)) {
                if (result == 2 && p.get_last_kick() != 4) {
                    t_spin = 2;
                    lg::log("Mini T-Spin");
                }
                else {
                    t_spin = 1;
                    lg::log("T-Spin");
                }
            }
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
 *      https://harddrop.com/wiki/Scoring 2009 guideline
 * 
 * Single               100 x level     
 * Double               300 x level     
 * Triple               500 x level     
 * Tetris               800 x level
 * T-Spin Mini          100 x level
 * T-Spin               400 x level
 * Mini T-Spin Single   200 x level
 * T-Spin Single        800 x level
 * Mini T-Spin Double   1200 x level
 * T-Spin Double        1200 x level
 * T-Spin Triple        1600 x level
 * Soft drop            1 point per cell
 * Hard drop            2 points per cell     
**/