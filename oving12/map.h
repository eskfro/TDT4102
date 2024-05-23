#include "TetrisWindow.h"
#include "Tetromino.h"
#include <map>


const std::map<TetrominoType, int> typeToSize {
    {TetrominoType::J, 3},
    {TetrominoType::L, 3},
    {TetrominoType::T, 3},
    {TetrominoType::S, 3},
    {TetrominoType::Z, 3},
    {TetrominoType::O, 2},
    {TetrominoType::I, 4}
};

const std::map<TetrominoType, TDT4102::Color> typeToColor {
    {TetrominoType::J, TDT4102::Color::blue},
    {TetrominoType::L, TDT4102::Color::orange},
    {TetrominoType::T, TDT4102::Color::purple},
    {TetrominoType::S, TDT4102::Color::green},
    {TetrominoType::Z, TDT4102::Color::red},
    {TetrominoType::O, TDT4102::Color::yellow},
    {TetrominoType::I, TDT4102::Color::light_blue}
};

const std::map<TetrominoType, std::vector<std::vector<int>>> initialMatrixMap {

    {
    TetrominoType::J,
        {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 1}
        }
    },
    {
    TetrominoType::L,
        {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 1}
        }
    },
    {
    TetrominoType::T,
        {
        {0, 0, 0},
        {1, 1, 1},
        {0, 1, 0}
        }
    },
    {
    TetrominoType::S,
        {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}
        }
    },
    {
    TetrominoType::Z,
        {
        {0, 0, 0},
        {1, 1, 0},
        {0, 1, 1}
        }
    },
    {
    TetrominoType::O,
        {
        {1, 1},
        {1, 1}
        }
    },
    {
    TetrominoType::I,
        {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
        }
    }
};