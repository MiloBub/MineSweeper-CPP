#include "menu.h"

Menu::Menu(float& x, float& y) {
    if (!this->font.loadFromFile("arial.ttf"))
        std::cerr << "Font missing!" << std::endl;
    for (int i = 0; i < 3; i++) {
        this->menu[i].setFont(this->font);
        this->menu[i].setFillColor(sf::Color::Black);
        this->menu[i].setCharacterSize(70);
        this->menu[i].setPosition((x / 4), (100 + 100 * i));
    }
    this->menu[0].setString("Play");
    this->menu[1].setString("Highscore");
    this->menu[2].setString("Exit");
    this->MenuSelected = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(menu[i]);
    }
}

void Menu::move_up() {
    if (this->MenuSelected >= 0) {
        menu[this->MenuSelected].setFillColor(sf::Color::Black);
    }
    this->MenuSelected--;
    if (this->MenuSelected == -1)
        this->MenuSelected = 2;
    menu[this->MenuSelected].setFillColor(sf::Color::Blue);
}

void Menu::move_down() {
    if (this->MenuSelected < 3) {
        menu[this->MenuSelected].setFillColor(sf::Color::Black);
    }
    this->MenuSelected++;
    if (this->MenuSelected == 3)
        this->MenuSelected = 0;
    menu[this->MenuSelected].setFillColor(sf::Color::Blue);
}

int Menu::get_chosen() {
    return MenuSelected;
}

void Menu::render(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Enter:
                    if (get_chosen() == 0) {
                        Field field;
                        sf::RenderWindow window_field(sf::VideoMode(window.getSize().x, window.getSize().y), "MINESWEEPER - PLAY");
                        field.render(window_field);
                    }
                    else if (get_chosen() == 1) {
                        sf::RenderWindow window_score(sf::VideoMode(window.getSize().x, window.getSize().y), "MINESWEEPER - HIGHSCORE");
                        draw_score(window_score);
                    }
                    else
                        window.close();
                    break;
                case sf::Keyboard::Up:
                    move_up();
                    break;
                case sf::Keyboard::Down:
                    move_down();
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
        window.clear(sf::Color(150, 150, 150));
        draw(window);
        window.display();
    }
}

void Menu::check_hs_file() {
    if (std::filesystem::exists("highscore.txt") == 0) {
        std::ofstream out("highscore.txt");
        for (int i = 0; i < 5; i++)
            out << "-----" << std::endl;
    }
}

void Menu::save_highscore(int& score) {
    Menu::check_hs_file();
    std::string temp;
    std::ifstream scores("highscore.txt");
    std::vector<std::string> write(5, "");
    int flag = 0;
    int end = 0;
    std::string temp1("test");
    std::string temp2("test");
    for (int i = 0; i < 5; i++) {
        getline(scores, temp);
        if (temp.find("-") != std::string::npos && flag == 0) {
            write[i] = std::to_string(score);
            flag++;
        }
        else if (temp.find("-") != std::string::npos && flag == 1) {
            write[i] = temp;
        }
        else if ((temp.find("-") == std::string::npos)) {
            int t = std::stoi(temp);
            if (score < t) {
                temp1 = write[i];
                write[i] = std::to_string(score);
                for (int j = i + 1; j < 5; j++) {
                    if (temp1 >= write[j]) {
                    }
                    else {
                        temp2 = write[j];
                        write[j] = temp1;
                        temp1 = temp2;
                        end++;
                    }
                }
            }
            else
                write[i] = temp;
            if (end > 0)
                break;
        }
    }
    std::ofstream out("highscore.txt");
    for (int i = 0; i < 5; i++) {
        out << write[i] << std::endl;
    }
}

void Menu::draw_score(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Enter:
                    window.close();
                    break;
                default:
                    break;
                }
            }
        }
        std::string temp;
        sf::Font font;
        sf::Text text[5];
        font.loadFromFile("arial.ttf");
        std::ifstream scores("highscore.txt");
        window.clear(sf::Color(150, 150, 150));
        for (int i = 0; i < 5; i++) {
            getline(scores, temp);
            Menu::check_hs_file();
            text[i].setFont(font);
            text[i].setFillColor(sf::Color::Black);
            text[i].setCharacterSize(50);
            text[i].setPosition(cell_size * screen_resize * columns / 3, cell_size * screen_resize + 100 * i);
            text[i].setString(temp);
            window.draw(text[i]);
        }
        window.display();
    }
}