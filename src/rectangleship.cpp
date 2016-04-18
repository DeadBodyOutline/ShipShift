#include "rectangleship.h"

#include "timedevent.h"
#include "scene.h"

RectangleShip::RectangleShip(int width, int height)
    : Ship(width, height)
    , m_charge(false)
    , m_chargeEnabled(true)
    , m_chargeTime(3.f)
    , m_chargeTimeAcc(3.f)
    , m_chargeCooldown(6.f)
    , m_chargeCooldownAcc(0.f)
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
    if (!m_chargeEnabled)
        return;

    m_charge = true;

    m_ship->setFillColor(sf::Color(255, 255, 255, 127));
    m_ship->setOutlineColor(sf::Color(255, 255, 255, 127));
    setVelModifier(3.f);
    setMaxVelocity(300.f);
    Scene::instance()->player()->revaluateVelocity();
    Scene::instance()->player()->setCanSwitchShip(false);
    m_chargeTimeAcc = m_chargeTime;
    m_chargeCooldownAcc = 0.f;

    TimedEvent *chargeTime = new TimedEvent(m_chargeTime, m_chargeCooldown);
    chargeTime->onTrigger([&]() {
        m_charge = false;
        m_chargeEnabled = false;
        m_ship->setFillColor(sf::Color(0, 0, 0));
        m_ship->setOutlineColor(sf::Color(255, 255, 255));
        setVelModifier(.5f);
        setMaxVelocity(50.f);
        Scene::instance()->player()->revaluateVelocity();
        Scene::instance()->player()->setCanSwitchShip(true);
    });

    chargeTime->wait([&](float dt) {
        m_chargeTimeAcc -= dt;
        if (m_chargeTimeAcc <= 0.f)
            m_chargeTimeAcc = m_chargeTime;
    });

    chargeTime->run([&](float dt) {
        m_chargeCooldownAcc += dt;
        if (m_chargeCooldownAcc >= m_chargeCooldown)
            m_chargeCooldownAcc = m_chargeCooldown;
    });

    chargeTime->onFinish([&]() {
        m_chargeEnabled = true;
    });

    Scene::instance()->addTimedEvent(chargeTime);
}

void RectangleShip::update(sf::Time delta)
{
    Ship::update(delta);
}

void RectangleShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Ship::draw(target, states);
}
