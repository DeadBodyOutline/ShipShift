#include <algorithm>

#include "player.h"
#include "stuffmath.h"

Player::Player(int width, int height)
    : sf::Drawable()
    , m_currentShip(nullptr)
    , m_step(10.f)
    , m_hull(100.f)
{
    // eeehhhhhhhhh....
    TriangleShip *m_triangleShip = new TriangleShip(width, height);
    m_triangleShip->setVisible(false);
    m_ships.insert(std::pair<ShipType, Ship *>(ShipType::Triangle, m_triangleShip));

    RectangleShip *m_rectangleShip = new RectangleShip(width, height);
    m_rectangleShip->setVisible(false);
    m_ships.insert(std::pair<ShipType, Ship *>(ShipType::Rectangle, m_rectangleShip));

    CircleShip *m_circleShip = new CircleShip(width / 2);
    m_circleShip->setVisible(false);
    m_ships.insert(std::pair<ShipType, Ship *>(ShipType::Circle, m_circleShip));

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

void Player::altAttack(sf::Vector2i target)
{
    if (!m_currentShip)
        return;

    if (m_shipType == ShipType::Triangle and target != sf::Vector2i())
        dynamic_cast<TriangleShip *>(m_currentShip)->setTarget(target);

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
    m_currentShip->rotate(x, y);
}

void Player::changeShipType(ShipType type)
{
    m_shipType = type;

    sf::Vector2f currPos = sf::Vector2f();
    float currRot = 0;

    if (m_currentShip) {
        currPos = position();
        currRot = m_currentShip->rotation();
        m_currentShip->setVisible(false);
    }

    m_currentShip = m_ships[type];

    if (currPos != sf::Vector2f()) {
        m_currentShip->setPosition(currPos);
        m_currentShip->setRotation(currRot);
        revaluateVelocity();
    }

    m_currentShip->setVisible(true);
}

Player::ShipType Player::shipType()
{
    return m_shipType;
}

void Player::receiveDamage(float damage)
{
    m_hull = std::max(0.f, m_hull - damage);
}

float Player::health() const
{
    return m_hull;
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

    for (auto ship : m_ships) {
        if (ship.second->visible()) {

            float newX = cos(m_currentShip->angle()) * m_velocity * delta.asSeconds();
            float newY = sin(m_currentShip->angle()) * m_velocity * delta.asSeconds();

            ship.second->move(newX, newY);
        }
        ship.second->update(delta);
    }
}

bool Player::collideWith(Ship *ship)
{
    if (!ship)
        return false;

    return m_currentShip->collideWith(ship->shape());
}

bool Player::collideWith(Projectile *projectile)
{
    if (!projectile)
        return false;

    return m_currentShip->collideWith(projectile->shape());
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

    for (auto ship : m_ships) {
        target.draw(*ship.second);
    }
}
