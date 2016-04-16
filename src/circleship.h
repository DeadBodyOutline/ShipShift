#ifndef __CIRCLESHIP_H__
#define __CIRCLESHIP_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "ship.h"

class CircleShip : public Ship
{
public:
    CircleShip(int radius = 25);
    ~CircleShip();

    void attack();
    void altAttack();

    void update(sf::Time delta = sf::Time::Zero);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __CIRCLESHIP_H__
