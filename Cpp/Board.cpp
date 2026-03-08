#include "Board.h"

Board::Board(sf::RenderWindow& win) : window(win) {

    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cout << "Failed to load font.\n";
    }

    buttonQuit = sf::RectangleShape(sf::Vector2f(100, 40));
    buttonQuit.setPosition(10, 10);
    buttonQuit.setFillColor(sf::Color::Red);

    buttonTextQuit = sf::Text("Quit", font, 20);
    buttonTextQuit.setPosition(37, 18);

    playerText.setFont(font);
    playerText.setCharacterSize(20);
    playerText.setPosition(120, 10);

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(270, 755);
    scoreText.setFillColor(sf::Color::White);

}

auto Board::createHexGrid() -> void {
    float height = std::sqrt(3) * radius;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            switch (row) {
                case 0:
                    if (!(col >= 3 && col <= 5))
                        continue;
                break;
                case 1:
                    if (col == 0 || col == 8)
                        continue;
                break;
                case 3:
                    if (col == 4)
                        continue;
                break;
                case 4:
                    if (col == 3 || col == 5)
                        continue;
                break;
                case 7:
                    if (!(col >= 2 && col <= 6))
                        continue;
                break;
                case 8:
                    if (!(col == 4))
                        continue;
                break;
            }

            float x = 110 + col * 1.5f * radius;
            float y = 20 + row * height;
            if (col % 2 != 0) {
                y += height / 2.0f;
            }

            sf::CircleShape shape(radius, 6);
            shape.setFillColor(sf::Color(182, 0, 182));
            shape.setOutlineColor(sf::Color::White);
            shape.setOutlineThickness(1);
            shape.setPosition(x, y);
            shape.setRotation(30);

            Hexagon hexagon(shape, row, col, HexState::Empty);

            if ((row == 0 && col == 4) ||
                (row == 6 && col == 8) ||
                (row == 6 && col == 0)) {
                hexagon.setState(HexState::Player1);
                }
            else if ((row == 8 && col == 4) ||
                     (row == 2 && col == 0) ||
                     (row == 2 && col == 8)) {
                     hexagon.setState(HexState::Player2);
                     }

            hexagons.push_back(hexagon);
        }
    }
}

auto Board::draw() -> bool {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = sf::Mouse::getPosition(window);

                if (buttonQuit.getGlobalBounds().contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y))) {
                    return true;}

                if (event.mouseButton.button == sf::Mouse::Left) {
                    Hexagon* clicked = getClosestHexagon(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y));
                    if (clicked) {
                        handleHexagonClick(clicked);
                    }
                }
            }
        }

        window.clear();

        for (const auto& hexagon : hexagons) {
            window.draw(hexagon.getShape());
        }

        window.draw(buttonQuit);
        window.draw(buttonTextQuit);
        playerText.setString(std::string(currentPlayer == HexState::Player1 ? "Red" : "Green") + " player's move");
        window.draw(playerText);
        window.draw(scoreText);
        window.display();
    }
    return false;
}


auto Board::getClosestHexagon(float x, float y) -> Hexagon* {
    for (auto& hexagon : hexagons) {
        if (hexagon.contains(x, y)) {
            return &hexagon;
        }
    }
    return nullptr;
}

auto Board::handleHexagonClick(Hexagon* hexagon) -> void {
    if (!hexagon) return;

    if (!selectedHexagon) {
        if (hexagon->getState() == currentPlayer) {
            selectedHexagon = hexagon;
            highlightPossibleMoves(hexagon);
            hexagon->getShape().setOutlineColor(sf::Color::Yellow);
            hexagon->getShape().setOutlineThickness(3);
        }
    }
    else {
        if (hexagon == selectedHexagon) {
            selectedHexagon = nullptr;
            resetHighlights();
            return;
        }

        if (hexagon->getState() == HexState::Empty &&
            std::find(possibleMoves.begin(), possibleMoves.end(), hexagon) != possibleMoves.end()) {
            makeMove(selectedHexagon, hexagon);
            switchPlayer();
            }

        selectedHexagon = nullptr;
        resetHighlights();
    }
}

auto Board::resetHighlights() -> void {
    for (auto& hex : hexagons) {
        hex.getShape().setOutlineColor(sf::Color::White);
        hex.getShape().setOutlineThickness(1);
    }
    possibleMoves.clear();
}

auto Board::highlightPossibleMoves(const Hexagon* hexagon) -> void {
    possibleMoves.clear();

    for (auto& hex : hexagons) {
        if (hex.getState() != HexState::Empty) {
            continue;
        }

        float distance = hexagon->getDistance(hex);
        if (distance <= 90.0f || distance <= 180.0f) {
            possibleMoves.push_back(&hex);
            hex.getShape().setOutlineColor(sf::Color::Yellow);
            hex.getShape().setOutlineThickness(3);
        }
    }
}

auto Board::makeMove(Hexagon* from, Hexagon* to) -> void {
    float distance = from->getDistance(*to);

    if (distance <= 90.0f) {
        to->setState(currentPlayer);
    }
    else if (distance <= 180.0f) {
        to->setState(currentPlayer);
        from->setState(HexState::Empty);
    }

    captureSurroundingPieces(to);
    updateScore();
}

auto Board::captureSurroundingPieces(Hexagon* hex) -> void {
    for (auto& neighbor : hexagons) {
        if (hex->isNeighbor(neighbor) &&
            neighbor.getState() != HexState::Empty &&
            neighbor.getState() != currentPlayer) {
            neighbor.setState(currentPlayer);
            }
    }
}

auto Board::switchPlayer() -> void {
    currentPlayer = (currentPlayer == HexState::Player1) ?HexState::Player2 : HexState::Player1;
}

auto Board::getPlayerPiecesCount(HexState player) -> int {
    int count = 0;
    for (const auto& hex : hexagons) {
        if (hex.getState() == player) {
            count++;
        }
    }
    return count;
}

auto Board::updateScore() -> void {
    int redCount = getPlayerPiecesCount(HexState::Player1);
    int greenCount = getPlayerPiecesCount(HexState::Player2);

    scoreText.setString("Red: " + std::to_string(redCount) +" | Green: " + std::to_string(greenCount));
    if (redCount == 0) {
        scoreText.setString("Green wins!");
        auto file = std::fstream("../Cpp/data.txt", std::ios::app);
        file << "\n" << "Green 58 vs Red 0";
        file.close();
    }
    if (greenCount == 0) {
        scoreText.setString("Red wins!");
        auto file = std::fstream("../Cpp/data.txt", std::ios::app);
        file << "\n" << "Red 58 vs Green 0";
        file.close();
    }
    if (redCount+greenCount == 58) {
        if (redCount>greenCount) {
            scoreText.setString("Red wins!");
            auto file = std::fstream("../Cpp/data.txt", std::ios::app);
            file << "\n" << "Red " << redCount << " vs Green" << greenCount;
            file.close();
        } else {
            window.clear();
            scoreText.setString("Green wins!");
            window.draw(scoreText);
            auto file = std::fstream("../Cpp/data.txt", std::ios::app);
            file << "\n" << "Red " << redCount << " vs Green" << greenCount;
            file.close();
        }
    }

}
