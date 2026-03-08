#pragma once
#include <SFML/Graphics.hpp>
#include "Hexagon.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

class Board {
private:
    std::vector<Hexagon> hexagons;
    sf::RenderWindow& window;
    const float radius = 45.0f;
    const int rows = 9;
    const int cols = 9;

    sf::RectangleShape buttonQuit;
    sf::Text buttonTextQuit;
    sf::Font font;
    sf::Text playerText;
    sf::Text scoreText;

    HexState currentPlayer = HexState::Player1;
    Hexagon* selectedHexagon = nullptr;
    std::vector<Hexagon*> possibleMoves;


public:
    Board(sf::RenderWindow& window);

    auto createHexGrid() -> void;
    auto draw() -> bool;
    auto getClosestHexagon(float x, float y) -> Hexagon*;
    auto handleHexagonClick(Hexagon* hexagon) -> void;
    auto highlightPossibleMoves(const Hexagon* hexagon) -> void;
    auto makeMove(Hexagon* from, Hexagon* to) -> void;
    auto captureSurroundingPieces(Hexagon* hex) -> void;
    auto switchPlayer() -> void;
    auto resetHighlights() -> void;
    auto updateScore() -> void;
    auto getPlayerPiecesCount(HexState player) -> int;
};
