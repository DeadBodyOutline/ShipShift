#include "rectangleship.h"

#include "timedevent.h"
#include "scene.h"

RectangleShip::RectangleShip(int width, int height)
    : Ship(width, height)
    , m_stealth(false)
    , m_stealthEnabled(true)
    , m_stealthTime(3.f)
    , m_stealthCooldown(6.f)
{
    m_ship = new sf::RectangleShape(sf::Vector2f(width, height));

    setColor(0, 0, 0);
    setOutlineThickness(2);
    setOutlineColor(255, 255, 255);

    m_ship->setOrigin(width / 2, height / 2);

    setVelModifier(.5f);
    setMaxVelocity(50.f);
}

RectangleShip::~RectangleShip()
{
}

void RectangleShip::attack()
{
}

void RectangleShip::altAttack()
{
    if (!m_stealthEnabled)
        return;

    m_stealth = true;

    m_ship->setFillColor(sf::Color(255, 255, 255, 127));
    m_ship->setOutlineColor(sf::Color(255, 255, 255, 127));
    setVelModifier(3.f);
    setMaxVelocity(300.f);
    Scene::instance()->player()->revaluateVelocity();

    TimedEvent *stealthTime = new TimedEvent(m_stealthTime, m_stealthCooldown);
    stealthTime->onTrigger([&]() {
        m_stealth = false;
        m_stealthEnabled = false;
        m_ship->setFillColor(sf::Color(0, 0, 0));
        m_ship->setOutlineColor(sf::Color(255, 255, 255));
        setVelModifier(.5f);
        setMaxVelocity(50.f);
        Scene::instance()->player()->revaluateVelocity();
    });

    stealthTime->onFinish([&]() {
        m_stealthEnabled = true;
    });

    Scene::instance()->addTimedEvent(stealthTime);
}

void RectangleShip::update(sf::Time delta)
{
    Ship::update(delta);
}

void RectangleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Ship::draw(target, states);
}
