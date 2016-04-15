#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include <tmx/Log.h>

sf::Vector2f getViewMovement(float dt)
{
    sf::Vector2f movement;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x = -1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x = 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y = -1.f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y = 1.f;

    movement = Helpers::Vectors::normalize(movement) * 500.f * dt;
    return movement;
}

void handleWindowEvent(sf::RenderWindow& renderWindow)
{
    sf::Event event;
    while(renderWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed
            || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            renderWindow.close();
        }
    }
}

sf::Text getFpsText()
{
    sf::Text fpsText;
    fpsText.setColor(sf::Color::White);
    fpsText.setCharacterSize(25);
    return fpsText;
}

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(800u, 600u), "ld35");
    sf::Text fpsText = getFpsText();

    tmx::Logger::SetLogLevel(tmx::Logger::Info | tmx::Logger::Error);

    tmx::MapLoader ml("3rdparty/dependencies/sfml-tmxloader/maps/");
    ml.Load("desert.tmx");

    sf::Clock deltaClock, frameClock;

    const float dt = 0.01f;

    float previousUpdateTime = deltaClock.getElapsedTime().asSeconds();
    float accumulator = 0.f;

    while (renderWindow.isOpen())
    {
        handleWindowEvent(renderWindow);

        float currentTime = deltaClock.getElapsedTime().asSeconds();
        float frameTime = currentTime - previousUpdateTime;
        previousUpdateTime = currentTime;
        accumulator += frameTime;

        sf::Vector2f movement;
        while (accumulator >= dt)
        {
            movement = getViewMovement(dt);
            accumulator -= dt;
        }

        sf::View view = renderWindow.getView();
        view.move(movement);
        renderWindow.setView(view);

        float fpsCount = 1.f / frameClock.restart().asSeconds();
        fpsText.setString("FPS: " + (std::to_string(fpsCount)));
        fpsText.move(movement);

        renderWindow.clear();
        renderWindow.draw(ml);
        renderWindow.draw(fpsText);
        renderWindow.display();
    }

    return 0;
}
