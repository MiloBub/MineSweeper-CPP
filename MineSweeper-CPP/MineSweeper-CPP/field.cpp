#include "field.h"

Field::Field() {
	std::vector<std::vector<Cell>> temp(rows, std::vector<Cell>(columns));
	this->cells = temp;
	this->game_over = 1;
	this->win_con = rows * columns - mines;
	restart();
}

void Field::draw(sf::RenderWindow& window) {
	sf::RectangleShape cell_shape(sf::Vector2f((cell_size * screen_resize) - 0.5 * screen_resize, (cell_size * screen_resize) - 0.5 * screen_resize));
	sf::Texture texture;
	sf::Sprite sprite;
	std::stringstream ss1;
	sf::Font font;
	sf::Text text_mines;
	font.loadFromFile("arial.ttf");
	text_mines.setFont(font);
	text_mines.setPosition(cell_size, cell_size * screen_resize * rows);
	text_mines.setCharacterSize(50);
	texture.loadFromFile("images/8pix.png");
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(screen_resize, screen_resize));
	for (unsigned int a = 0; a < columns; ++a) {
		for (unsigned int b = 0; b < rows; ++b) {
			cell_shape.setPosition(cell_size * screen_resize * a, cell_size * screen_resize * b);
			sprite.setPosition(cell_size * screen_resize * a, cell_size * screen_resize * b);
			if (cells[a][b].get_is_open() == 0) {
				cell_shape.setFillColor(sf::Color(150, 150, 150));
				sprite.setTextureRect(sf::IntRect(0 - cell_size, 0, cell_size, cell_size));
				if (cells[a][b].get_is_flagged() == 1)
					sprite.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
			}
			else {
				int miny = cells[a][b].get_mines_around();
				sprite.setTextureRect(sf::IntRect(cell_size * miny, 0, cell_size, cell_size));
				cell_shape.setFillColor(sf::Color(200, 200, 200));
				if (miny == 0) {
					sprite.setTextureRect(sf::IntRect(0 - cell_size, 0, cell_size, cell_size));
					if (cells[a][b].get_is_mined() == 1)
						cell_shape.setFillColor(sf::Color::Red);
				}
			}
			ss1.str("");
			ss1 << unflagged_mines;

			text_mines.setString(ss1.str());
			window.draw(text_mines);
			window.draw(cell_shape);
			window.draw(sprite);
		}
	}
}

bool Field::get_game_over() {
	return game_over;
}

bool Field::restart() {
	if (get_game_over() == 1) {
		this->unflagged_mines = mines;
		this->game_over = 0;
		this->first_click = 0;
		for (unsigned int a = 0; a < columns; ++a)
			for (unsigned int b = 0; b < rows; ++b)
				this->cells[a][b] = Cell(a, b);
		return 1;
	}
	return 0;
}

int Field::open_cell(int& a, int& b) {
	if (b < rows * cell_size * screen_resize) {
		if (this->first_click == 0) {
			this->first_click = 1;
			std::random_device rd;
			std::mt19937 e{ rd() };
			std::uniform_int_distribution<int> x_distribution(0, columns - 1);
			std::uniform_int_distribution<int> y_distribution(0, rows - 1);
			for (int i = 0; i < mines;) {
				int x = x_distribution(e);
				int y = y_distribution(e);
				if (cells[x][y].get_is_mined() == 0 && (x != a && y != b)) {
					cells[x][y].set_mine();
					++i;
				}
			}
			for (unsigned int a = 0; a < columns; ++a)
				for (unsigned int b = 0; b < rows; ++b)
					cells[a][b].count_mines_around(cells);
		}
		if (cells[a / cell_size / cell_size][b / cell_size / cell_size].open(cells) == 1)
			this->game_over = 1;
	}
	int licznik = 0;
	for (unsigned int a = 0; a < columns; ++a)
		for (unsigned int b = 0; b < rows; ++b)
			if (cells[a][b].get_is_open() == 1)
				licznik++;
	if (this->win_con == licznik)
		this->game_over = 1;
	return licznik;
}

void Field::flag_cell(int& x, int& y) {
	if (y < rows * cell_size * screen_resize) {
		if (cells[x / cell_size / cell_size][y / cell_size / cell_size].flag() == 0)
			unflagged_mines++;
		else
			unflagged_mines--;
	}
}

int Field::get_win_con() {
	return win_con;
}

void Field::render(sf::RenderWindow& window) {
	int ster = 0;
	int ster_text = 0;
	sf::Clock clock;
	sf::Time time;
	while (window.isOpen()) {
		sf::Event event;
		sf::Font font;
		font.loadFromFile("arial.ttf");
		sf::Text text[2];
		for (int i = 0; i < 2; i++) {
			text[i].setFont(font);
			text[i].setCharacterSize(50);
		}
		text[0].setPosition(cell_size * screen_resize * (columns - 1.5), cell_size * screen_resize * rows);
		text[1].setPosition(cell_size * screen_resize * columns / 3, cell_size * screen_resize * rows);
		std::stringstream ss2;
		int s = time.asSeconds();
		ss2.str("");
		ss2 << s;
		text[0].setString(ss2.str());
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button) {
				case sf::Mouse::Left:
					if (open_cell(event.mouseButton.x, event.mouseButton.y) == get_win_con()) {
						Menu::save_highscore(s);
						ster_text++;
					}
					break;
				case sf::Mouse::Right:
					flag_cell(event.mouseButton.x, event.mouseButton.y);
					break;
				default:
					break;
				}
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Enter:
					if (restart() == 1) {
						clock.restart();
						--ster;
					}
					break;
				case sf::Keyboard::Escape:
					window.close();
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		if (ster == 0) {
			if (get_game_over() == 1) {
				++ster;
				if (ster_text == 0)
					text[1].setString("LOSS");
				else
					text[1].setString("WIN");
			}
			time = clock.getElapsedTime();
			window.clear();
			draw(window);
			window.draw(text[0]);
			window.draw(text[1]);
			window.display();
		}
	}
}