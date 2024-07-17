import global;

#include <SFML/Graphics.hpp>
#include <filesystem>

#include "cell.h"
#include "field.h"
#include "menu.h"

int main() {
    float x = columns * cell_size * screen_resize;
    float y = (rows + 1) * cell_size * screen_resize;
    sf::RenderWindow window(sf::VideoMode(x, y), "MINESWEEPER");
    Menu menu(x, y);
    menu.render(window);
    return 0;
}