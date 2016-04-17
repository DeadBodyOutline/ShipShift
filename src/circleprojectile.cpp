#include "circleprojectile.h"
#include "stuffmath.h"

CircleProjectile::CircleProjectile(int width, int height)
    : Projectile(width, height)
{
    m_projectile = new sf::CircleShape(width);
    m_projectile->setOrigin(width / 2, height / 2);
    m_velocity = 5.f;
    m_damage = 1.f;
}

CircleProjectile::~CircleProjectile()
{
}

void CircleProjectile::update(sf::Time delta)
{
    float angle = r2d(rotation() - 90);

    float newX = cos(angle) * m_velocity;
    float newY = sin(angle) * m_velocity;
    move(newX, newY);

    Projectile::update(delta);
}

void CircleProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_projectile)
        return;

    target.draw(*m_projectile);
}
