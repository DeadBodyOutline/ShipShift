#include "circleship.h"

CircleShip::CircleShip(int radius)
    : Ship(radius, radius)
{
    m_ship = new sf::CircleShape(radius);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(0, 255, 0);

    //dynamic_cast<sf::CircleShape *>(m_ship)->setPointCount(400); // we can define the number of point here

    m_ship->setOrigin(radius, radius);

    setVelModifier(1.f);
    setMaxVelocity(100.f);
}

CircleShip::~CircleShip()
{
}

void CircleShip::attack()
{
}

void CircleShip::altAttack()
{
}

void CircleShip::update(sf::Time delta)
{
    Ship::update(delta);
}

void CircleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Ship::draw(target, states);
}
