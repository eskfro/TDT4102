#pragma once
#include "Point.h"
#include "Color.h"

#include <memory>
#include <vector>
#include <iostream>
#include <map>

enum class TetrominoType{J, L, T, S, Z, O, I, NONE};

class Tetromino {
public:
    static int blockSize;

    Tetromino(TDT4102::Point startingPoint, TetrominoType tetType);
    Tetromino();
    
    void rotateClockwise();
    void rotateCounterClockwise();

    void moveDown();
    void moveLeft();
    void moveRight();

    bool blockExist(int row, int col);
    
    TetrominoType getBlock(int row, int col);
    int getMatrixSize();
    TDT4102::Point getPosition();
    TDT4102::Color getColor();
    int getBottomPosition();
    int getRightPosition();
    int getLeftPosition();

    void clearGrid();
    void setMatrixSize(int n);
    void setTetroColor(TDT4102::Color c);
    void setBlockMatrix(int row, int col, TetrominoType t);
    void setTopLeftCorner(TDT4102::Point p);
    // Tetromino& operator=(const Tetromino& rhs);

private: 
    int matrixSize;
    TDT4102::Point topLeftCorner;
    std::vector<std::vector<TetrominoType>> blockMatrix;
    TDT4102::Color tetroColor;
};  
