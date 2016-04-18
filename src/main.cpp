#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

#include "input.h"
#include "player.h"
#include "scene.h"
#include "triangleship.h"
#include "circleship.h"
#include "rectangleship.h"

// TODO: create a HUD class
sf::Text getWaveText(sf::Font &font, unsigned int wave)
{
    sf::Text text;
    text.setFont(font);
    std::ostringstream stringStream;
    stringStream << "Wave " << wave << "!";
    text.setString(stringStream.str());
    text.setPosition(10.f, 10.f);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    return text;
}

sf::Text getScoreText(sf::Font &font, unsigned long long score)
{
    sf::Text text;
    text.setFont(font);
    std::ostringstream stringStream;
    stringStream << "Score: " << score;
    text.setString(stringStream.str());
    text.setPosition(10.f, 30.f);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    return text;
}

sf::Text getGameOverText(sf::RenderWindow &game, sf::Font &font)
{
    sf::Text text;
    text.setFont(font);
    std::ostringstream stringStream;
    text.setString("GAME OVER");
    text.setPosition(200.f, game.getSize().y / 2.f - 50.f);
    text.setCharacterSize(50);
    text.setColor(sf::Color::White);
    return text;
}

sf::Text getRetryText(sf::RenderWindow &game, sf::Font &font)
{
    sf::Text text;
    text.setFont(font);
    std::ostringstream stringStream;
    text.setString("Press <RETURN> to retry");
    text.setPosition(80.f, game.getSize().y / 2.f + 15.f);
    text.setCharacterSize(30);
    text.setColor(sf::Color::White);
    return text;
}

sf::Text getShipText(sf::RenderWindow &game, sf::Font &font, unsigned int wave)
{
    sf::Text text;
    text.setFont(font);
    std::ostringstream stringStream;

    Player::ShipType type = Scene::instance()->player()->shipType();
    if (type == Player::Triangle)
        stringStream << "Shooter";
    else if (type == Player::Rectangle)
        stringStream << "Melee";
    else if (type == Player::Circle)
        stringStream << "Defender";

    stringStream << " Form";

    sf::Vector2f pos(10.f, game.getSize().y - 30.f);
    text.setPosition(pos);
    text.setString(stringStream.str());
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);

    return text;
}

void drawTriangleShipInfo(sf::RenderWindow &game, sf::Font &font)
{
    sf::RectangleShape cooldownBar(sf::Vector2f(100.f, 10.f));
    cooldownBar.setFillColor(sf::Color(255, 0, 0));
    cooldownBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownBar.setOutlineThickness(3);


    TriangleShip *ship = static_cast<TriangleShip *>(Scene::instance()->player()->currentShip());
    float cooldown = ship->cooldown();
    float cooldownCounter = ship->cooldownCounter();
    float value = 1.f;
    if (cooldownCounter > 0.f)
        value = cooldownCounter / cooldown;

    sf::RectangleShape cooldownValueBar(sf::Vector2f(cooldownBar.getSize().x * value, 10.f));
    cooldownValueBar.setFillColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineThickness(3);

    sf::Vector2f pos(game.getSize().x - cooldownBar.getSize().x - 10.f,
                     game.getSize().y - 26.f);
    cooldownBar.setPosition(pos);
    cooldownValueBar.setPosition(pos);
    game.draw(cooldownBar);
    game.draw(cooldownValueBar);

    sf::Text text;
    text.setFont(font);
    text.setString("Nova Cooldown");
    sf::Vector2f textPos(game.getSize().x - cooldownBar.getSize().x - 10.f,
                         game.getSize().y - 30.f);
    textPos.x -= cooldownBar.getSize().x + 180.f;
    text.setPosition(textPos);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    game.draw(text);
}

