#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class Scores {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::RectangleShape buttonQuit;
    sf::Text buttonTextQuit;

public:
    Scores(sf::RenderWindow& window);

    auto drawaScore() -> bool;
};


