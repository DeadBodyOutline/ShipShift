#include "triangleship.h"
#include "stuffmath.h"

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

    setVelModifier(2.f);
    setMaxVelocity(200.f);
}

TriangleShip::~TriangleShip()
{
    m_projectiles.clear();
}

void TriangleShip::attack()
{
    LaserProjectile *projectile = new LaserProjectile();
    projectile->setColor(outlineColor());
    projectile->setRotation(rotation());

    float angle = r2d(rotation() - 90);

    sf::Vector2f displacement;
    displacement.x = cos(angle) * height() / 2;
    displacement.y = sin(angle) * height() / 2;

    projectile->setPosition(position() + displacement);

    m_projectiles.push_back(projectile);
}

void TriangleShip::altAttack()
{
}

void TriangleShip::update(sf::Time delta)
{
    for (auto projectile : m_projectiles)
        projectile->update(delta);

    Ship::update(delta);
}

void TriangleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto projectile : m_projectiles)
        target.draw(*projectile, states);

    Ship::draw(target, states);
}