void drawRectangleShipInfo(sf::RenderWindow &game, sf::Font &font)
{
    sf::RectangleShape cooldownBar(sf::Vector2f(100.f, 10.f));
    cooldownBar.setFillColor(sf::Color(255, 0, 0));
    cooldownBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownBar.setOutlineThickness(3);


    RectangleShip *ship = static_cast<RectangleShip *>(Scene::instance()->player()->currentShip());
    float cooldown;
    float cooldownCounter;

    if (ship->charge()) {
        cooldown = ship->chargeTime();
        cooldownCounter = ship->chargeTimeAcc();
    } else {
        cooldown = ship->chargeCooldown();
        cooldownCounter = ship->chargeCooldownAcc();
    }

    float value = 1.f;
    if (cooldownCounter > 0.f)
        value = cooldownCounter / cooldown;

    sf::RectangleShape cooldownValueBar(sf::Vector2f(cooldownBar.getSize().x * value, 10.f));
    cooldownValueBar.setFillColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineThickness(3);

    sf::Vector2f pos(game.getSize().x - cooldownBar.getSize().x - 10.f,
                     game.getSize().y - 26.f);
    cooldownBar.setPosition(pos);
    cooldownValueBar.setPosition(pos);
    game.draw(cooldownBar);
    game.draw(cooldownValueBar);

    sf::Text text;
    text.setFont(font);
    if (ship->charge())
        text.setString("Charge Duration");
    else
        text.setString("Charge Cooldown");
    sf::Vector2f textPos(game.getSize().x - cooldownBar.getSize().x - 10.f,
                         game.getSize().y - 30.f);
    textPos.x -= cooldownBar.getSize().x + 180.f;
    text.setPosition(textPos);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    game.draw(text);
}

void drawCircleShipInfo(sf::RenderWindow &game, sf::Font &font)
{
    sf::RectangleShape cooldownBar(sf::Vector2f(100.f, 10.f));
    cooldownBar.setFillColor(sf::Color(255, 0, 0));
    cooldownBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownBar.setOutlineThickness(3);


    CircleShip *ship = static_cast<CircleShip *>(Scene::instance()->player()->currentShip());
    float cooldown = ship->shieldDuration();
    float cooldownCounter = ship->shieldEnergy();
    float value = 1.f;
    if (cooldownCounter > 0.f)
        value = cooldownCounter / cooldown;

    sf::RectangleShape cooldownValueBar(sf::Vector2f(cooldownBar.getSize().x * value, 10.f));
    cooldownValueBar.setFillColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineThickness(3);

    sf::Vector2f pos(game.getSize().x - cooldownBar.getSize().x - 10.f,
                     game.getSize().y - 26.f);
    cooldownBar.setPosition(pos);
    cooldownValueBar.setPosition(pos);
    game.draw(cooldownBar);
    game.draw(cooldownValueBar);

    sf::Text text;
    text.setFont(font);
    text.setString("Shield Energy");
    sf::Vector2f textPos(game.getSize().x - cooldownBar.getSize().x - 10.f,
                         game.getSize().y - 30.f);
    textPos.x -= cooldownBar.getSize().x + 140.f;
    text.setPosition(textPos);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    game.draw(text);
}

void drawPlayerHealth(sf::RenderWindow &game, sf::Font &font)
{
    sf::RectangleShape cooldownBar(sf::Vector2f(100.f, 10.f));
    cooldownBar.setFillColor(sf::Color(255, 0, 0));
    cooldownBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownBar.setOutlineThickness(3);


    float cooldown = Scene::instance()->player()->totalHealth();
    float cooldownCounter = Scene::instance()->player()->health();

    float value = 1.f;
    if (cooldownCounter > 0.f)
        value = cooldownCounter / cooldown;

    sf::RectangleShape cooldownValueBar(sf::Vector2f(cooldownBar.getSize().x * value, 10.f));
    cooldownValueBar.setFillColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineThickness(3);

    sf::Vector2f pos(game.getSize().x - cooldownBar.getSize().x - 10.f, 13.f);
    cooldownBar.setPosition(pos);
    cooldownValueBar.setPosition(pos);
    game.draw(cooldownBar);
    game.draw(cooldownValueBar);

    sf::Text text;
    text.setFont(font);
    text.setString("Ship Health");
    sf::Vector2f textPos(game.getSize().x - cooldownBar.getSize().x - 10.f, 10.f);
    textPos.x -= cooldownBar.getSize().x + 140.f;
    text.setPosition(textPos);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    game.draw(text);
}

