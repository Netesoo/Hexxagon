#include "Scores.h"

Scores::Scores(sf::RenderWindow &win)
    : window(win) {

    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cout << "Failed to load font.\n";
    }

    buttonQuit = sf::RectangleShape(sf::Vector2f(100, 40));
    buttonQuit.setPosition(10, 10);
    buttonQuit.setFillColor(sf::Color::Red);

    buttonTextQuit = sf::Text("Quit", font, 20);
    buttonTextQuit.setPosition(37, 18);

}

auto Scores::drawaScore() -> bool {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = sf::Mouse::getPosition(window);

                if (buttonQuit.getGlobalBounds().contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y))) {
                    return true;
                }
            }
        }
        window.clear();

        auto file = std::fstream("../Cpp/data.txt");
        if (!file) {
            auto error = sf::Text("File not found!", font, 24);
            error.setPosition(300,400);
            window.draw(error);
        }

        auto word = std::string();
        auto result = std::vector<std::string>{};

        while (std::getline(file,word)) {
            result.push_back(word);
        }

        file.close();

        auto text = std::vector<sf::Text>{};
        auto space = 100;
        for (const auto& out : result) {
            auto res = sf::Text(out, font, 24);
            res.setPosition(300, space);
            space += 50;
            window.draw(res);
        }

        window.draw(buttonQuit);
        window.draw(buttonTextQuit);
        window.display();
    }
    return false;
}



