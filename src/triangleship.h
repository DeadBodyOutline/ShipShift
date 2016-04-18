#ifndef __TRIANGLESHIP_H__
#define __TRIANGLESHIP_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "ship.h"

class TriangleShip : public Ship
{
public:
    TriangleShip(int width = 50, int height = 50);

    void attack();
    void altAttack();

    void update(sf::Time delta = sf::Time::Zero);

    float cooldown() { return m_cooldown; }
    float cooldownCounter() { return m_cooldownCounter; }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2i m_target;

    float m_canShootAltAttack;
    float m_cooldown;
    float m_cooldownCounter;
};

#endif // __TRIANGLESHIP_H__
