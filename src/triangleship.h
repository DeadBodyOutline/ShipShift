#ifndef __TRIANGLESHIP_H__
#define __TRIANGLESHIP_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include <vector>

#include "ship.h"
#include "laserprojectile.h"

class TriangleShip : public Ship
{
public:
    TriangleShip(int width = 50, int height = 50);
    ~TriangleShip();

    void attack();
    void altAttack();

    void update(sf::Time delta = sf::Time::Zero);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<LaserProjectile *> m_projectiles;
};

#endif // __TRIANGLESHIP_H__
