#include "mediumenemy.h"

MediumEnemy::MediumEnemy(int width, int height)
    : Boid(width, height)
{
    m_ship = new sf::ConvexShape(4);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(255, 0, 0);

    sf::ConvexShape *shape = dynamic_cast<sf::ConvexShape *>(m_ship);
    if (!shape)
        return;

    shape->setPoint(0, sf::Vector2f(0, 0));
    shape->setPoint(1, sf::Vector2f(m_width / 2, -m_height / 2));
    shape->setPoint(2, sf::Vector2f(m_width, 0));
    shape->setPoint(3, sf::Vector2f(m_width / 2, m_height / 2));

    m_ship->setOrigin(width / 2, -height / 2);
}

void MediumEnemy::attack()
{

}

void MediumEnemy::altAttack()
{

}

void MediumEnemy::update(sf::Time delta)
{
    Boid::update(delta);
}
