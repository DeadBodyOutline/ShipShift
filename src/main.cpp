#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "input.h"
#include "player.h"
#include "scene.h"

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(800u, 600u), "ld35");

    sf::Clock deltaClock, frameClock;
    const float dt = 0.01f;
    float previousUpdateTime = deltaClock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    Player player(50, 50);
    player.setPosition(800 / 2, 600 / 2);

    Scene *scene = Scene::instance();
    scene->setPlayer(&player);
    scene->setGame(&renderWindow);

    Input input;

    input.registerHandler(sf::Event::Closed, [&](sf::Event e){ renderWindow.close(); });
    input.registerKeyHandler(sf::Keyboard::Escape, [&](sf::Event e){ renderWindow.close(); });

    input.registerKeyHandler(sf::Keyboard::Left, [&](sf::Event e){
        // TODO: rotate spaceship left
    });

    input.registerKeyHandler(sf::Keyboard::Right, [&](sf::Event e){
        // TODO: rotate spaceship right
    });

    input.registerHandler(sf::Event::MouseButtonPressed, [&](sf::Event e){
        if (e.mouseButton.button == sf::Mouse::Button::Left)
            player.attack();

        if (e.mouseButton.button == sf::Mouse::Button::Right)
            player.altAttack();
    });

    input.registerHandler(sf::Event::MouseMoved, [&](sf::Event e){
        player.rotate(e.mouseMove.x, e.mouseMove.y);
        player.accelerate();
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
            scene->update(dt);
        }

        renderWindow.clear();
        scene->draw();
        renderWindow.display();
    }

    return 0;
}
