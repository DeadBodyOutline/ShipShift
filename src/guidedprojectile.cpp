#include "guidedprojectile.h"
#include "stuffmath.h"

GuidedProjectile::GuidedProjectile(int width, int height)
    : Projectile(width, height)
    , m_target(nullptr)
{
    m_projectile = new sf::CircleShape(width);

    // XXX
    m_projectile->setOrigin(width / 2, -height / 2);

    m_velocity = 1.4f;
    m_damage = 4.f;
    m_liveness = 3.f;
}

GuidedProjectile::~GuidedProjectile()
{
}

void GuidedProjectile::update(sf::Time delta)
{
    sf::Vector2f v = m_target->position() - position();
    float angle = atan2f(v.y, v.x);
    float newX = cos(angle) * m_velocity;
    float newY = sin(angle) * m_velocity;
    move(newX, newY);

    Projectile::update(delta);
}

void GuidedProjectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_projectile)
        return;

    target.draw(*m_projectile);
}

void GuidedProjectile::setTarget(Ship *target)
{
    m_target = target;
}
