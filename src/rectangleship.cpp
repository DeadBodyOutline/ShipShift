#include "rectangleship.h"

RectangleShip::RectangleShip(int width, int height)
    : Ship(width, height)
{
    m_ship = new sf::RectangleShape(sf::Vector2f(width, height));

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(255, 255, 255);

    m_ship->setOrigin(width / 2, height / 2);
}

RectangleShip::~RectangleShip()
{
}

void RectangleShip::attack()
{
}

void RectangleShip::altAttack()
{
}

void RectangleShip::update(sf::Time delta)
{
    Ship::update(delta);
}

void RectangleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Ship::draw(target, states);
}
