#include "Tile.h"
#include <map>
#include <cassert>
#include <iostream>

// For aa sette labelfarge i henhold til hvor mange miner som er rundt
const std::map<int, TDT4102::Color> minesToColor
{{1, TDT4102::Color::blue},
{2, TDT4102::Color::red},
{3, TDT4102::Color::dark_green},
{4, TDT4102::Color::dark_magenta},
{5, TDT4102::Color::dark_blue},
{6, TDT4102::Color::dark_cyan},
{7, TDT4102::Color::dark_red},
{8, TDT4102::Color::gold}};

// For aa sette Tilelabel i henhold til state
const std::map<Cell, std::string> cellToSymbol
{{Cell::closed, ""},
{Cell::open, ""},
{Cell::flagged, "|>"}};

Tile::Tile(TDT4102::Point pos, int size) : 
	Button({pos.x, pos.y}, 1.5*size, size, "") {
		setButtonColor(TDT4102::Color::silver);
	}

void Tile::open() {
	if (this->state == Cell::open || this->state == Cell::flagged) {
		return;
	}
	if (this->isMine) {
		set_label("X");
	 	set_label_color(TDT4102::Color::red);
	}
	setButtonColor(TDT4102::Color::white);
	this->state = Cell::open;
}

//Lagde denne funksjonen slik at jeg kan implementere
//retry knapp
void Tile::close() {
	this->isMine = false;
	this->state = Cell::closed;

	setButtonColor(TDT4102::Color::silver);
	set_label(cellToSymbol.at(this->state));
	set_label_color(TDT4102::Color::black);

}

void Tile::flag() {
	if (this->state == Cell::open) {
		return;
	}
	if (this->state == Cell::flagged) {
		this->state = Cell::closed;
		set_label(cellToSymbol.at(this->state));
		// set_label_color(TDT4102::Color::white);
		return;
	}
	if (this->state == Cell::closed) {
		this->state = Cell::flagged;
		set_label(cellToSymbol.at(this->state));
		set_label_color(TDT4102::Color::red);
	}
	// set_label(cellToSymbol.at(this->state));	
	// this->setButtonColor(TDT4102::Color::red);
}

void Tile::setAdjMines(int n) {
	// std::cout << "adjacent mines : " << n << std::endl;
	if (this->isMine || this->state == Cell::flagged) {
		return;
	}
	assert(n > 0 || n < 9);
	set_label_color(minesToColor.at(n + 1));
	set_label(std::to_string(n));
}

void Tile::make_mine() {
	this->isMine = true;
}

bool Tile::is_mine() const {
	return isMine;
}



