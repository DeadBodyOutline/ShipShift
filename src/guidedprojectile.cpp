#include "guidedprojectile.h"
#include "stuffmath.h"

GuidedProjectile::GuidedProjectile(int width, int height)
    : Projectile(width, height)
    , m_target(sf::Vector2f())
{
    m_projectile = new sf::ConvexShape(4);

    sf::ConvexShape *shape = dynamic_cast<sf::ConvexShape *>(m_projectile);
    shape->setPoint(0, sf::Vector2f(0, 0));
    shape->setPoint(1, sf::Vector2f(m_width / 2, -m_height / 5));
    shape->setPoint(2, sf::Vector2f(m_width, 0));
    shape->setPoint(3, sf::Vector2f(m_width / 2, (m_height / 5) * 4));

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
    // TODO use m_target
    float angle = r2d(rotation() - 90);

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
