#ifndef __CIRCLESHIP_H__
#define __CIRCLESHIP_H__

#include <SFML/System.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "ship.h"

class CircleShip : public Ship
{
public:
    CircleShip(int radius = 25);
    ~CircleShip();

    void attack();
    void altAttack();

    bool collideWith(sf::Shape *shape = nullptr, bool ship = false);
    // code based on
    // https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2
    sf::Vector2f getShapeCenter(const sf::Shape &shape);
    sf::Vector2f getShapeSize(const sf::Shape &shape);
    bool circleTest(const sf::Shape &shape1, const sf::Shape &shape2);
    //

    void update(sf::Time delta = sf::Time::Zero);

    float shieldDuration() const { return m_shieldDuration; }
    float shieldEnergy() const { return m_shieldDurationAcc; }
    bool shieldUp() const { return m_shieldUp; }

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    bool m_shieldUp;
    float m_shieldDuration;
    float m_shieldDurationAcc;
    float m_shieldIncrease;
    float m_shieldRadius;
    sf::CircleShape m_shield;
};

#endif // __CIRCLESHIP_H__
