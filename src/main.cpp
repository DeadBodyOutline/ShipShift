#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "input.h"
#include "wavecontroller.h"

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(800u, 600u), "ld35");

    sf::Clock deltaClock, frameClock;
    const float dt = 0.01f;
    float previousUpdateTime = deltaClock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    Input input;

    input.registerHandler(sf::Event::Closed, [&](sf::Event e){ renderWindow.close(); });
    input.registerKeyHandler(sf::Keyboard::Escape, [&](sf::Event e){ renderWindow.close(); });

    input.registerKeyHandler(sf::Keyboard::Left, [&](sf::Event e){
        // TODO: rotate spaceship left
    });

    input.registerKeyHandler(sf::Keyboard::Right, [&](sf::Event e){
        // TODO: rotate spaceship right
    });

    input.registerKeyHandler(sf::Keyboard::Up, [&](sf::Event e){
        // TODO: increase spaceship speed
    });

    input.registerKeyHandler(sf::Keyboard::Down, [&](sf::Event e){
        // TODO: decrease spaceship speed
    });

    input.registerKeyHandler(sf::Keyboard::Space, [&](sf::Event e){
        // TODO: fire
    });

    input.registerKeyHandler(sf::Keyboard::LControl, [&](sf::Event e){
        // TODO: trigger special power
    });

    WaveController waveController(renderWindow);

    while (renderWindow.isOpen())
    {
        input.handleEvents(renderWindow);

        float currentTime = deltaClock.getElapsedTime().asSeconds();
        float frameTime = currentTime - previousUpdateTime;
        previousUpdateTime = currentTime;
        accumulator += frameTime;

        sf::Vector2f movement;
        while (accumulator >= dt) {
            accumulator -= dt;
            waveController.update(dt);
        }

        renderWindow.clear();
        waveController.draw();
        renderWindow.display();
    }

    return 0;
}
