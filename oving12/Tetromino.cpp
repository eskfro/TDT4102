#include "Tetromino.h"
#include "map.h"

Tetromino::Tetromino(){
    topLeftCorner = {0, 0};
    matrixSize = 0;
}

int Tetromino::blockSize = 0;

void Tetromino::setTetroColor(TDT4102::Color c) {
    this->tetroColor.redChannel = c.redChannel;
    this->tetroColor.greenChannel = c.greenChannel;
    this->tetroColor.blueChannel = c.blueChannel;
}

Tetromino::Tetromino(TDT4102::Point startingPoint, TetrominoType tetType) : 
topLeftCorner{startingPoint}
{
    this->matrixSize = typeToSize.at(tetType);
    TDT4102::Color c = typeToColor.at(tetType);
    this->setTetroColor(c);
    std::vector<std::vector<int>> int_matrix = initialMatrixMap.at(tetType);

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (int_matrix.at(i).at(j) == 0) {
                std::cout << "NONE\n";
                blockMatrix[i][j] = TetrominoType::NONE;
            }
            if (int_matrix.at(i).at(j) == 1) {
                std::cout << "NONE\n";
                blockMatrix[i][j] = tetType;
            }
        }
    }
}


void Tetromino::setMatrixSize(int n) {
    this->matrixSize = n;
    this->blockMatrix.resize(n, std::vector<TetrominoType>(n, TetrominoType::NONE));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            this->blockMatrix[i][j] = TetrominoType::NONE;
        }
    }
}


void Tetromino::moveLeft() {
    topLeftCorner.x = topLeftCorner.x - blockSize;
}

void Tetromino::moveRight() {
    topLeftCorner.x = topLeftCorner.x + blockSize;
}

void Tetromino::moveDown() {
    topLeftCorner.y = topLeftCorner.y + blockSize;
}

void Tetromino::rotateCounterClockwise() {
    //Første rotasjon, med hensyn på diagonalen
    for (int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }

    //Andre rotasjon, med hensyn på den midtre raden
    for (int row = 0; row < matrixSize/2; row++) {
        for(int column = 0; column < matrixSize; column++){
            std::swap(blockMatrix[row][column], blockMatrix[matrixSize-row-1][column]);
            
        }
    }
}

void Tetromino::rotateClockwise() {
    //Første rotasjon, med hensyn på diagonalen
    for (int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }
     
    //Andre rotasjon, med hensyn på den midtre kolonnen
    for (int row = 0; row < matrixSize; row++){
        for(int column = 0; column < matrixSize/2; column++){
            std::swap(blockMatrix[row][column], blockMatrix[row][matrixSize-column-1]);
        }
    }
}

void Tetromino::clearGrid() {
    this->blockMatrix.clear();
}

bool Tetromino::blockExist(int row, int col) {
    if (blockMatrix.at(row).at(col) != TetrominoType::NONE) {
        return true;
    } else {return false;}
}

TetrominoType Tetromino::getBlock(int row, int col) {
    return blockMatrix.at(row).at(col);
}

int Tetromino::getMatrixSize() {
    return this->matrixSize;
}

TDT4102::Point Tetromino::getPosition() {
    return this->topLeftCorner;
}

int Tetromino::getBottomPosition() {
    int y = this->getPosition().y;
    for (int d_row = (matrixSize-1); d_row >= 0; d_row--) {
        for (int col = 0; col < matrixSize; col++) {
            if (this->blockMatrix.at(d_row).at(col) != TetrominoType::NONE) {
                return (y + (d_row+1) * blockSize);
            }
        }
    }
    return y;
    
}

int Tetromino::getRightPosition() {
    int x = this->getPosition().x;
    int empty_right_cols = 0;
    for (int d_col = (matrixSize - 1); d_col >= 0; d_col--) {
        for (int row = 0; row < matrixSize; row++) {
            if (this->blockMatrix.at(row).at(d_col) != TetrominoType::NONE) {
                return (x + (d_col+1) * blockSize);
            }
        }
    }
    return x;
}


int Tetromino::getLeftPosition() {
    int x = this->getPosition().x;
    bool left_col_is_empty = true;
    for (int row = 0; row < matrixSize; row++) {
        if(blockMatrix.at(row).at(0) != TetrominoType::NONE) {
            left_col_is_empty = false;
        }
    }  
    if (left_col_is_empty) {
        return x + blockSize;
    } else {return x;}
}

// Tetromino& Tetromino::operator=(const Tetromino& rhs) {
//     this->matrixSize = rhs.matrixSize;
//     this->topLeftCorner = rhs.topLeftCorner;
//     this->tetroColor = rhs.tetroColor;

//     for (int i = 0; i < rhs.getMatrixSize(); i++) {
//         for (int j = 0; j < rhs.getMatrixSize(); j++) {
//             this->blockMatrix[i][j] = rhs.blockMatrix.at(i).at(j);
//         }
//     }
//     return *this;
// }

TDT4102::Color Tetromino::getColor() {
    return tetroColor;
}

void Tetromino::setTopLeftCorner(TDT4102::Point p) {
    this->topLeftCorner = p;
}

void Tetromino::setBlockMatrix(int row, int col, TetrominoType t) {
    this->blockMatrix[row][col] = t;
}




