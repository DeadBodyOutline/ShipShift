#include <algorithm>

#include "player.h"

Player::Player(int width, int height)
    : sf::Drawable()
    , m_currentShip(nullptr)
    , m_step(10.f)
    , m_angle(0.f)
{
    m_triangleShip = std::make_shared<TriangleShip>(width, height);
    m_rectangleShip = std::make_shared<RectangleShip>(width, height);
    m_circleShip = std::make_shared<CircleShip>(width / 2);

    changeShipType(ShipType::Triangle);
}

Player::~Player()
{
}

void Player::attack()
{
    if (!m_currentShip)
        return;

    m_currentShip->attack();
}

void Player::altAttack()
{
    if (!m_currentShip)
        return;

    m_currentShip->altAttack();
}

void Player::accelerate()
{
    if (!m_currentShip)
        return;

    float velocity = m_velocity + (m_step * m_currentShip->velModifier());
    m_velocity =  std::min(velocity, m_currentShip->maxVelocity());
}

void Player::deacelerate()
{
    if (!m_currentShip)
        return;

    float velocity = m_velocity - (m_step * m_currentShip->velModifier());
    m_velocity =  std::max(velocity, -m_currentShip->maxVelocity());
}

void Player::rotate(int x, int y)
{
    sf::Vector2f v = sf::Vector2f(x, y) - position();

    m_angle = atan2f(v.y, v.x);
    float angle = m_angle * 180.f / 3.14159265359f;

    m_currentShip->setRotation(angle + 90);
}

void Player::changeShipType(ShipType type)
{
    m_shipType = type;

    sf::Vector2f currPos = sf::Vector2f();
    float currRot = 0;

    if (m_currentShip) {
        currPos = position();
        currRot = m_currentShip->rotation();
    }

    switch (type) {
        case ShipType::Triangle:
            m_currentShip = m_triangleShip;
            break;
        case ShipType::Rectangle:
            m_currentShip = m_rectangleShip;
            break;
        case ShipType::Circle:
            m_currentShip = m_circleShip;
            break;
        default:
            break;
    }

    if (currPos != sf::Vector2f()) {
        m_currentShip->setPosition(currPos);
        m_currentShip->setRotation(currRot);
        revaluateVelocity();
    }
}

Player::ShipType Player::shipType()
{
    return m_shipType;
}

void Player::setPosition(int x, int y)
{
    sf::Vector2f v(x, y);
    setPosition(v);
}

void Player::setPosition(sf::Vector2f point)
{
    if (!m_currentShip || point == position())
        return;

    m_currentShip->setPosition(point);
}

sf::Vector2f Player::position() const
{
    if (!m_currentShip)
        return sf::Vector2f();

    return m_currentShip->position();
}

void Player::update(float delta)
{
    update(sf::seconds(delta));
}

void Player::update(sf::Time delta)
{
    if (!m_currentShip)
        return;

    float newX = cos(m_angle) * m_velocity * delta.asSeconds();
    float newY = sin(m_angle) * m_velocity * delta.asSeconds();

    m_currentShip->move(newX, newY);
    m_currentShip->update(delta);
}

// limit the velocity when shapeshifting the ship
void Player::revaluateVelocity()
{
    m_velocity = (m_velocity > 0)
        ? std::min(m_velocity, m_currentShip->maxVelocity())
        : std::max(m_velocity, -m_currentShip->maxVelocity());
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_currentShip)
        return;

    target.draw(*m_currentShip);
}
