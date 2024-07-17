#ifndef CELL_H
#define CELL_H

import global;

#include <Vector>
#include <iostream>

class Cell {
private:
	bool is_mined = 0, is_flagged = 0, is_opened = 0;
	unsigned int mines_around = 0;
	int x;
	int y;
public:
	Cell();
	Cell(int x, int y);
	bool get_is_mined(), get_is_flagged(), get_is_open();
	void count_mines_around(std::vector<std::vector<Cell>>& cells);
	unsigned int get_mines_around();
	void set_mine();
	int open(std::vector<std::vector<Cell>>& cells);
	bool flag();
	void reset();
};

#endif