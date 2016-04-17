#include "player.h"

Player::Player(int width, int height)
    : sf::Drawable()
    , m_currentShip(nullptr)
{
    m_triangleShip = std::make_shared<TriangleShip>(width, height);
    m_rectangleShip = std::make_shared<RectangleShip>(width, height);
    m_circleShip = std::make_shared<CircleShip>(width / 2);

    changeShipType(ShipType::Triangle);
    //changeShipType(ShipType::Rectangle);
    //changeShipType(ShipType::Circle);
}

Player::~Player()
{
}

void Player::attack()
{
}

void Player::altAttack()
{
}

void Player::changeShipType(ShipType type)
{
    //if (type == m_shipType)
        //return;

    m_shipType = type;

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

void Player::update(sf::Time delta)
{
    if (!m_currentShip)
        return;

    m_currentShip->update(delta);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_currentShip)
        return;

    target.draw(*m_currentShip);
}