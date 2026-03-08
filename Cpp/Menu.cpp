#include "Menu.h"

Menu::Menu(sf::RenderWindow& win) : window(win) {
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Failed to load font.\n";
    }

    title = sf::Text("Hexxagon", font, 75);
    title.setPosition(215, 180);

    buttonPVP = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonPVP.setPosition({250, 300});
    buttonPVP.setFillColor(sf::Color::Black);

    buttonTextPVP = sf::Text("Player vs Player", font, 24);
    buttonTextPVP.setPosition(305, 310);

    buttonPVC = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonPVC.setPosition(250, 370);
    buttonPVC.setFillColor(sf::Color::Black);

    buttonTextPVC = sf::Text("Player vs Computer, nie zrobione", font, 24);
    buttonTextPVC.setPosition(290, 380);

    buttonLoad = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonLoad.setPosition({250, 440});
    buttonLoad.setFillColor(sf::Color::Black);

    buttonTextLoad = sf::Text("Load, nie zrobione", font, 24);
    buttonTextLoad.setPosition(370, 450);

    buttonScore = sf::RectangleShape(sf::Vector2f(300, 50));
    buttonScore.setPosition(250, 510);
    buttonScore.setFillColor(sf::Color::Black);

    buttonTextScore = sf::Text("Scores", font, 24);
    buttonTextScore.setPosition(370, 520);
}

auto Menu::drawMenu() -> int {
    while (window.isOpen()) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1; // Zamknięcie aplikacji
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(window);

                    if (buttonPVP.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        return 1;
                    }
                    if (buttonScore.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        return 4;
                    }
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(buttonPVP);
        window.draw(buttonTextPVP);
        window.draw(buttonPVC);
        window.draw(buttonTextPVC);
        window.draw(buttonLoad);
        window.draw(buttonTextLoad);
        window.draw(buttonScore);
        window.draw(buttonTextScore);
        window.display();
    }

    return -1;
}
