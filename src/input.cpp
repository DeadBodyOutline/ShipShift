#include "input.h"

void Input::registerHandler(sf::Event::EventType e, std::function<void(sf::Event)> handler)
{
    m_events[e] = handler;
}

void Input::registerKeyHandler(sf::Keyboard::Key code, std::function<void(sf::Event)> handler)
{
    m_keyEvents[code] = handler;
}

void Input::handleEvents(sf::RenderWindow& renderWindow)
{
    sf::Event event;
    while (renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) { // TODO: released?
            auto got = m_keyEvents.find(event.key.code);
            if (got != m_keyEvents.end())
                got->second(event);
        } else {
            auto got = m_events.find(event.type);
            if (got != m_events.end())
                got->second(event);
        }
    }
}
