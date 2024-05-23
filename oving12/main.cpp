#include "Tetromino.h"
#include "TetrisWindow.h"


int main() {
	//Opprett vindu her
	std::cout << "main:   - - - - - - - - -   - - -- - -- - \n"; 
	int _blocksize = 30;

	Tetromino::blockSize = _blocksize;
	constexpr int nBlocksWidth = 10;
	constexpr int nBlocksHeight = 20;
	constexpr int edge = 30;

	int window_width = nBlocksWidth * _blocksize + 2*edge;
	int window_height = nBlocksHeight * _blocksize + 2*edge;

	int x = (1920 - window_width)/2.0;
	int y = 100;
	
	TetrisWindow window = 
	TetrisWindow(x, y, window_width, window_height, _blocksize, edge, "Tetris Window");
	window.run();
	window.wait_for_close();



	
    //kall run på det her
	return 0;
}
