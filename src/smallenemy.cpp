#include "smallenemy.h"

SmallEnemy::SmallEnemy(int width, int height)
    : Boid(width, height)
{
    m_ship = new sf::CircleShape(width, 6);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(255, 255, 0);

    m_ship->setOrigin(width / 2, -width / 2);
}

void SmallEnemy::attack()
{

}

void SmallEnemy::altAttack()
{

}

void SmallEnemy::update(sf::Time delta)
{
    Boid::update(delta);
}
