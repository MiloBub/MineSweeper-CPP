#include "cell.h"

Cell::Cell() {};

Cell::Cell(int x, int y) {
	this->x = x;
	this->y = y;
	reset();
}

void Cell::set_mine() {
	this->is_mined = 1;
}

int Cell::open(std::vector<std::vector<Cell>>& cells) {
	if (get_is_open() == 0 && get_is_flagged() == 0) {
		this->is_opened = 1;
		if (get_is_mined() == 0 && get_mines_around() == 0) {
			for (int a = -1; a < 2; a++) {
				for (int b = -1; b < 2; b++) {
					if ((a == 0 && b == 0) || (this->x + a < 0) || (this->y + b < 0) || (this->x + a >= columns) || (this->y + b >= rows))
						continue;
					else {
						if (cells[this->x + a][this->y + b].get_is_open() == 0)
							cells[this->x + a][this->y + b].open(cells);
					}
				}
			}
		}
		return get_is_mined();
	}
	return 2;
}

bool Cell::get_is_mined() {
	return is_mined;
}

bool Cell::get_is_open() {
	return is_opened;
}

bool Cell::get_is_flagged() {
	return is_flagged;
}

unsigned int Cell::get_mines_around() {
	return mines_around;
};

void Cell::reset() {
	this->is_mined = 0;
	this->is_flagged = 0;
	this->is_opened = 0;
	this->mines_around = 0;
}

void Cell::count_mines_around(std::vector<std::vector<Cell>>& cells) {
	if (get_is_mined() == 0)
		for (int a = -1; a < 2; a++)
			for (int b = -1; b < 2; b++)
				if ((a == 0 && b == 0) || (this->x + a < 0) || (this->y + b < 0) || (this->x + a == columns) || (this->y + b == rows))
					continue;
				else if (cells[this->x + a][this->y + b].get_is_mined() == 1)
					++mines_around;
}

bool Cell::flag() {
	if (get_is_open() == 0)
		this->is_flagged = 1 - this->is_flagged;
	if (this->is_flagged == 0)
		return 0;
	else
		return 1;
}