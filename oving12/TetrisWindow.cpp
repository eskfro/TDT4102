#include "TetrisWindow.h"
#include "map.h"
#include <iostream>


TetrisWindow::TetrisWindow(int x, int y, int width, int height, int block, int _edge, std::string title) : 
edge{_edge},
blockSize{block},
windowWidth{width},
windowHeight{height},

playButton{{2*edge + 10 * block, edge}, 100, 100, "Play"},
stopButton{{2*edge + 10 * block, 4 * edge}, 100, 100, "Stop"},
restartButton{{2*edge + 10 * block, 7 * edge}, 100, 100, "Restart"},

AnimationWindow(x, y, width + 3*block, height, title) 
{
    this->isBottomed = false;
    this->play = true;
    this->full_row = 0;

    nBlocksWidth = static_cast<int>((width - 2*edge)/static_cast<float>(block));
    nBlocksHeight = static_cast<int>((height - 2*edge)/static_cast<float>(block));
    std::cout << " blocks width: " << nBlocksWidth << " blocks height: " << nBlocksHeight << "\n";
    generateRandomTetromino();

    this->gridMatrix.resize(nBlocksHeight, std::vector<TetrominoType>(nBlocksWidth, TetrominoType::NONE));

    this->add(playButton);
    this->add(stopButton);
    this->add(restartButton);

    playButton.setCallback(std::bind(&TetrisWindow::cb_play, this));
    stopButton.setCallback(std::bind(&TetrisWindow::cb_stop, this));
    restartButton.setCallback(std::bind(&TetrisWindow::cb_restart, this));
};

void TetrisWindow::run() {
    unsigned int framesSinceLastTetronimoMove = 0;
    const unsigned int framesPerTetronimoMove = 100;

    while(!should_close()) { 
        handleInput();

        if (!play) {
            //Standard drawing 
            draw_rectangle({edge, edge}, windowWidth - 2*edge, windowHeight - 2*edge, 
	        TDT4102::Color::white, TDT4102::Color::black);
            drawGrid();
            drawCurrrentTetromino();
            drawGridLines();

            next_frame();
            continue;
        }

        framesSinceLastTetronimoMove++;
        if(framesSinceLastTetronimoMove >= framesPerTetronimoMove) {
            framesSinceLastTetronimoMove = 0;
            moveTetrominoDown();
        }
        //Standard drawing
        draw_rectangle({edge, edge}, windowWidth - 2*edge, windowHeight - 2*edge, 
	    TDT4102::Color::white, TDT4102::Color::black);
        drawGrid();
        drawCurrrentTetromino();
        drawGridLines();

        check_if_bottomed();
        check_for_full_row();

        if (isBottomed) {
            fastenTetromino();
            generateRandomTetromino();
        }
        if (full_row) {
            remove_row(full_row);
        }
        this->full_row = 0;
        this->isBottomed = false;
        next_frame();
    }
}

void TetrisWindow::cb_play() {
    this->play = true;
}

void TetrisWindow::cb_stop() {
    this->play = false;
}

void TetrisWindow::cb_restart() {
    if (!this->play) {
        clearBigGrid();
        generateRandomTetromino();
    }
}

void TetrisWindow::clearBigGrid() {
    for (int i = 0; i < nBlocksHeight; i++) {
        for (int j = 0; j < nBlocksWidth; j++)
            gridMatrix.at(i).at(j) = TetrominoType::NONE;
    }
} 


void TetrisWindow::remove_row(int n) {
    for (int d_row = (nBlocksHeight - 1); d_row >= 1; d_row--) {
        for (int col = 0; col < this->nBlocksWidth; col++) {
            if (d_row > n) {
                break;
            }
            this->gridMatrix.at(d_row).at(col) = 
            this->gridMatrix.at(d_row - 1).at(col);
        } 
    }
}

void TetrisWindow::drawGrid() {
    for (int i = 0; i < this->nBlocksHeight; i++) {
        for (int j = 0; j < this->nBlocksWidth; j++) {
            if (this->gridMatrix.at(i).at(j) == TetrominoType::NONE) {
                continue;
            }
            TDT4102::Color col = typeToColor.at(gridMatrix.at(i).at(j));
            this->draw_rectangle({edge+j*blockSize, edge+i*blockSize}, blockSize, 
            blockSize, col);
        }
    }
}

