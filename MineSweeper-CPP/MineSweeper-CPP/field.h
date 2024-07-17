#ifndef FIELD_H
#define FIELD_H

import global;

#include <random>
#include <Vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "cell.h"
#include "menu.h"

class Field {
private:
	bool game_over;
	bool first_click;
	std::vector<std::vector<Cell>> cells;
	int unflagged_mines;
	int win_con;
public:
	Field();
	bool get_game_over();
	int get_win_con();
	void draw(sf::RenderWindow& window);
	void flag_cell(int& x, int& y);
	int open_cell(int& x, int& y);
	bool restart();
	void render(sf::RenderWindow& window);
};

#endif