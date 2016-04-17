#include "smallenemy.h"

#include "scene.h"
#include "circleprojectile.h"
#include "stuffmath.h"

SmallEnemy::SmallEnemy(int width, int height)
    : Boid(width, height)
{
    m_ship = new sf::CircleShape(width, 6);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(255, 255, 0);

    m_ship->setOrigin(width / 2, -width / 2);
}

void SmallEnemy::attack()
{
    CircleProjectile *projectile = new CircleProjectile();
    projectile->setColor(outlineColor());

    projectile->setRotation(rotation());

    float angle = r2d(rotation() - 90);

    sf::Vector2f displacement;
    displacement.x = cos(angle) * height() / 2;
    displacement.y = sin(angle) * height() / 2;

    projectile->setPosition(position() + displacement);

    Scene::instance()->addProjectile(projectile);
}

void SmallEnemy::altAttack()
{

}

void SmallEnemy::update(sf::Time delta)
{
    float dt = delta.asSeconds();
    keepDistance(m_player->position(), 250.f);
    wander(dt, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_game->getSize(), 0.01);

    Boid::update(delta);
}
