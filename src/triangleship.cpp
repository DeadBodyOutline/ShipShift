#include "triangleship.h"
#include "stuffmath.h"

//#include "projectile.h"
#include "laserprojectile.h"
#include "guidedprojectile.h"
#include "scene.h"

TriangleShip::TriangleShip(int width, int height)
    : Ship(width, height)
    , m_target(sf::Vector2i())
    , m_canShootAltAttack(true)
    , m_cooldown(5.f)
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

void TriangleShip::setTarget(sf::Vector2i target)
{
    m_target = target;
}

void TriangleShip::altAttack()
{
    if (!m_canShootAltAttack)
        return;

    m_canShootAltAttack = false;

    GuidedProjectile *projectile = new GuidedProjectile();
    projectile->setColor(outlineColor());
    projectile->setRotation(rotation());

    // TODO
    //if (m_target != sf::Vector2i())
        // use it to seek target

    float angle = r2d(rotation() - 90);

    sf::Vector2f displacement;
    displacement.x = cos(angle) * (height() / 5 * 4);
    displacement.y = sin(angle) * (height() / 5 * 4);

    projectile->setPosition(position() + displacement);

    Scene::instance()->addProjectile(projectile);
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