void drawWaveInfo(sf::RenderWindow &game, sf::Font &font)
{
    sf::RectangleShape cooldownBar(sf::Vector2f(100.f, 10.f));
    cooldownBar.setFillColor(sf::Color(255, 0, 0));
    cooldownBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownBar.setOutlineThickness(3);

    float cooldown = Scene::instance()->waveTime();
    float cooldownCounter = Scene::instance()->waveTimeAcc();

    float value = 1.f;
    if (cooldownCounter > 0.f)
        value = cooldownCounter / cooldown;

    sf::RectangleShape cooldownValueBar(sf::Vector2f(cooldownBar.getSize().x * value, 10.f));
    cooldownValueBar.setFillColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineColor(sf::Color(0, 255, 0));
    cooldownValueBar.setOutlineThickness(3);

    sf::Vector2f pos(300.f, 13.f);
    cooldownBar.setPosition(pos);
    cooldownValueBar.setPosition(pos);
    game.draw(cooldownBar);
    game.draw(cooldownValueBar);

    sf::Text text;
    text.setFont(font);
    text.setString("Wave Time");
    sf::Vector2f textPos(150.f - 10.f, 10.f);
    text.setPosition(textPos);
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    game.draw(text);
}

int main()
{
    sf::Font font;
    if (!font.loadFromFile("resources/pressstart.ttf"))
        std::cout << "Failed to load font!" << std::endl;

    sf::RenderWindow renderWindow(sf::VideoMode(800u, 600u), "ld35");
    sf::Color backgroundColor = sf::Color(5, 6, 8, 255);

    bool gameStarted = false;
    bool gameOver = false;
    sf::Texture dboTexture;
    if (!dboTexture.loadFromFile("resources/dbo.png"))
    std::cout << "Failed to load image!" << std::endl;
    sf::Sprite dboSprite;
    dboSprite.setTexture(dboTexture);
    dboSprite.setPosition(renderWindow.getSize().x / 2.f - dboTexture.getSize().x /2.f,
                          renderWindow.getSize().y / 2.f - dboTexture.getSize().y /2.f);
    float splashTime = 3.f;

    sf::Clock deltaClock, frameClock;
    const float dt = 0.01f;
    float previousUpdateTime = deltaClock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    Player *player = Scene::instance()->player();

    Scene *scene = Scene::instance();
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

    input.registerKeyHandler(sf::Keyboard::Return, [&](sf::Event e){
        if (gameOver)
            scene->reset();
    });

    input.registerHandler(sf::Event::MouseButtonPressed, [&](sf::Event e){
        if (e.mouseButton.button == sf::Mouse::Button::Left) {
            scene->player()->attack();
        }

        if (e.mouseButton.button == sf::Mouse::Button::Right)
            scene->player()->altAttack();
    });

    input.registerHandler(sf::Event::MouseMoved, [&](sf::Event e){
        scene->player()->rotate(e.mouseMove.x, e.mouseMove.y);
        scene->player()->accelerate();
    });

    /// XXX just to quick test ship changing
    input.registerKeyHandler(sf::Keyboard::Num1, [&](sf::Event e){
        scene->player()->changeShipType(Player::ShipType::Triangle);
    });

    input.registerKeyHandler(sf::Keyboard::Num2, [&](sf::Event e){
        scene->player()->changeShipType(Player::ShipType::Rectangle);
    });

    input.registerKeyHandler(sf::Keyboard::Num3, [&](sf::Event e){
        scene->player()->changeShipType(Player::ShipType::Circle);
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
            if (gameStarted) {
                if (!gameOver)
                    scene->update(dt);
            } else {
                splashTime -= dt;
                dboSprite.setColor(sf::Color(255, 255, 255, 255 * splashTime));
                if (splashTime <= 0.f)
                    gameStarted = true;
            }
        }

        if (!gameStarted) {
            renderWindow.clear(backgroundColor);
            renderWindow.draw(dboSprite);
            renderWindow.display();
            continue;
        }

        gameOver = scene->player()->health() <= 0.f;

        renderWindow.clear(backgroundColor);
        if (!gameOver) {
            scene->draw();
            renderWindow.draw(getWaveText(font, scene->currentWave()));
            renderWindow.draw(getShipText(renderWindow, font, scene->currentWave()));
            Player::ShipType type = scene->player()->shipType();

            if (type == Player::Triangle)
                drawTriangleShipInfo(renderWindow, font);
            else if (type == Player::Rectangle)
                drawRectangleShipInfo(renderWindow, font);
            else if (type == Player::Circle)
                drawCircleShipInfo(renderWindow, font);

            drawPlayerHealth(renderWindow, font);
            drawWaveInfo(renderWindow, font);
        } else {
            renderWindow.draw(getGameOverText(renderWindow, font));
            renderWindow.draw(getRetryText(renderWindow, font));
            renderWindow.draw(getWaveText(font, scene->currentWave()));
        }
        renderWindow.draw(getScoreText(font, scene->score()));

        renderWindow.display();
    }

    return 0;
}
