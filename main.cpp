#include <SFML/Graphics.hpp>
#include "Cpp/Board.h"
#include "Cpp/Menu.h"
#include "Cpp/Scores.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Hexxagon");
    Menu menu(window);

    while (window.isOpen()) {
        int choice = menu.drawMenu();

        if (choice == -1) {
            break;
        }
        if (choice == 1) {
            Board board(window);
            board.createHexGrid();

            bool backToMenu = board.draw();
            if (backToMenu) {
                continue;
            }
        }
        if (choice == 4) {
            Scores scores(window);

            bool backToMenu = scores.drawaScore();
            if (backToMenu) {
                continue;
            }
        }
    }
}