void TetrisWindow::drawGridLines() {
    for (int row = 0; row < nBlocksHeight; row++) {
        this->draw_line({edge                           , edge + row * blockSize}, 
                        {edge + nBlocksWidth * blockSize, edge + row * blockSize});
    }
    for (int col = 0; col < nBlocksWidth; col++) {
        this->draw_line({edge + col * blockSize, edge}, 
                        {edge + col * blockSize, edge + nBlocksHeight * blockSize});
    }
}

bool TetrisWindow::isInGrid(int row, int col) {
    if ((row < 0) || 
        (row > this->currentTetromino.getMatrixSize() - 1) || 
        (col < 0) ||
        (col > this->currentTetromino.getMatrixSize() - 1)) {
        return false;
    } 
    return true;
}

bool TetrisWindow::isInBig(int row, int col) {

    if (row < 0 ||
        row > (nBlocksHeight - 1) || 
        col < 0 || 
        col > (nBlocksWidth - 1)) {
        return false;
    } 
    return true;
}

void TetrisWindow::fastenTetromino() {
    int size = this->currentTetromino.getMatrixSize();
    int grid_row = (this->currentTetromino.getPosition().y - edge ) / 
    static_cast<float>(blockSize);
    int grid_col = (this->currentTetromino.getPosition().x - edge ) / 
    static_cast<float>(blockSize);

    std::cout << "\ngrid row: " << grid_row << "\ngrid col: " << grid_col << "\n";

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (isInGrid(row, col) && isInBig(row + grid_row, col + grid_col)) {
                if (this->currentTetromino.getBlock(row, col) != TetrominoType::NONE) {
                    this->gridMatrix.at(row + grid_row).at(col + grid_col) = 
                    this->currentTetromino.getBlock(row, col);
                }
            }
        }
    }

    
}

void TetrisWindow::check_for_full_row() {
    for (int d_row = (nBlocksHeight - 1); d_row >= 0; d_row--) {
        // std::cout << "\nd_row: " << d_row << "\n";
        bool row_is_full = true;
        for (int col = 0; col < nBlocksWidth; col++) {
            if (gridMatrix.at(d_row).at(col) == TetrominoType::NONE) {
                row_is_full = false;
                break;
            }
        }
        if (row_is_full) {
            // std::cout << "\nrow number " << d_row << " is full\n";
            this->full_row = d_row;
            return;
        }
    }
}

void TetrisWindow::check_if_bottomed() {
    int size = this->currentTetromino.getMatrixSize();
    int grid_row = (this->currentTetromino.getPosition().y - edge ) / 
    static_cast<float>(blockSize);
    int grid_col = (this->currentTetromino.getPosition().x - edge ) / 
    static_cast<float>(blockSize);

    int next_row = (grid_row + 1);
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (isInGrid(row, col) && isInBig(row + next_row, col + grid_col)) {
                if ((this->currentTetromino.getBlock(row, col) != TetrominoType::NONE) && 
                    (this->gridMatrix.at(row + next_row).at(col + grid_col) != TetrominoType::NONE)) {
                     this->isBottomed = true;
                }  
            }
        }
    }
}


