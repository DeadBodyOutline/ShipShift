#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void handleWindowEvent(sf::RenderWindow& renderWindow)
{
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed
            || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            renderWindow.close();
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
            accumulator -= dt;

        renderWindow.clear();
        renderWindow.display();
    }

    return 0;
}
