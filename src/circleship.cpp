#include "circleship.h"

#include "player.h"
#include "scene.h"

CircleShip::CircleShip(int radius)
    : Ship(radius, radius)
    , m_shieldUp(false)
    , m_shieldDuration(5.f)
    , m_shieldDurationAcc(5.f)
    , m_shieldIncrease(0.001)
    , m_shieldRadius(radius * 3.f)
{
    m_ship = new sf::CircleShape(radius);
    m_shield = sf::CircleShape(m_shieldRadius);

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(0, 255, 0);
    m_shield.setFillColor(sf::Color(0, 255, 0, 127));

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
    if (m_shieldDurationAcc <= 0)
        return;
    m_shieldUp = true;
    Scene::instance()->player()->setCanSwitchShip(false);
}

void CircleShip::update(sf::Time delta)
{
    if (m_shieldUp) {
        m_shieldDurationAcc -= delta.asSeconds();
        if (m_shieldDurationAcc <= 0) {
            m_shieldUp = false;
            Scene::instance()->player()->setCanSwitchShip(true);
        }
    } else {
        m_shieldDurationAcc += delta.asSeconds();
        if (m_shieldDurationAcc >= m_shieldDuration)
            m_shieldDurationAcc = m_shieldDuration;
    }
    Ship::update(delta);

    sf::Vector2f shieldPos = m_ship->getPosition();
    shieldPos.x -= m_shieldRadius;
    shieldPos.y -= m_shieldRadius;

    m_shield.setPosition(shieldPos);
}

void CircleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Ship::draw(target, states);
    if (m_shieldUp)
        target.draw(m_shield);
}
