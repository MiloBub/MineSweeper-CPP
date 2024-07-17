#ifndef MENU_H
#define MENU_H

import global;

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "field.h"

class Menu {
private:
	int MenuSelected;
	sf::Font font;
	sf::Text menu[3];
public:
	Menu(float& x, float& y);
	void draw(sf::RenderWindow& window);
	void move_up();
	void move_down();
	int get_chosen();
	void render(sf::RenderWindow& window);
	static void save_highscore(int& score);
	static void check_hs_file();
	void draw_score(sf::RenderWindow& window);
};

#endif