#ifndef __RECTANGLESHIP_H__
#define __RECTANGLESHIP_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "ship.h"

class RectangleShip : public Ship
{
public:
    RectangleShip(int width = 50, int height = 50);
    ~RectangleShip();

    void attack();
    void altAttack();

    void update(sf::Time delta = sf::Time::Zero);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __RECTANGLESHIP_H__
