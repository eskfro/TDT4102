#pragma once
#include "AnimationWindow.h"
#include "Tetromino.h"
#include "widgets/TextInput.h"
#include "widgets/Button.h"

#include <random>
#include <map>
#include <memory>
#include <iostream>

class TetrisWindow : public TDT4102::AnimationWindow {

public:
    TetrisWindow(int x, int y, int width, int height, int blockSize, int edge, std::string title);
    void run();
    void drawCurrrentTetromino();
    void generateRandomTetromino();
    void moveTetrominoDown();
    void fastenTetromino();

    void drawGrid();
    void drawGridLines();
    void clearBigGrid();

    void check_if_bottomed();
    void check_for_full_row();
    void remove_row(int n);

    bool isInGrid(int row, int col);
    bool isInBig(int row, int col);

    void cb_play();
    void cb_stop();
    void cb_restart();

private:
    void handleInput();

    bool isBottomed; 
    int full_row;

    int nBlocksWidth;
    int nBlocksHeight;
    int windowWidth;
    int windowHeight;
    int blockSize;
    int edge;

    std::vector<std::vector<TetrominoType>> gridMatrix;
    std::vector<std::vector<TetrominoType>> currentMatrix;
    Tetromino currentTetromino;

    TDT4102::Button playButton;
    TDT4102::Button stopButton;
    TDT4102::Button restartButton;

    bool play;
};