void TetrisWindow::handleInput() {

    static bool lastZKeyState = false;
    static bool lastUpKeyState = false;
    static bool lastRightKeyState = false;
    static bool lastLeftKeyState = false;
    static bool lastDownKeyState = false;
    static bool lastXKeyState = false;

    bool currentZKeyState = is_key_down(KeyboardKey::Z);
    bool currentUpKeyState = is_key_down(KeyboardKey::UP);
    bool currentRightKeyState = is_key_down(KeyboardKey::RIGHT);
    bool currentLeftKeyState = is_key_down(KeyboardKey::LEFT);
    bool currentDownKeyState = is_key_down(KeyboardKey::DOWN);
    bool currentXKeyState = is_key_down(KeyboardKey::X);

    if(currentZKeyState && !lastZKeyState) {
        // Z / rotate anti clockwise
        // std::cout << "z\t";
        if (this->currentTetromino.getLeftPosition() != edge &&
            this->currentTetromino.getRightPosition() != (edge + nBlocksWidth * blockSize) &&
            this->currentTetromino.getBottomPosition() != (edge + nBlocksHeight * blockSize)) {
            this->currentTetromino.rotateCounterClockwise();
        }
    }
    if(currentUpKeyState && !lastUpKeyState) {
        // Up / rotate clockwise
        // std::cout << "up\t";
        if (this->currentTetromino.getLeftPosition() != edge &&
            this->currentTetromino.getRightPosition() != (edge + nBlocksWidth * blockSize) &&
            this->currentTetromino.getBottomPosition() != (edge + nBlocksHeight * blockSize)) {
            this->currentTetromino.rotateClockwise();
        }
    }
    if(currentRightKeyState && !lastRightKeyState) {
        // Right
        // std::cout << "right\t";
        if (this->currentTetromino.getRightPosition() < (edge + nBlocksWidth * blockSize)) {
            this->currentTetromino.moveRight();
        }
    }
    if(currentLeftKeyState && !lastLeftKeyState) {
        // Left
        // std::cout << "left\t";
        if (this->currentTetromino.getLeftPosition() > edge) {
            this->currentTetromino.moveLeft();
        }
    }
    if(currentDownKeyState && !lastDownKeyState) {
        // Down
        // std::cout << "down\t";
        moveTetrominoDown();
    }
    if(currentXKeyState && !lastXKeyState) {
        // Down
        // std::cout << "x\t";
        while(!isBottomed) {
            moveTetrominoDown();
        }
        
    }

    lastZKeyState = currentZKeyState;
    lastUpKeyState = currentUpKeyState;
    lastRightKeyState = currentRightKeyState;
    lastLeftKeyState = currentLeftKeyState;
    lastDownKeyState = currentDownKeyState;
    lastXKeyState = currentXKeyState;
}

void TetrisWindow::moveTetrominoDown() {
    check_if_bottomed();
    if (isBottomed) {
        return;
    }
    if (this->currentTetromino.getBottomPosition() >= (edge + nBlocksHeight * blockSize)) {
        this->isBottomed = true;
        return;
    }    
    // std::cout << "down\t";
    this->currentTetromino.moveDown();
}

void TetrisWindow::generateRandomTetromino() {
    this->currentTetromino.clearGrid();

    this->isBottomed = false;
    this->full_row = 0;

    std::random_device rd;
    unsigned int seed = rd();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution dist(0, 6);
    int randomInt = dist(engine);
    TetrominoType random_type = static_cast<TetrominoType>(randomInt);
    TDT4102::Color col  = typeToColor.at(random_type);

    int size = typeToSize.at(random_type);
    this->currentTetromino.setMatrixSize(size);
    std::cout << "size : " <<size << "\n";
    this->currentTetromino.setTetroColor(col);
    this->currentTetromino.setTopLeftCorner({edge + 3 * blockSize, edge});

    std::vector<std::vector<int>> int_matrix = initialMatrixMap.at(random_type);
              
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (int_matrix.at(i).at(j) == 0) {
                this->currentTetromino.setBlockMatrix(i, j, TetrominoType::NONE);
            }
            if (int_matrix.at(i).at(j) == 1) {
                this->currentTetromino.setBlockMatrix(i, j, random_type);
            }
        }
    }
}

void TetrisWindow::drawCurrrentTetromino() {
    for (int i = 0; i < currentTetromino.getMatrixSize(); i++) {
        for (int j = 0; j < currentTetromino.getMatrixSize(); j++) {
            if (currentTetromino.getBlock(i, j) != TetrominoType::NONE) {
                int block_position_x = currentTetromino.getPosition().x + j * blockSize; 
                int block_position_y = currentTetromino.getPosition().y + i * blockSize;
                TDT4102::Point p{block_position_x, block_position_y};

                this->draw_rectangle(p, blockSize, blockSize, currentTetromino.getColor());
            }
        }
    }
}

