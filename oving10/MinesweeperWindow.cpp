#include "MinesweeperWindow.h"
#include "Tile.h"
#include <iostream>
#include <random>
#include <set>
#include <cassert>
#include <vector>
#include <memory>


MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize + 100, (height + 1) * cellSize, title},
	width{width}, height{height}, mines{mines}, 
	tf_main{{width * cellSize, static_cast<int>(height / 2.0) * cellSize - 150}, 100, 100, "game :\n\npending ..."},
	check_if_won({width * cellSize, static_cast<int>(height / 2.0) * cellSize - 50}, 100, 100, "check"),
	btn_retry({width * cellSize, static_cast<int>(height / 2.0) * cellSize + 50 }, 100, 100, "retry")

{
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->setCallback(std::bind(&MinesweeperWindow::cb_click, this));
			auto temp = tiles.back().get();
			add(*temp); 
		}
	}

	//Legger til button
	add(check_if_won);
    check_if_won.setCallback(std::bind(&MinesweeperWindow::cb_check, this));

	add(btn_retry);
    btn_retry.setCallback(std::bind(&MinesweeperWindow::cb_retry, this));

	//Legger til søkeboks for spill
	add(tf_main);

	// Legg til miner paa tilfeldige posisjoner
	std::random_device rd;
	unsigned int seed = rd();
	default_random_engine engine(seed);
	uniform_int_distribution dist(0, width * height - 1);

	bool all_positions_are_unique = false;

	//Lokke som går helt til kombinasjonen er unik
	while (!all_positions_are_unique) {
		std::vector<int> v;
		for (int i = 0; i < mines; i++) {
			int random_int = dist(engine);
			v.push_back(random_int);
		}
		//Lager et set,  sjekker om vektoren er av unike elementer
		set<int> s(v.begin(), v.end());
		all_positions_are_unique = (s.size() == v.size());

		//Setter isMIne til true
		//med hjelpefunksjonen make_mine();
		if (all_positions_are_unique) {
			std::cout << "\ngame : mine at : ";
			for (int i : v) {
				assert(i < (width * height) && i > -1); 
				tiles.at(i)->make_mine();
				std::cout << i << " ";

				//Setter label på knappene
				//
				tiles.at(i)->setLabel("m");
				tiles.at(i)->setLabelColor(TDT4102::Color::green);
			}
			std::cout << std::endl;
		}
	}
}






vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}







void MinesweeperWindow::openTile(Point xy) {
	//Spillet fryser når man er ferdig
	if (game_is_lost || game_is_won) {
		return;
	}
	at(xy)->open();

	if (at(xy)->getState() == Cell::flagged) {
		return;
	}
	//Hvis spiller treffer en mine
	if (at(xy)->is_mine()) {
		game_is_lost = true;
		add_tf();
		std::cout << "\nyou lose | you hit a mine\n" << std::endl;
		return;
	}

	//Spilleren traff ikke en mine, tellekode
	vector<Point> p = adjacentPoints(xy);
	int adjacent_mines = countMines(p);
	if (adjacent_mines > 0) {
		at(xy)->setAdjMines(adjacent_mines);
		return;
	}

	//rekursjon
	for (Point pnt : p) {
		//hindrer at rekursjonen går fram og tilbake mellom åpne tiles
		if (at(pnt)->getState() == Cell::open) {
			continue;
		}
		openTile(pnt);
	}
}






void MinesweeperWindow::flagTile(Point xy) {
	if (game_is_lost || game_is_won) {
		return;
	}
	at(xy)->flag();
}





//Kaller openTile ved venstreklikk og flagTile ved hoyreklikk
void MinesweeperWindow::cb_click() {
	Point xy{this->get_mouse_coordinates()};
	if (!inRange(xy)) {
		return;
	}
	if (this->is_left_mouse_button_down()) {
		openTile(xy);
	}
	else if(this->is_right_mouse_button_down()){
		flagTile(xy);
	}
}






int MinesweeperWindow::countMines(vector<Point> coords) const {
	int count = 0; 
	for (Point p : coords) {
		if (at(p)->is_mine()) {
			count++;
		}
	}
	return count;
}






void MinesweeperWindow::cb_check() {
	int flagged_counter = 0;
	int other_counter = 0;

	std::cout << "\nchecking ... \n"; 

	//Counter kode
	for (const auto tile_ptr : tiles) {
		if (tile_ptr->getState() == Cell::flagged && tile_ptr->is_mine()) {
			flagged_counter++;
			continue;
		}
		if (tile_ptr->getState() == Cell::open && tile_ptr->is_mine() == false) {
			other_counter++;
		}	
	}
	//Telle kode
	if (flagged_counter == this->mines && other_counter == Size() - this->mines) {
		game_is_won = true;
		std::cout << "you won\n";
		add_tf();
	} 
	// if (game_is_won) {
	// 	std::cout << "\nyou won\n";
	// 	return;
	// }

	//Litt sånn printe greier
	if (game_is_lost) {
		std::cout << "flagged counter : " << flagged_counter << "\n";
		std::cout << "other   counter : " << other_counter << "\n";
		std::cout << "you lost\n";
	} 
	else if (!game_is_lost && !game_is_won) {
		std::cout << "flagged counter : " << flagged_counter << "\n";
		std::cout << "other   counter : " << other_counter << "\n";
		std::cout << "pending ...\n";
		// add_tf();
	}
}




void MinesweeperWindow::add_tf() {
	if (game_is_won) {
		tf_main.setText("game :\n\nyou won");
	} 
	if (game_is_lost) {
		tf_main.setText("game :\n\nyou lost");
	}
}




void MinesweeperWindow::cb_retry() {
	game_is_lost = false;
	game_is_won = false; 
	std::cout << "\ngame : retry";
	tf_main.setText("game :\n\npending ...");

	//Lukker alle tiles
	for (shared_ptr<Tile>& t : tiles) {
		t->close();
	}

	std::random_device rd;
	unsigned int seed = rd();
	default_random_engine engine(seed);
	uniform_int_distribution dist(0, width * height - 1);

	bool all_positions_are_unique = false;

	//Lokke som går helt til kombinasjonen er unik
	while (!all_positions_are_unique) {
		std::vector<int> v;
		for (int i = 0; i < mines; i++) {
			int random_int = dist(engine);
			v.push_back(random_int);
		}
		//Lager et set,  sjekker om vektoren er av unike elementer
		set<int> s(v.begin(), v.end());
		all_positions_are_unique = (s.size() == v.size());

		//Setter isMIne til true
		//med hjelpefunksjonen make_mine();
		if (all_positions_are_unique) {
			std::cout << "\ngame : mine at : ";
			for (int i : v) {
				assert(i < (width * height) && i > -1); 
				tiles.at(i)->make_mine();
				std::cout << i << " ";	

				//Setter label på knappene
				tiles.at(i)->setLabel("m");
				tiles.at(i)->setLabelColor(TDT4102::Color::green);
			}
			std::cout << std::endl;
		}
	}	
}



