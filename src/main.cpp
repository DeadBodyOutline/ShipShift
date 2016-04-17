#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "input.h"
#include "wavecontroller.h"

#include "player.h"

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(800u, 600u), "ld35");

    sf::Clock deltaClock, frameClock;
    const float dt = 0.01f;
    float previousUpdateTime = deltaClock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    Player player(50, 50);
    player.setPosition(800 / 2, 600 / 2);

    Input input;

    input.registerHandler(sf::Event::Closed, [&](sf::Event e){ renderWindow.close(); });
    input.registerKeyHandler(sf::Keyboard::Escape, [&](sf::Event e){ renderWindow.close(); });

    input.registerKeyHandler(sf::Keyboard::Left, [&](sf::Event e){
        // TODO: rotate spaceship left
    });

    input.registerKeyHandler(sf::Keyboard::Right, [&](sf::Event e){
        // TODO: rotate spaceship right
    });

    input.registerKeyHandler(sf::Keyboard::W, [&](sf::Event e){
        player.accelerate();
    });

    input.registerKeyHandler(sf::Keyboard::S, [&](sf::Event e){
        player.deacelerate();
    });

    input.registerKeyHandler(sf::Keyboard::Space, [&](sf::Event e){
        player.attack();
    });

    input.registerKeyHandler(sf::Keyboard::LControl, [&](sf::Event e){
        player.altAttack();
    });

    input.registerHandler(sf::Event::MouseMoved, [&](sf::Event e){
        player.rotate(e.mouseMove.x, e.mouseMove.y);
    });

    /// XXX just to quick test ship changing
    input.registerKeyHandler(sf::Keyboard::Num1, [&](sf::Event e){
        player.changeShipType(Player::ShipType::Triangle);
    });

    input.registerKeyHandler(sf::Keyboard::Num2, [&](sf::Event e){
        player.changeShipType(Player::ShipType::Rectangle);
    });

    input.registerKeyHandler(sf::Keyboard::Num3, [&](sf::Event e){
        player.changeShipType(Player::ShipType::Circle);
    });
    ///

    WaveController waveController(renderWindow, player);

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
            player.update(dt);
        }

        renderWindow.clear();

        waveController.draw();
        renderWindow.draw(player);

        renderWindow.display();
    }

    return 0;
}
