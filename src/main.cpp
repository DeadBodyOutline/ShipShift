#include <SFML/Graphics.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    sf::RenderWindow game(sf::VideoMode(800, 600), "ld35");

    while (game.isOpen()) {
        sf::Event event;

        while (game.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape)
                game.close();
            if (event.type == sf::Event::Closed)
                game.close();
        }

        game.clear();
        game.display();
    }

    return 0;
}
