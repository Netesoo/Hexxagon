#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

enum class HexState {
    Empty,
    Player1,
    Player2
};

class Hexagon {
private:
    sf::CircleShape shape;
    int row;
    int col;
    HexState state;
    sf::Vector2f center;

public:
    Hexagon(const sf::CircleShape &shape, int row, int col, HexState state);

    auto contains(float x, float y) const -> bool;
    auto getShape() const-> const sf::CircleShape&;
    auto getShape() -> sf::CircleShape&;
    auto setState(HexState newState) -> void;
    auto getState() const -> HexState;
    auto getRow() const -> int;
    auto getCol() const -> int;
    auto getCenter() const -> sf::Vector2f;
    auto getDistance(const Hexagon& hex) const -> float;
    auto isNeighbor(const Hexagon& other) const -> bool;
};