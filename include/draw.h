# pragma once

#include "define.h"
#include "tetromino.h"
#include "piece.h"
#include "game.h"

namespace dw {
    void window(int top, int left, int weight, int height, std::string title);
    void tetromino(Tetromino_0& t, int top, int left);
    void tetromino(Tetromino& t, int top, int left, int index);

    void frame(Matrix& m, int top, int left);
    void next(std::queue<Tetromino> q, int top, int left);
    void hold(Tetromino& t, int top, int left);
    void matrix(const Matrix& m, int top, int left, Matrix* buffer = nullptr, std::string blank = "  ");
}