#ifndef __INPUT_H__
#define __INPUT_H__

#include <functional>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Input {
public:
    void registerHandler(sf::Event::EventType e, std::function<void(sf::Event)> handler);
    void registerKeyHandler(sf::Keyboard::Key code, std::function<void(sf::Event)> handler);
    void handleEvents(sf::RenderWindow& renderWindow);
private:
    std::map<sf::Event::EventType, std::function<void(sf::Event)>> m_events;
    std::map<sf::Keyboard::Key, std::function<void(sf::Event)>> m_keyEvents;
};

#endif // __INPUT_H__
