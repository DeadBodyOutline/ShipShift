#include <cmath>

#include "triangleship.h"
#include "stuffmath.h"

#include "laserprojectile.h"
#include "guidedprojectile.h"
#include "scene.h"

TriangleShip::TriangleShip(int width, int height)
    : Ship(width, height)
    , m_target(sf::Vector2i())
    , m_canShootAltAttack(true)
    , m_cooldown(10.f)
    , m_cooldownCounter(0.f)
{
    m_ship = new sf::ConvexShape(3);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(255, 0, 0);

    sf::ConvexShape *shape = dynamic_cast<sf::ConvexShape *>(m_ship);
    shape->setPoint(0, sf::Vector2f(0, 0));
    shape->setPoint(1, sf::Vector2f(m_width / 2, -m_height));
    shape->setPoint(2, sf::Vector2f(m_width, 0));

    m_ship->setOrigin(width / 2, -height / 2);

    setVelModifier(2.f);
    setMaxVelocity(200.f);
}

void TriangleShip::attack()
{
    LaserProjectile *projectile = new LaserProjectile(4, 30);
    projectile->setPlayerProjectile(true);
    projectile->setColor(outlineColor());
    projectile->setRotation(rotation());
    projectile->setDamage(10.f);

    float angle = r2d(rotation() - 90);

    sf::Vector2f displacement;
    displacement.x = cos(angle) * height() / 2;
    displacement.y = sin(angle) * height() / 2;

    projectile->setPosition(position() + displacement);

    Scene::instance()->addProjectile(projectile);
}

void TriangleShip::altAttack()
{
    if (!m_canShootAltAttack)
        return;

    int n = 30;
    for (int i = 0; i < 360; i += 360 / n) {
        LaserProjectile *projectile = new LaserProjectile(4, 30);
        projectile->setPlayerProjectile(true);
        projectile->setColor(sf::Color(160, 32, 240));
        projectile->setRotation(rotation());
        projectile->setDamage(10.f);

        float angle = i;
        sf::Vector2f displacement;
        displacement.x = cos(angle) * height() / 2;
        displacement.y = sin(angle) * height() / 2;
        projectile->setRotation(angle + 90);

        projectile->setPosition(position() + displacement);

        Scene::instance()->addProjectile(projectile);
    }

    m_canShootAltAttack = false;
}

void TriangleShip::update(sf::Time delta)
{
    if (!m_canShootAltAttack) {
        m_cooldownCounter += delta.asSeconds();

        if (m_cooldownCounter >= m_cooldown) {
            m_canShootAltAttack = true;
            m_cooldownCounter = 0.f;
        }
    }

    Ship::update(delta);
}

void TriangleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Ship::draw(target, states);
}
