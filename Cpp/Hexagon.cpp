#include "Hexagon.h"
#include "Board.h"

Hexagon::Hexagon(const sf::CircleShape& shape, int row, int col, HexState state)
    : shape(shape), row(row), col(col), state(HexState::Empty) {}

auto Hexagon::contains(float x, float y) const -> bool {

    sf::Vector2f center = getCenter();

    float dx = x - center.x;
    float dy = y - center.y;

    float radius = shape.getRadius();

    float q2x = std::abs(dx);
    float q2y = std::abs(dy) * 2.0f/std::sqrt(3);
    if (q2x > radius) return false;
    if (q2y > radius) return false;
    return (q2x * 0.5f + q2y) <= radius;
}

auto Hexagon::getShape() const -> const sf::CircleShape& {
    return shape;
}

auto Hexagon::getShape() -> sf::CircleShape & {
    return shape;
}

auto Hexagon::setState(HexState newState) -> void {
    state = newState;

    switch(state) {
        case HexState::Empty
        : shape.setFillColor(sf::Color(182,0,182));
        break;
        case HexState::Player1
        : shape.setFillColor(sf::Color::Red);
        break;
        case HexState::Player2
        : shape.setFillColor(sf::Color::Green);
        break;
    }

}

auto Hexagon::getState() const -> HexState {
    return state;
}

auto Hexagon::getRow() const -> int {
    return row;
}

auto Hexagon::getCol() const -> int {
    return col;
}

auto Hexagon::getCenter() const -> sf::Vector2f {
    auto bounds = shape.getGlobalBounds();
    return {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
}

auto Hexagon::getDistance(const Hexagon& hex) const -> float {

    auto center1 = getCenter();
    auto center2 = hex.getCenter();

    float dx = center1.x - center2.x;
    float dy = center1.y - center2.y;

    float distance = std::sqrt(dx * dx + dy * dy);

    return distance;
}

auto Hexagon::isNeighbor(const Hexagon& hex) const -> bool {
    return getDistance(hex) <= 90.0f;
}



