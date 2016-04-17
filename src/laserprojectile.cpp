#include "laserprojectile.h"
#include "stuffmath.h"

LaserProjectile::LaserProjectile(int width, int height)
    : Projectile(width, height)
{
    m_projectile = new sf::RectangleShape(sf::Vector2f(width, height));
    m_projectile->setOrigin(width / 2, height / 2);
    m_velocity = 5.f;
    m_damage = 1.f;
}

LaserProjectile::~LaserProjectile()
{
}

void LaserProjectile::update(sf::Time delta)
{
    float angle = r2d(rotation() - 90);

    float newX = cos(angle) * m_velocity;
    float newY = sin(angle) * m_velocity;
    move(newX, newY);

    Projectile::update(delta);
}

void LaserProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_projectile)
        return;

    target.draw(*m_projectile);
}
