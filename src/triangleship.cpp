#include "triangleship.h"

TriangleShip::TriangleShip(int width, int height)
    : Ship(width, height)
{
    m_ship = new sf::ConvexShape(3);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(255, 0, 0);

    dynamic_cast<sf::ConvexShape *>(m_ship)->setPoint(0, sf::Vector2f(0, 0));
    dynamic_cast<sf::ConvexShape *>(m_ship)->setPoint(1, sf::Vector2f(m_width / 2, -m_height));
    dynamic_cast<sf::ConvexShape *>(m_ship)->setPoint(2, sf::Vector2f(m_width, 0));

    m_ship->setOrigin(width / 2, -height / 2);
}

TriangleShip::~TriangleShip()
{
}

void TriangleShip::attack()
{
}

void TriangleShip::altAttack()
{
}

void TriangleShip::update(sf::Time delta)
{
    Ship::update(delta);
}

void TriangleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Ship::draw(target, states);
}
