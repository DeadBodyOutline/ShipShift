#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "input.h"

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(800u, 600u), "ld35");

    sf::Clock deltaClock, frameClock;
    const float dt = 0.01f;
    float previousUpdateTime = deltaClock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    Input input;

    input.registerHandler(sf::Event::Closed, [&](){ renderWindow.close(); });
    input.registerKeyHandler(sf::Keyboard::Escape, [&](){ renderWindow.close(); });

    while (renderWindow.isOpen())
    {
        input.handleEvents(renderWindow);

        float currentTime = deltaClock.getElapsedTime().asSeconds();
        float frameTime = currentTime - previousUpdateTime;
        previousUpdateTime = currentTime;
        accumulator += frameTime;

        sf::Vector2f movement;
        while (accumulator >= dt)
            accumulator -= dt;

        renderWindow.clear();
        renderWindow.display();
    }

    return 0;
}
