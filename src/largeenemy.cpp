#include "largeenemy.h"

#include "scene.h"
#include "laserprojectile.h"
#include "stuffmath.h"

LargeEnemy::LargeEnemy(int width, int height)
    : Boid(width, height)
{
    m_ship = new sf::ConvexShape(4);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(0, 0, 255);

    sf::ConvexShape *shape = dynamic_cast<sf::ConvexShape *>(m_ship);
    if (!shape)
        return;

    shape->setPoint(0, sf::Vector2f(0, 0));
    shape->setPoint(1, sf::Vector2f(m_width, 0));
    shape->setPoint(2, sf::Vector2f(m_width, m_height));
    shape->setPoint(3, sf::Vector2f(0, m_height));

    m_ship->setOrigin(width / 2, -height / 2);
}

void LargeEnemy::attack()
{
    LaserProjectile *projectile = new LaserProjectile();
    projectile->setColor(outlineColor());

    projectile->setRotation(rotation());

    float angle = r2d(rotation() - 90);

    sf::Vector2f displacement;
    displacement.x = cos(angle) * height() / 2;
    displacement.y = sin(angle) * height() / 2;

    projectile->setPosition(position() + displacement);

    Scene::instance()->addProjectile(projectile);
}

void LargeEnemy::altAttack()
{

}

void LargeEnemy::update(sf::Time delta)
{
    float dt = delta.asSeconds();
    keepDistance(m_player->position(), 350.f);
    wander(dt, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_game->getSize(), 0.6);

    Boid::update(delta);
}
