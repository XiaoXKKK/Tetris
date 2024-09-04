#include "tetromino.h"

namespace gm {
    Tetromino_0 I = { {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    } };
    Tetromino_0 J = { {
        {2, 0, 0},
        {2, 2, 2},
        {0, 0, 0}
    } };
    Tetromino_0 L = { {
        {0, 0, 3},
        {3, 3, 3},
        {0, 0, 0}
    } };
    Tetromino_0 O = { {
        {0, 4, 4},
        {0, 4, 4},
        {0, 0, 0}
    } };
    Tetromino_0 S = { {
        {0, 5, 5},
        {5, 5, 0},
        {0, 0, 0}
    } };
    Tetromino_0 T = { {
        {0, 6, 0},
        {6, 6, 6},
        {0, 0, 0}
    } };
    Tetromino_0 Z = { {
        {7, 7, 0},
        {0, 7, 7},
        {0, 0, 0}
    } };

    std::map<int, Color> tetro_colors = {
        {1, Color::Cyan},
        {2, Color::Blue},
        {3, Color::Orange},
        {4, Color::Yellow},
        {5, Color::Red},
        {6, Color::Purple},
        {7, Color::Green}
    };

    Tetromino_0 rotate(Tetromino_0& t) {
        Tetromino_0 newTetro(t.size(), std::vector<int>(t.size(), 0));

        for (int i = 0; i < t.size(); i++)
        {
            for (int j = 0; j < t[i].size(); j++)
            {
                newTetro[j][t.size() - 1 - i] = t[i][j];
            }
        }
        return std::move(newTetro);
    }

    Tetromino i{ {
        {{{'I', (int)Color::Cyan}, {-1, 0}, {1, 0}, {2, 0}}},//0
        {{{'I', (int)Color::Cyan}, {0, 1}, {0, -1}, {0, -2}}},//R
        {{{'I', (int)Color::Cyan}, {-2, 0}, {-1, 0}, {1, 0}}},//2
        {{{'I', (int)Color::Cyan}, {0, 2}, {0, 1}, {0, -1}}},//L
    } };

    Tetromino j{ {
        {{{'J',(int)Color::Blue},{-1,1},{-1,0},{1,0}}},//0
        {{{'J',(int)Color::Blue},{1,1},{0,1},{0,-1}}}, // R
        {{{'J',(int)Color::Blue},{-1,0},{1,0},{1,-1}}},// 2
        {{{'J',(int)Color::Blue},{0,1},{-1,-1},{0,-1}}},//L
    } };
    Tetromino l{ {
        {{{'L',(int)Color::Orange},{-1,0},{1,0},{1,1}}},//0
        {{{'L',(int)Color::Orange},{0,1},{0,-1},{1,-1}}},//R
        {{{'L',(int)Color::Orange},{-1,-1},{-1,0},{1,0}}},//2
        {{{'L',(int)Color::Orange},{-1,1},{0,1},{0,-1}}},//L
    } };
    Tetromino o{ {
        {{{'O',(int)Color::Yellow},{0,1},{1,1},{1,0}}},//0
        {{{'O',(int)Color::Yellow},{0,-1},{1,0},{1,-1}}},//R
        {{{'O',(int)Color::Yellow},{-1,-1},{-1,0},{0,-1}}},//2
        {{{'O',(int)Color::Yellow},{-1,1},{-1,0},{0,1}}},//L
    } };
    Tetromino s{ {
        {{{'S',(int)Color::Green},{-1,0},{0,1},{1,1}}},//0
        {{{'S',(int)Color::Green},{0,1},{1,0},{1,-1}}},// R
        {{{'S',(int)Color::Green},{-1,-1},{0,-1},{1,0}}},// 2
        {{{'S',(int)Color::Green},{-1,1},{-1,0},{0,-1}}},//L
    } };
    Tetromino t{ {
        {{{'T',(int)Color::Purple},{-1,0},{0,1},{1,0}}},//0
        {{{'T',(int)Color::Purple},{0,1},{1,0},{0,-1}}},// R
        {{{'T',(int)Color::Purple},{-1,0},{1,0},{0,-1}}},//2
        {{{'T',(int)Color::Purple},{-1,0},{0,1},{0,-1}}},//L
    } };
    Tetromino z{ {
        {{{'Z',(int)Color::Red},{-1,1},{0,1},{1,0}}},//0
        {{{'Z',(int)Color::Red},{1,1},{1,0},{0,-1}}},// R
        {{{'Z',(int)Color::Red},{-1,0},{0,-1},{1,-1}}},//2
        {{{'Z',(int)Color::Red},{-1,-1},{-1,0},{0,1}}},//L
    } };
    Offset offset{{
        {{{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0}}},//0
        {{{ 0, 0},{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}}},//R
        {{{ 0, 0},{ 0, 0},{ 0, 0},{ 1, 0},{ 0, 0}}},//2
        {{{ 0, 0},{-1, 0},{-1, 1},{ 0, 2},{-1, 2}}} //L
    }};
    Offset offset_i{{
        {{{ 0, 0},{-1, 0},{ 2, 0},{-1, 0},{ 2, 0}}},//0
        {{{-1, 0},{ 0, 0},{ 0, 0},{ 0, 1},{ 0,-2}}},//R
        {{{-1, 1},{ 1, 1},{-2, 1},{ 1, 0},{-2, 0}}},//2
        {{{ 0, 1},{ 0, 1},{ 0, 1},{ 0,-1},{ 0, 2}}} //L
    }};
    Offset offset_o{{
        {{{ 0, 0}}},//0
        {{{ 0,-1}}},//R
        {{{-1,-1}}},//2
        {{{-1, 0}}} //L
    }};
}// namespace gm