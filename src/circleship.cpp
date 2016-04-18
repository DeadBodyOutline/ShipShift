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
    if (m_shieldUp)
        target.draw(m_shield);

    Ship::draw(target, states);
}

bool CircleShip::collideWith(sf::Shape *shape)
{
    if (!shape)
        return false;

    return (m_shieldUp)
        ? circleTest(m_shield, *shape)
        : circleTest(*m_ship, *shape);
}

// code based on https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2
sf::Vector2f CircleShip::getShapeCenter(const sf::Shape &shape)
{
    sf::FloatRect AABB = shape.getGlobalBounds();
    return sf::Vector2f (AABB.left + AABB.width / 2.f,
            AABB.top + AABB.height / 2.f);
}

sf::Vector2f CircleShip::getShapeSize(const sf::Shape &shape)
{
    sf::FloatRect originalSize = shape.getGlobalBounds();
    sf::Vector2f scale = shape.getScale();

    return sf::Vector2f(originalSize.width * scale.x,
            originalSize.height * scale.y);
}

bool CircleShip::circleTest(const sf::Shape &shape1, const sf::Shape &shape2)
{
    sf::Vector2f obj1Size = getShapeSize(shape1);
    sf::Vector2f obj2Size = getShapeSize(shape2);

    float radius1 = (obj1Size.x + obj1Size.y) / 4;
    float radius2 = (obj2Size.x + obj2Size.y) / 4;

    sf::Vector2f distance = getShapeCenter(shape1) - getShapeCenter(shape2);

    return (distance.x * distance.x + distance.y * distance.y <=
            (radius1 + radius2) * (radius1 + radius2));
}
//
