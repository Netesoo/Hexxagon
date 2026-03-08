#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
private:
    sf::RenderWindow& window;
    sf::Font font;

    sf::Text title;
    sf::RectangleShape buttonPVP;
    sf::Text buttonTextPVP;
    sf::RectangleShape buttonPVC;
    sf::Text buttonTextPVC;
    sf::RectangleShape buttonLoad;
    sf::Text buttonTextLoad;
    sf::RectangleShape buttonScore;
    sf::Text buttonTextScore;

public:
    Menu(sf::RenderWindow& window);

    auto drawMenu() -> int;
};
